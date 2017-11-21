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
        调试指令
    */
    //单步过
    static bool __stdcall t_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //步步过
    static bool __stdcall p_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //运行
    static bool __stdcall g_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //是否是单步指令，如果是call返回false
    bool is_single_step();

    /*
        断点指令
    */
    //设置CC断点
    static bool __stdcall bp_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //查看CC断点列表
    static bool __stdcall bpl_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //删除CC某个断点
    static bool __stdcall bpc_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);

    //设置硬件断点
    static bool __stdcall bh_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //查看硬件断点
    static bool __stdcall bhl_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    //删除硬件断点
    static bool __stdcall bhc_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
    
    /* 
        数据显示指令
    */
    static bool __stdcall u_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);

      
    /*
        记录指令
    */

private:
    bool get_vt_command(const XString& str_command, std::vector<XString>& vt_command, int min);

private:
    std::map<XString, pfun_command_call_back> comm_mgr;

    //调试指令需要使用
    bool single_step;
};

