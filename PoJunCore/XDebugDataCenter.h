#pragma once
  
#include "XPublicHead.h" 
 
class XDebugDataCenter
{
public:
    XDebugDataCenter();
    ~XDebugDataCenter();

    static XDebugDataCenter* m_This;
    static XDebugDataCenter* pins();

    void set_file_path(XString& file_path); 

    void break_point(EXCEPTION_RECORD* ed, tagDebugInfo& debug_info);

    void create_process(CREATE_PROCESS_DEBUG_INFO* cp, HANDLE process);
      
    void insert_dll(LOAD_DLL_DEBUG_INFO *load_dll);

    void remove_dll(UNLOAD_DLL_DEBUG_INFO* unload_dll);
     
    void insert_thread(CREATE_THREAD_DEBUG_INFO* tdi);

    void insert_out_string(OUTPUT_DEBUG_STRING_INFO* os, HANDLE process);
     
private: 
    XString file_path; 
}; 