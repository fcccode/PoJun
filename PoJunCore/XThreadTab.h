#pragma once
#include "XPublicHead.h"
#include <vector> 

class XThreadTab
{
public:
    XThreadTab();
    ~XThreadTab();

    static XThreadTab* m_This;
    static XThreadTab* pins();

    void insert_thread(CREATE_THREAD_DEBUG_INFO* pti);

private:
    std::vector<CREATE_THREAD_DEBUG_INFO> thread_tab;
};

