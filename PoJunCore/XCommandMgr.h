#pragma once
#include "XPublicHead.h" 
#include <map>

class XCommandMgr
{
public:
    XCommandMgr();
    ~XCommandMgr();

    static XCommandMgr* m_This;
    static XCommandMgr* pins();

    std::map<int, int> a;
};

