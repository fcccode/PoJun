#pragma once
#include <windows.h>

class XDebugProcessInfo
{
private:
    XDebugProcessInfo();
    ~XDebugProcessInfo();

public:
    static XDebugProcessInfo* m_This;
    static XDebugProcessInfo* pins();

    void set_process_handle_id(HANDLE process, DWORD pid);
    HANDLE get_process_handle();
    DWORD get_process_pid();

    void set_thread_handle_id(HANDLE thread, DWORD tid);
    HANDLE get_thread_handle();
      
private:
    HANDLE process;
    HANDLE thread;
    DWORD pid;
    DWORD tid;
};

