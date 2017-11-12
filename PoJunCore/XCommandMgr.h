#pragma once
#include "XPCoreHead.h" 
#include <map>
 

class XCommandMgr
{
public:
    XCommandMgr();
    ~XCommandMgr();

    static XCommandMgr* m_This;
    static XCommandMgr* pins();

    bool insert(const XString& command, pfun_command_call_back call_back);

    bool command_call_back(const XString& command, const CONTEXT& context, DWORD next_address);
     
public:
    //调试指令
    static bool __stdcall p_command(const XString& command, const CONTEXT& context, DWORD next_address);
    static bool __stdcall t_command(const XString& command, const CONTEXT& context, DWORD next_address);
    static bool __stdcall g_command(const XString& command, const CONTEXT& context, DWORD next_address);

    //数据显示指令

    //断点指令

    //记录指令

private:
    std::map<XString, pfun_command_call_back> comm_mgr;
};

