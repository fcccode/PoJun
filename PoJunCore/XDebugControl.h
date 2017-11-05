#pragma once 
#include "XPublicHead.h"
    
class XEXP XDebugControl
{
public:
    XDebugControl();
    ~XDebugControl();

    static XDebugControl* m_This;
    static XDebugControl* pins();

    void start_debug_loop(XString& file_path, pfun_in_fun in_fun, pfun_out_fun out_fun);

    DWORD e_acess_violation(tagDebugInfo& debug_info);

    DWORD e_break_point(tagDebugInfo& debug_info);

    DWORD e_single_step(tagDebugInfo& debug_info);

    DWORD create_process_debug_event(tagDebugInfo& debug_info);

    DWORD create_thread_debug_event(tagDebugInfo& debug_info);

    DWORD exit_thread_debug_event(tagDebugInfo& debug_info);

    DWORD exit_process_debug_event(tagDebugInfo& debug_info);

    DWORD load_dll_debug_event(tagDebugInfo& debug_info);

    DWORD unload_dll_debug_event(tagDebugInfo& debug_info);

    DWORD output_debug_string_event(tagDebugInfo& debug_info);

    DWORD irp_event(tagDebugInfo& debug_info); 
};

