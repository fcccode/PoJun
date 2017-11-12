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

void XDebugControl::start_debug_loop(XString& file_path, pfun_in_fun in_fun, pfun_out_fun out_fun, DWORD count)
{
    if (in_fun == nullptr || out_fun == nullptr)
    {
        return;
    }
     
    this->file_path = file_path;
    this->count = count;
    this->f_in = in_fun;
    this->f_out = out_fun;

    tagDebugInfo debug_info;
    memset(&debug_info, 0x0, sizeof(tagDebugInfo));
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

DWORD XDebugControl::e_acess_violation(tagDebugInfo& debug_info)
{  
    return DBG_CONTINUE;
}

DWORD XDebugControl::e_break_point(tagDebugInfo& debug_info)
{
    EXCEPTION_DEBUG_INFO *ed = (EXCEPTION_DEBUG_INFO*)&debug_info.event.u;
    if (ed != nullptr)
    {
        EXCEPTION_RECORD *er = (EXCEPTION_RECORD*)&ed->ExceptionRecord;
        if (er != nullptr)
        {
            XString command;
            DWORD next_address = 0;
            BP_STATUS status = XBreakPoint::pins()->break_point(er, debug_info);
            if (status == BP_NULL)
            {
                return DBG_EXCEPTION_NOT_HANDLED;
            }
            else if (status == BP_OEP)
            { 
                this->teb = XThread::get_thread_teb(debug_info.thread, debug_info.context.SegFs);
                XBreakPoint::pins()->reduction_oep(debug_info.process);
                user_control(debug_info, command, next_address);
            }
            else if (status == BP_CC)
            {
                user_control(debug_info, command, next_address);
            }

            command_explanation(command, debug_info, next_address);
        }
    } 

    return DBG_CONTINUE;
}

DWORD XDebugControl::e_single_step(tagDebugInfo& debug_info)
{
    return 0;
}

DWORD XDebugControl::create_process_debug_event(tagDebugInfo& debug_info)
{
    CREATE_PROCESS_DEBUG_INFO *cp = (CREATE_PROCESS_DEBUG_INFO*)&debug_info.event.u.CreateProcessInfo;
    if (cp  != nullptr)
    {
        XInt3Tab::pins()->create_process(cp, debug_info.process);
    }

    return DBG_CONTINUE;
}

DWORD XDebugControl::create_thread_debug_event(tagDebugInfo& debug_info)
{
    CREATE_THREAD_DEBUG_INFO *ct = (CREATE_THREAD_DEBUG_INFO*)&debug_info.event.u.CreateThread;
    if (ct != nullptr)
    {
        XThreadTab::pins()->insert_thread(ct);
    }

    return DBG_CONTINUE;
}

DWORD XDebugControl::exit_thread_debug_event(tagDebugInfo& debug_info)
{ 
    //没有有用的信息。
    return DBG_CONTINUE;
}

DWORD XDebugControl::exit_process_debug_event(tagDebugInfo& debug_info)
{ 
    //没有有用的信息。 
    return DBG_CONTINUE;
}
 
DWORD XDebugControl::load_dll_debug_event(tagDebugInfo& debug_info)
{
    LOAD_DLL_DEBUG_INFO *ld = (LOAD_DLL_DEBUG_INFO*)&debug_info.event.u.LoadDll;
    if (ld != nullptr)
    {
        XModelTab::pins()->insert_dll(ld);
    }
      
    return DBG_CONTINUE;
}

DWORD XDebugControl::unload_dll_debug_event(tagDebugInfo& debug_info)
{
    UNLOAD_DLL_DEBUG_INFO *ud = (UNLOAD_DLL_DEBUG_INFO*)&debug_info.event.u.UnloadDll;
    if (ud != nullptr)
    {
        XModelTab::pins()->remove_dll((DWORD)ud->lpBaseOfDll);
    }
      
    return DBG_CONTINUE;
}

DWORD XDebugControl::output_debug_string_event(tagDebugInfo& debug_info)
{
    OUTPUT_DEBUG_STRING_INFO *ods = (OUTPUT_DEBUG_STRING_INFO*)&debug_info.event.u.DebugString;
    if (ods != nullptr)
    { 
        XOutStringTab::pins()->insert_out_string(ods, debug_info.process);
    }

    return DBG_CONTINUE;
}

DWORD XDebugControl::irp_event(tagDebugInfo& debug_info)
{ 
    //没有有用的信息
    return DBG_CONTINUE;
} 
 

void XDebugControl::user_control(tagDebugInfo& debug_info, XString& command, DWORD& next_address)
{
    std::list<DECODEING_ASM> asm_tab;
    bool ok = XDecodingASM::pins()->decoding_asm(
        debug_info.process,
        debug_info.context.Eip,
        this->count,
        asm_tab);
    if (ok)
    {
        this->f_out(debug_info.context, asm_tab); 
        this->f_in(command);

        if (asm_tab.size())
        {
            std::list<DECODEING_ASM>::iterator it = asm_tab.begin();
            ++it;
            next_address = it->address;
        }
    }

    asm_tab.clear();
}

void XDebugControl::command_explanation(XString& command, tagDebugInfo& debug_info, DWORD next_address)
{
    XCommandMgr::pins()->command_call_back(command, debug_info.context, next_address);
}