#pragma once 
#include "XPJCoreHead.h"
#include <list>

class XOutStringTab
{
public:
    XOutStringTab();
    ~XOutStringTab();

    static XOutStringTab* m_This;
    static XOutStringTab* pins();

    void insert_out_string(OUTPUT_DEBUG_STRING_INFO* os, HANDLE pcoess);

private:
    std::list<XString> out_string;
};

