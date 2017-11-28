#pragma once
#include "XPJCoreHead.h"
#include <vector> 

class XThreadTab
{
public:
    XThreadTab();
    ~XThreadTab();

    static XThreadTab* m_This;
    static XThreadTab* pins();

    void insert_thread(CREATE_THREAD_DEBUG_INFO* pti);

    bool get_thread_table(std::vector<CREATE_THREAD_DEBUG_INFO>& tab);

private:
    std::vector<CREATE_THREAD_DEBUG_INFO> thread_tab;
};

