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

    bool command_call_back(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
     
public:
    /*
        ����ָ��
    */
    //������
    static bool __stdcall t_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //������
    static bool __stdcall p_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //����
    static bool __stdcall g_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //�Ƿ��ǵ���ָ������call����false
    bool is_single_step();

    /*
        �ϵ�ָ��
    */
    //����CC�ϵ�
    static bool __stdcall bp_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //�鿴CC�ϵ��б�
    static bool __stdcall bpl_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //ɾ��CCĳ���ϵ�
    static bool __stdcall bpc_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);

    //����Ӳ���ϵ�
    static bool __stdcall bh_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //�鿴Ӳ���ϵ�
    static bool __stdcall bhl_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //ɾ��Ӳ���ϵ�
    static bool __stdcall bhc_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    
    /* 
        ������ʾָ��
    */
    static bool __stdcall u_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);

      
    /*
        ��¼ָ��
    */

private:
    bool get_vt_command(const XString& str_command, std::vector<XString>& vt_command, int min);

private:
    std::map<XString, pfun_command_call_back> comm_mgr;

    //����ָ����Ҫʹ��
    bool single_step;
};

