#pragma once
#include "XPJCoreHead.h" 
#include <map>
 
enum OPCODE
{
    E_CALL_E8 = 0xE8,
    E_CALL_FF = 0xFF,
    E_REP = 0xF3,
    E_REPNE = 0xF2
};

class XCommandMgr
{
private:
    XCommandMgr();
    ~XCommandMgr();

public:
    static XCommandMgr* m_This;
    static XCommandMgr* pins();

    bool insert(const XString& command, pfun_command_call_back call_back);

    bool command_call_back(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
     
public:
    /*
        ����ָ��
    */
    //������
    static bool __stdcall t_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //������
    static bool __stdcall p_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //����
    static bool __stdcall g_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //�Ƿ��ǵ���ָ������call����false
    bool is_single_step(); 

    /*
        �ϵ�ָ��
    */
    //����CC�ϵ�
    static bool __stdcall bp_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //�鿴CC�ϵ��б�
    static bool __stdcall bpl_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //ɾ��CCĳ���ϵ�
    static bool __stdcall bpc_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);

    //����Ӳ���ϵ�
    static bool __stdcall bh_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //�鿴Ӳ���ϵ�
    static bool __stdcall bhl_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //ɾ��Ӳ���ϵ�
    static bool __stdcall bhc_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    
    //�����ڴ�ϵ�
    static bool __stdcall bm_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //�鿴�ڴ�ϵ�
    static bool __stdcall bml_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //ɾ���ڴ�ϵ�
    static bool __stdcall bmc_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    
    /* 
        ������ʾָ��
    */

    //�����
    static bool __stdcall u_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //�Ĵ���
    static bool __stdcall r_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //ģ��
    static bool __stdcall lm_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //�߳� ~
    static bool __stdcall thread_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //k���鿴ջ
    static bool __stdcall k_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);

    //�ֽ���ʾ
     
    static bool __stdcall db_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    static bool __stdcall dw_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    static bool __stdcall dd_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    static bool __stdcall dq_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);

    static bool __stdcall eb_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    static bool __stdcall ew_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    static bool __stdcall ed_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    static bool __stdcall ea_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    static bool __stdcall eu_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
      
    //������ʾ 
     
    /*
        ��¼ָ��
    */

private:
    bool get_vt_command(const XString& str_command, std::vector<XString>& vt_command, int min);

    bool get_d_row_address(std::vector<XString>& vt, DWORD& address, DWORD& size);

    template<typename T>
    bool str2type(T** buf, std::vector<XString>& vt);

    bool get_e_address(std::vector<XString>& vt, DWORD& address);

private:
    std::map<XString, pfun_command_call_back> comm_mgr;

    //����ָ����Ҫʹ��
    bool single_step;
};

