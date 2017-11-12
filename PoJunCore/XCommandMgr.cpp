#include "stdafx.h"
#include "XCommandMgr.h"


XCommandMgr* XCommandMgr::m_This = nullptr;
XCommandMgr::XCommandMgr()
{
    insert(L"p", XCommandMgr::p_command);
    insert(L"t", XCommandMgr::t_command);
    insert(L"g", XCommandMgr::g_command);
}


XCommandMgr::~XCommandMgr()
{
}
 
XCommandMgr* XCommandMgr::pins()
{
    if (m_This == nullptr)
    {
        m_This = new XCommandMgr;
    }

    return m_This;
}

bool XCommandMgr::insert(const XString& command, pfun_command_call_back call_back)
{
    std::map<XString, pfun_command_call_back>::iterator it = this->comm_mgr.find(command);
    if (it != this->comm_mgr.end())
    {
        return false;
    }

    this->comm_mgr.insert(std::pair<XString, pfun_command_call_back>(command, call_back));
    return true;
}

bool XCommandMgr::command_call_back(const XString& command, const CONTEXT& context, DWORD next_address)
{
    std::map<XString, pfun_command_call_back>::iterator it = this->comm_mgr.find(command);
    if (it == this->comm_mgr.end())
    {
        return false;
    }

    return it->second(command, context, next_address);
}

bool __stdcall XCommandMgr::p_command(const XString& command, const CONTEXT& context, DWORD next_address)
{
    return true;
}

bool __stdcall XCommandMgr::t_command(const XString& command, const CONTEXT& context, DWORD next_address)
{
    return true;
}

bool __stdcall XCommandMgr::g_command(const XString& command, const CONTEXT& context, DWORD next_address)
{
    return true;
}
