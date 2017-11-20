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
        调试指令
    */
    //单步过
    static bool __stdcall t_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info);
    //步步过
    static bool __stdcall p_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info);
    //运行
    static bool __stdcall g_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info);
    //是否是单步指令，如果是call返回false
    bool is_single_step();

    /* 
        数据显示指令
    */

    /*
        断点指令
    */

    /*
        记录指令
    */

private:
    std::map<XString, pfun_command_call_back> comm_mgr;

    bool single_step;
};

