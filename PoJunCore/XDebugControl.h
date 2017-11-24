#pragma once 
#include "XPCoreHead.h"
    
class XEXP XDebugControl
{
public:
    XDebugControl();
    ~XDebugControl();

    static XDebugControl* m_This;
    static XDebugControl* pins();

    void start_debug_loop(XString& file_path, pfun_in_fun in_fun, pfun_out_fun out_fun, pfun_command_call_back_out command_out, DWORD count);

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

private:
    void user_control(tagDebugInfo& debug_info);

    void command_explanation(XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);

    bool scan_command(XString& command);

private:
    XString file_path;

    DWORD teb;

    DWORD count;

    pfun_in_fun f_in;
    pfun_out_fun f_out;
    pfun_command_call_back_out f_command_out;
};

