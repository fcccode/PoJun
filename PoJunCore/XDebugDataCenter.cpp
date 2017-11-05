#include "stdafx.h"
#include "XDebugDataCenter.h"
#include "XBreakPoint.h"
#include "XInt3Tab.h"
#include "XThreadTab.h"
#include "XModelTab.h"   
#include "XOutStringTab.h"


XDebugDataCenter* XDebugDataCenter::m_This = 0;
XDebugDataCenter::XDebugDataCenter()
{ 
} 

XDebugDataCenter::~XDebugDataCenter()
{
}
 
XDebugDataCenter* XDebugDataCenter::pins()
{
    if (m_This == nullptr)
    {
        m_This = new XDebugDataCenter;
    }

    return m_This;
}

void XDebugDataCenter::set_file_path(XString& file_path)
{
    this->file_path = file_path;
}

void XDebugDataCenter::break_point(EXCEPTION_RECORD* ed, tagDebugInfo& debug_info)
{
    XBreakPoint::pins()->break_point(ed, debug_info);
}

void XDebugDataCenter::create_process(CREATE_PROCESS_DEBUG_INFO* cp, HANDLE process)
{
    XInt3Tab::pins()->create_process(cp, process);
}

void XDebugDataCenter::insert_dll(LOAD_DLL_DEBUG_INFO *load_dll)
{ 
    XModelTab::pins()->insert_dll(load_dll);
}

void XDebugDataCenter::remove_dll(UNLOAD_DLL_DEBUG_INFO* unload_dll)
{
    XModelTab::pins()->remove_dll((DWORD)unload_dll->lpBaseOfDll);
}
 
void XDebugDataCenter::insert_thread(CREATE_THREAD_DEBUG_INFO* tdi)
{
    XThreadTab::pins()->insert_thread(tdi);
}
 
void XDebugDataCenter::insert_out_string(OUTPUT_DEBUG_STRING_INFO* os, HANDLE process)
{
    XOutStringTab::pins()->insert_out_string(os, process);
}