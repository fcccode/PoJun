#include "stdafx.h"
#include "XDebugProcessInfo.h"
 
XDebugProcessInfo* XDebugProcessInfo::m_This = nullptr;
XDebugProcessInfo::XDebugProcessInfo()
{
}


XDebugProcessInfo::~XDebugProcessInfo()
{
}
 
XDebugProcessInfo* XDebugProcessInfo::pins()
{
    if (m_This == nullptr)
    {
        m_This = new XDebugProcessInfo;
    }

    return m_This;
}


void XDebugProcessInfo::set_process_handle_id(HANDLE process, DWORD pid)
{
    this->process = process;
    this->pid = pid;
}

HANDLE XDebugProcessInfo::get_process_handle()
{
    return this->process;
}

DWORD XDebugProcessInfo::get_process_pid()
{
    return this->pid;
}

void XDebugProcessInfo::set_thread_handle_id(HANDLE thread, DWORD tid)
{
    this->thread = thread;
    this->tid = tid;
}

HANDLE XDebugProcessInfo::get_thread_handle()
{
    return this->thread;
}