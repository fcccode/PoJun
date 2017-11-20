#include "stdafx.h"
#include "XCommandMgr.h"
#include "XBreakPoint.h"
 
XCommandMgr* XCommandMgr::m_This = nullptr;
XCommandMgr::XCommandMgr()
{
    insert(L"t", XCommandMgr::t_command);
    insert(L"p", XCommandMgr::p_command); 
    insert(L"g", XCommandMgr::g_command);

    insert(L"bp", XCommandMgr::bp_command);
    insert(L"bpl", XCommandMgr::bpl_command);
    insert(L"bpc", XCommandMgr::bpc_command);
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

bool XCommandMgr::command_call_back(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{ 
    std::vector<XString> vt_command;
    XString str_command = command;
    str_command.get_vt_str_seg(vt_command, L" ");
    XString command_head = *vt_command.begin();
     
    std::map<XString, pfun_command_call_back>::iterator it = this->comm_mgr.find(command_head);
    if (it == this->comm_mgr.end())
    {
        return false;
    }

    return it->second(command, debug_info, opcode_info, out_module_data);
}

bool __stdcall XCommandMgr::t_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = E_T;
    //设置EFlage标志
    XCommandMgr::pins()->single_step = true;
    debug_info.context.EFlags |= 0x100;
    return true;
}

bool __stdcall XCommandMgr::p_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = E_P;
    if (opcode_info.current_opcode == E_CALL_E8 
        || opcode_info.current_opcode == E_CALL_FF)
    {
        XCommandMgr::pins()->single_step = false;
        XBreakPoint::pins()->insert_single_step(debug_info.process, opcode_info.next_address);
    }
    else
    {
        XCommandMgr::pins()->single_step = true;
        debug_info.context.EFlags |= 0x100;
    } 

    return true;
} 

bool __stdcall XCommandMgr::g_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = E_G;
    std::vector<XString> vt_command;
    XString str_command = command;
    str_command.get_vt_str_seg(vt_command, L" "); 
    if (vt_command.size() != 2)
    {
        //默认直接飞
        return true;
    }
    
    std::vector<XString>::iterator it = vt_command.begin();
    it++;
      
    XBreakPoint::pins()->insert_single_step(debug_info.process, it->to_int_0x());
    return true;
}

bool XCommandMgr::is_single_step()
{
    return this->single_step;
}

bool __stdcall XCommandMgr::bp_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = E_BP;
    std::vector<XString> vt_command;
    XString str_command = command;
    str_command.get_vt_str_seg(vt_command, L" "); 
    if (vt_command.size() != 2)
    {
        //默认直接飞
        return true;
    }

    std::vector<XString>::iterator it = vt_command.begin();
    it++;

    XBreakPoint::pins()->insert_cc(debug_info.process, it->to_int_0x());
    return true; 
}

bool __stdcall XCommandMgr::bpl_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = E_BPL; 
    XBreakPoint::pins()->get_cc_table(out_module_data.break_point_tab);
    return true;
}

bool __stdcall XCommandMgr::bpc_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = E_BPC;
    std::vector<XString> vt_command;
    XString str_command = command;
    str_command.get_vt_str_seg(vt_command, L" "); 
    if (vt_command.size() != 2)
    {
        //命令错误，直接飞
        return true;
    }

    std::vector<XString>::iterator it = vt_command.begin();
    it++;

    XBreakPoint::pins()->delete_cc_inedx(it->to_int());
    return true; 
}