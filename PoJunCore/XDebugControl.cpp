#include "stdafx.h"
#include "XDebugControl.h" 
#include "XDebugDataCenter.h"
#include "XThreadTab.h"

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

void XDebugControl::start_debug_loop(XString& file_path, pfun_in_fun in_fun, pfun_out_fun out_fun)
{
    if (in_fun == nullptr || out_fun == nullptr)
    {
        return;
    }

    XDebugDataCenter::pins()->set_file_path(file_path);

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
        if (er == nullptr)
        {
            XDebugDataCenter::pins()->break_point(er, debug_info);
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
    CREATE_PROCESS_DEBUG_INFO *pCreateProcessDbgINOF 
        = (CREATE_PROCESS_DEBUG_INFO*)&debug_info.event.u.CreateProcessInfo;
    if (pCreateProcessDbgINOF != nullptr)
    {
        XDebugDataCenter::pins()->create_process(pCreateProcessDbgINOF, debug_info.process);
    }

    return DBG_CONTINUE;
}

DWORD XDebugControl::create_thread_debug_event(tagDebugInfo& debug_info)
{
    CREATE_THREAD_DEBUG_INFO *pCreateThreadDbgINOF 
        = (CREATE_THREAD_DEBUG_INFO*)&debug_info.event.u.CreateThread;
    if (pCreateThreadDbgINOF != nullptr)
    {
        XDebugDataCenter::pins()->insert_thread(pCreateThreadDbgINOF);
    }

    return DBG_CONTINUE;
}

DWORD XDebugControl::exit_thread_debug_event(tagDebugInfo& debug_info)
{ 
    //没有有用的信息，不搞。
    return DBG_CONTINUE;
}

DWORD XDebugControl::exit_process_debug_event(tagDebugInfo& debug_info)
{ 
    //没有有用的信息。 
    return DBG_CONTINUE;
}
 
DWORD XDebugControl::load_dll_debug_event(tagDebugInfo& debug_info)
{
    LOAD_DLL_DEBUG_INFO *load_dll 
        = (LOAD_DLL_DEBUG_INFO*)&debug_info.event.u.LoadDll;
    if (load_dll != nullptr)
    {
        XDebugDataCenter::pins()->insert_dll(load_dll);
    }
      
    return DBG_CONTINUE;
}

DWORD XDebugControl::unload_dll_debug_event(tagDebugInfo& debug_info)
{
    UNLOAD_DLL_DEBUG_INFO *unload_dll 
        = (UNLOAD_DLL_DEBUG_INFO*)&debug_info.event.u.UnloadDll;
    if (unload_dll != nullptr)
    {
        XDebugDataCenter::pins()->remove_dll(unload_dll);
    }
      
    return DBG_CONTINUE;
}

DWORD XDebugControl::output_debug_string_event(tagDebugInfo& debug_info)
{
    OUTPUT_DEBUG_STRING_INFO *pos 
        = (OUTPUT_DEBUG_STRING_INFO*)&debug_info.event.u.DebugString;
    if (pos != nullptr)
    {
        XDebugDataCenter::pins()->insert_out_string(pos, debug_info.process);
    }

    return DBG_CONTINUE;
}

DWORD XDebugControl::irp_event(tagDebugInfo& debug_info)
{ 
    //没有有用的信息
    return DBG_CONTINUE;
} 
 