#include "stdafx.h"
#include "XThreadTab.h" 
#include "XDebugProcessInfo.h"
 
XThreadTab* XThreadTab::m_This = 0;
XThreadTab::XThreadTab()
{
    this->thread_tab.clear();
}

XThreadTab::~XThreadTab()
{
}
 
XThreadTab* XThreadTab::pins()
{
    if (m_This == 0)
    {
        m_This = new XThreadTab;
    }

    return m_This;
}

void XThreadTab::insert_thread(CREATE_THREAD_DEBUG_INFO* pti)
{
    CREATE_THREAD_DEBUG_INFO tab;
    tab.hThread = pti->hThread;
    tab.lpStartAddress = pti->lpStartAddress;
    tab.lpThreadLocalBase = pti->lpThreadLocalBase;

    this->thread_tab.push_back(tab);
}

bool XThreadTab::get_thread_table(std::vector<THREAD_DATA>& tab)
{
    //tab = this->thread_tab;
      
    return XThread::get_process_thread_table(
        XDebugProcessInfo::pins()->get_process_pid(),
        tab);
}

bool XThreadTab::get_thread_data(int pos, CREATE_THREAD_DEBUG_INFO& data)
{
    if (this->thread_tab.size() < pos || pos < 0)
    {
        return false;
    }

    data = this->thread_tab[pos];
    return true;
}