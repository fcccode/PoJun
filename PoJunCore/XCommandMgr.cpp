#include "stdafx.h"
#include "XCommandMgr.h"
#include "XBreakPoint.h"
#include "XDecodingASM.h"
#include "XMemoryMgr.h"
 
XCommandMgr* XCommandMgr::m_This = nullptr;
XCommandMgr::XCommandMgr()
{
    insert(L"t", XCommandMgr::t_command);
    insert(L"p", XCommandMgr::p_command); 
    insert(L"g", XCommandMgr::g_command);

    insert(L"bp", XCommandMgr::bp_command);
    insert(L"bpl", XCommandMgr::bpl_command);
    insert(L"bpc", XCommandMgr::bpc_command);

    insert(L"bh", XCommandMgr::bh_command);
    insert(L"bhl", XCommandMgr::bhl_command);
    insert(L"bhc", XCommandMgr::bhc_command);
     
    insert(L"u", XCommandMgr::u_command);

    insert(L"db", XCommandMgr::db_command);
    insert(L"dw", XCommandMgr::dw_command);
    insert(L"dd", XCommandMgr::dd_command);
    insert(L"dq", XCommandMgr::dq_command);
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
    //…Ë÷√EFlage±Í÷æ
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
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 2))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
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
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 2))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
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
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 2))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }

    std::vector<XString>::iterator it = vt_command.begin();
    it++;

    XBreakPoint::pins()->delete_cc_inedx(it->to_int());
    return true; 
}

bool __stdcall XCommandMgr::bh_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    std::vector<XString> vt_command; 
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 4))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }
     
    XBreakPoint::pins()->insert_hard_break(vt_command, debug_info.context); 
    return true;
}

bool __stdcall XCommandMgr::bhl_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    XBreakPoint::pins()->get_hard_ware_break_tab(out_module_data.hard_dware_break_tab);
    return true;
}

bool __stdcall XCommandMgr::bhc_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{ 
    std::vector<XString> vt_command;
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 2))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }

    std::vector<XString>::iterator it = vt_command.begin();
    it++;
     
    XBreakPoint::pins()->delete_hard_ware_break_inedx(debug_info.context, it->to_int());
    return true;
}
 
bool __stdcall XCommandMgr::u_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    std::vector<XString> vt_command;
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 2))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }

    std::vector<XString>::iterator it = vt_command.begin();
    it++;

    DWORD address = it->to_int_0x();
    DWORD count = 8;
    if (vt_command.size() == 3)
    { 
        it++; 
        count = it->to_int();
    } 
       
    XDecodingASM::pins()->decoding_asm(debug_info.process, address, count, out_module_data.asm_table);
    return true;
}

bool __stdcall XCommandMgr::db_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    std::vector<XString> vt_command;
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 1))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }

    DWORD address = debug_info.context.Eip;
    DWORD row = 8;

    XCommandMgr::pins()->get_d_row_address(vt_command, address, row);
     
    XString mem_data;
    XMemoryMgr::pins()->get_memort_byte(debug_info.process, address, row, mem_data);
    MessageBox(nullptr, mem_data.w_cstr(), nullptr, MB_OK);
    return true;
}

bool __stdcall XCommandMgr::dw_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    std::vector<XString> vt_command;
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 1))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }

    DWORD address = debug_info.context.Eip;
    DWORD row = 8;

    XCommandMgr::pins()->get_d_row_address(vt_command, address, row);

    XString mem_data;
    XMemoryMgr::pins()->get_memort_word(debug_info.process, address, row, mem_data);
    MessageBox(nullptr, mem_data.w_cstr(), nullptr, MB_OK);
    return true;
}

bool __stdcall XCommandMgr::dd_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    std::vector<XString> vt_command;
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 1))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }

    DWORD address = debug_info.context.Eip;
    DWORD row = 8;

    XCommandMgr::pins()->get_d_row_address(vt_command, address, row);

    XString mem_data;
    XMemoryMgr::pins()->get_memort_dword(debug_info.process, address, row, mem_data);
    MessageBox(nullptr, mem_data.w_cstr(), nullptr, MB_OK);
    return true;
}

bool __stdcall XCommandMgr::dq_command(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    return true;
}

bool XCommandMgr::get_vt_command(const XString& command, std::vector<XString>& vt_command, int min)
{
    XString str_command = command;
    str_command.get_vt_str_seg(vt_command, L" ");
    if (vt_command.size() < min)
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }

    return true;
}

bool XCommandMgr::get_d_row_address(std::vector<XString>& vt, DWORD& address, DWORD& row)
{ 
    if (vt.size() > 1)
    {
        std::vector<XString>::iterator it = vt.begin();
        it++;

        address = it->to_int_0x();

        it++;
        if (it != vt.end())
        {
            row = it->to_int();
        }
    }

    return true;
}