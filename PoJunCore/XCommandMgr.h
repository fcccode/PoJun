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
    //����ָ��
    static bool __stdcall p_command(const XString& command, const CONTEXT& context, DWORD next_address);
    static bool __stdcall t_command(const XString& command, const CONTEXT& context, DWORD next_address);
    static bool __stdcall g_command(const XString& command, const CONTEXT& context, DWORD next_address);

    //������ʾָ��

    //�ϵ�ָ��

    //��¼ָ��

private:
    std::map<XString, pfun_command_call_back> comm_mgr;
};

