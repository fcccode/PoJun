#include "stdafx.h"
#include "XDebugControl.h"  
#include "XBreakPoint.h"
#include "XInt3Tab.h"
#include "XThreadTab.h"
#include "XModelTab.h"   
#include "XOutStringTab.h"
#include <XThread.h>
#include "XDecodingASM.h"
#include "XCommandMgr.h" 
#include "XMemoryMgr.h"
#include "XSQLite3.h"
#include <XProcess.h>

XDebugControl* XDebugControl::m_This = nullptr;
XDebugControl::XDebugControl()
{
}


XDebugControl::~XDebugControl()
{
}

XDebugControl* XDebugControl::pins()
{
    if (m_This == nullptr)
    {
        m_This = new XDebugControl;
    }

    return m_This;
}

void XDebugControl::start_debug_loop(XString& file_path, pfun_in_fun in_fun, pfun_out_fun out_fun, pfun_command_call_back_out command_out, DWORD count)
{
    if (in_fun == nullptr || out_fun == nullptr)
    {
        return;
    }
     
    this->file_path = file_path;
    this->count = count;
    this->f_in = in_fun;
    this->f_out = out_fun;
    this->f_command_out = command_out;

    XSQLite3::pins()->init_sql(file_path);

    if (!XProcess::create_process(file_path))
    {
        return;
    }
    
    DEBUG_INFO debug_info;
    memset(&debug_info, 0x0, sizeof(DEBUG_INFO));
    debug_info.process = INVALID_HANDLE_VALUE;
    debug_info.thread = INVALID_HANDLE_VALUE;
    debug_info.context.ContextFlags = CONTEXT_FULL | CONTEXT_DEBUG_REGISTERS;
       
    do
    {  
        ::WaitForDebugEvent(&debug_info.event, INFINITE);
        debug_info.process =
            ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, debug_info.event.dwProcessId);
        debug_info.thread =
            ::OpenThread(THREAD_ALL_ACCESS, FALSE, debug_info.event.dwThreadId);  
        ::GetThreadContext(debug_info.thread, &debug_info.context);

        DWORD dwContinueStatue = DBG_EXCEPTION_NOT_HANDLED;
        switch (debug_info.event.dwDebugEventCode)
        {
        case EXCEPTION_DEBUG_EVENT:
        {
            switch (debug_info.event.u.Exception.ExceptionRecord.ExceptionCode)
            {
            case EXCEPTION_ACCESS_VIOLATION:
                dwContinueStatue = e_acess_violation(debug_info);
                break;
            case EXCEPTION_BREAKPOINT:
                dwContinueStatue = e_break_point(debug_info);
                break;
            case EXCEPTION_SINGLE_STEP:
                dwContinueStatue = e_single_step(debug_info);
                break;
            default:
                break;
            }
            break;
        }
        case CREATE_PROCESS_DEBUG_EVENT:
            dwContinueStatue = create_process_debug_event(debug_info);
            break; 
        case CREATE_THREAD_DEBUG_EVENT:
            dwContinueStatue = create_thread_debug_event(debug_info);
            break;
        case EXIT_THREAD_DEBUG_EVENT:
            dwContinueStatue = exit_thread_debug_event(debug_info);
            break;
        case EXIT_PROCESS_DEBUG_EVENT:
            dwContinueStatue = exit_process_debug_event(debug_info);
            break;
        case LOAD_DLL_DEBUG_EVENT:
            dwContinueStatue = load_dll_debug_event(debug_info);
            break;
        case UNLOAD_DLL_DEBUG_EVENT:
            dwContinueStatue = unload_dll_debug_event(debug_info);
            break;
        case OUTPUT_DEBUG_STRING_EVENT:
            dwContinueStatue = output_debug_string_event(debug_info);
            break;
        case RIP_EVENT:
            dwContinueStatue = irp_event(debug_info);
            break;
        default:
            break;
        }

        ::SetThreadContext(debug_info.thread, &debug_info.context);
        ::ContinueDebugEvent(debug_info.event.dwProcessId, debug_info.event.dwThreadId, dwContinueStatue);
        ::CloseHandle(debug_info.process);
        ::CloseHandle(debug_info.thread);

    } while (TRUE);
}

DWORD XDebugControl::e_acess_violation(DEBUG_INFO& debug_info)
{  
    EXCEPTION_DEBUG_INFO *ed = (EXCEPTION_DEBUG_INFO*)&debug_info.event.u;
    if (ed == nullptr)
    {
        return DBG_CONTINUE;
    }

    CXMEMORY_MGR status = XMemoryMgr::pins()->is_my_break_point(ed);
    if (status == CXMEMORY_MGR::E_NOT_TYPE)
    {
        return DBG_EXCEPTION_NOT_HANDLED;
    }
     
    if (status == CXMEMORY_MGR::E_TRUE)
    { 
        XMemoryMgr::pins()->reset_protect(debug_info.process, ed->ExceptionRecord.ExceptionInformation[1]);

        user_control(debug_info);
        
        debug_info.context.EFlags |= 0x100; 
    } 

    return DBG_CONTINUE;;
}

DWORD XDebugControl::e_break_point(DEBUG_INFO& debug_info)
{
    EXCEPTION_DEBUG_INFO *ed = (EXCEPTION_DEBUG_INFO*)&debug_info.event.u;
    if (ed != nullptr)
    {
        EXCEPTION_RECORD *er = (EXCEPTION_RECORD*)&ed->ExceptionRecord;
        if (er != nullptr)
        { 
            DWORD next_address = 0;
            BYTE opcode = 0;
            BP_STATUS status = XBreakPoint::pins()->break_point(er, debug_info);
            switch (status)
            {
            case BP_NULL:
                return DBG_EXCEPTION_NOT_HANDLED;
            case BP_OEP: 
                this->teb = XThread::get_thread_teb(debug_info.thread, debug_info.context.SegFs);
                XBreakPoint::pins()->reduction_oep(debug_info.process);
            case BP_P_SINGLE_STEP:
            case BP_CC:
                { 
                    XBreakPoint::pins()->reduction_cc(debug_info.process, debug_info.context.Eip, false);
                     
                    user_control(debug_info);
                     
                    reduction_break_point(debug_info.process, true);
                      
                    if (status != BP_OEP)
                    {
                        //OEP的CC就不用还原了
                        XBreakPoint::pins()->set_reduction_single_step(debug_info.context);
                    } 
                    break;
                }   
            default:
                break;
            }  
        }
    } 

    return DBG_CONTINUE;
}

DWORD XDebugControl::e_single_step(DEBUG_INFO& debug_info)
{
    EXCEPTION_DEBUG_INFO *ed = (EXCEPTION_DEBUG_INFO*)&debug_info.event.u;
    if (ed == nullptr)
    {
        return DBG_EXCEPTION_NOT_HANDLED;
    }
      
    if (debug_info.context.Dr6 != 0 
        && ((debug_info.context.Dr6 & 0x4000) == 0))
    { 
        user_control(debug_info); 

        reduction_break_point(debug_info.process, true);
    } 
    else if (XCommandMgr::pins()->is_single_step())
    { 
        //判断当前单步上释放存在CC断点
        bool current_cc = XInt3Tab::pins()->is_my_cc(debug_info.process, debug_info.context.Eip);
        if (current_cc)
        {  
            //存在则还原，主要用于展示反汇编和跳过当前指令
            XBreakPoint::pins()->reduction_cc(debug_info.process, debug_info.context.Eip, false);
        }

        user_control(debug_info);
         
        reduction_break_point(debug_info.process, true);

        if (current_cc)
        {
            //这里刚好也是CC，那么将这条CC给记录下
            XBreakPoint::pins()->set_reduction_single_step(debug_info.context);
        }
    }
    else 
    { 
        reduction_break_point(debug_info.process, true); 
    }

    return DBG_CONTINUE;
}

DWORD XDebugControl::create_process_debug_event(DEBUG_INFO& debug_info)
{
    CREATE_PROCESS_DEBUG_INFO *cp = (CREATE_PROCESS_DEBUG_INFO*)&debug_info.event.u.CreateProcessInfo;
    if (cp != nullptr)
    {
        XInt3Tab::pins()->create_process(cp, debug_info.process);
    }

    return DBG_CONTINUE;
}

DWORD XDebugControl::create_thread_debug_event(DEBUG_INFO& debug_info)
{
    CREATE_THREAD_DEBUG_INFO *ct = (CREATE_THREAD_DEBUG_INFO*)&debug_info.event.u.CreateThread;
    if (ct != nullptr)
    {
        XThreadTab::pins()->insert_thread(ct);
    }

    return DBG_CONTINUE;
}

DWORD XDebugControl::exit_thread_debug_event(DEBUG_INFO& debug_info)
{ 
    //没有有用的信息。
    return DBG_CONTINUE;
}

DWORD XDebugControl::exit_process_debug_event(DEBUG_INFO& debug_info)
{ 
    //没有有用的信息。 
    return DBG_CONTINUE;
}
 
DWORD XDebugControl::load_dll_debug_event(DEBUG_INFO& debug_info)
{
    LOAD_DLL_DEBUG_INFO *ld = (LOAD_DLL_DEBUG_INFO*)&debug_info.event.u.LoadDll;
    if (ld != nullptr)
    {
        XModelTab::pins()->insert_dll(ld);
    }
      
    return DBG_CONTINUE;
}

DWORD XDebugControl::unload_dll_debug_event(DEBUG_INFO& debug_info)
{
    UNLOAD_DLL_DEBUG_INFO *ud = (UNLOAD_DLL_DEBUG_INFO*)&debug_info.event.u.UnloadDll;
    if (ud != nullptr)
    {
        XModelTab::pins()->remove_dll((DWORD)ud->lpBaseOfDll);
    }
      
    return DBG_CONTINUE;
}

DWORD XDebugControl::output_debug_string_event(DEBUG_INFO& debug_info)
{
    OUTPUT_DEBUG_STRING_INFO *ods = (OUTPUT_DEBUG_STRING_INFO*)&debug_info.event.u.DebugString;
    if (ods != nullptr)
    { 
        XOutStringTab::pins()->insert_out_string(ods, debug_info.process);
    }

    return DBG_CONTINUE;
}

DWORD XDebugControl::irp_event(DEBUG_INFO& debug_info)
{ 
    //没有有用的信息
    return DBG_CONTINUE;
} 
 

void XDebugControl::user_control(DEBUG_INFO& debug_info)
{
    std::list<DECODEING_ASM> asm_tab;
    bool ok = XDecodingASM::pins()->decoding_asm(
        debug_info.process,
        debug_info.context.Eip,
        this->count,
        asm_tab);
    if (!ok)
    {   
        return;
    }
     
    OPCODE_INFO opcode_info;
    if (asm_tab.size())
    {
        std::list<DECODEING_ASM>::iterator it = asm_tab.begin();
        opcode_info.current_opcode = it->opcode[0];
        ++it;
        opcode_info.next_address = it->address;
    } 

    this->f_out(debug_info.context, asm_tab);

    asm_tab.clear();

    XString str_command;
    //命令不等于 t,p,g则一直循环
    do 
    {
        this->f_in(str_command);

        DEBUG_MODULE_DATA module_data;
        command_explanation(str_command, debug_info, opcode_info, module_data);
        this->f_command_out(module_data);

    } while (scan_command(str_command));
}

void XDebugControl::command_explanation(XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    XCommandMgr::pins()->command_call_back(command, debug_info, opcode_info, out_module_data);
}

bool XDebugControl::scan_command(XString& command)
{
    if (command.empty())
    {
        return true;
    }

    std::vector<XString> vt_command;
    XString str_command = command;
    str_command.get_vt_str_seg(vt_command, L" ");
    XString command_head = *vt_command.begin();

    if (command_head.compare(L"t") == 0
        || command_head.compare(L"p") == 0
        || command_head.compare(L"g") == 0)
    {
        return false;
    }

    return true;
}

void XDebugControl::reduction_break_point(HANDLE handle, bool status)
{ 
    DWORD address = XBreakPoint::pins()->get_reduction_single_step();
    if (address != 0)
    {
        //如果上一条指令触发的是CC，那么将上一条的CC断点还原
        XBreakPoint::pins()->reduction_cc(handle, address, true);
    }

    address = XMemoryMgr::pins()->get_reduction_memory_break_point();
    if (address != 0)
    {
        //如果上一条断点触发的是内存断点，那么将上一条的内存断点还原
        XMemoryMgr::pins()->reset_protect(handle, address, true); 
    }

    return;
}