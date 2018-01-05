#pragma once
#include "XPJCoreHead.h"
#include <vector> 
#include "XThread.h"

class XThreadTab
{
private:
    XThreadTab();
    ~XThreadTab();

public:
    static XThreadTab* m_This;
    static XThreadTab* pins();

    void insert_thread(CREATE_THREAD_DEBUG_INFO* pti);

    bool get_thread_table(std::vector<THREAD_DATA>& tab);

    bool get_thread_data(int pos, CREATE_THREAD_DEBUG_INFO& data);

private:
    std::vector<CREATE_THREAD_DEBUG_INFO> thread_tab;
};

