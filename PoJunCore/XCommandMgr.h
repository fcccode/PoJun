#pragma once
#include "XPCoreHead.h" 
#include <map>
 
enum OPCODE
{
    E_CALL_E8 = 0xE8,
    E_CALL_FF = 0xFF
};

class XCommandMgr
{
public:
    XCommandMgr();
    ~XCommandMgr();

    static XCommandMgr* m_This;
    static XCommandMgr* pins();

    bool insert(const XString& command, pfun_command_call_back call_back);

    bool command_call_back(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info);
     
public:
    /*
        ����ָ��
    */
    //������
    static bool __stdcall t_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info);
    //������
    static bool __stdcall p_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info);
    //����
    static bool __stdcall g_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info);
    //�Ƿ��ǵ���ָ������call����false
    bool is_single_step();

    /* 
        ������ʾָ��
    */

    /*
        �ϵ�ָ��
    */

    /*
        ��¼ָ��
    */

private:
    std::map<XString, pfun_command_call_back> comm_mgr;

    bool single_step;
};

