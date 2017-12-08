#include "stdafx.h"
#include "XCommandMgr.h" 
#include "XInt3Tab.h"
#include "XHardwareBreak.h"
#include "XDecodingASM.h"
#include "XMemoryMgr.h"
#include "XModelTab.h"
#include "XThreadTab.h" 
#include "XStackData.h"
#include "XDebugProcessInfo.h"

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
     
    insert(L"bm", XCommandMgr::bm_command);
    insert(L"bml", XCommandMgr::bml_command);
    insert(L"bmc", XCommandMgr::bmc_command);
     
    insert(L"u", XCommandMgr::u_command);
    insert(L"r", XCommandMgr::r_command);
    insert(L"lm", XCommandMgr::lm_command);
    insert(L"~", XCommandMgr::thread_command);
    insert(L"k", XCommandMgr::k_command);

    insert(L"db", XCommandMgr::db_command);
    insert(L"dw", XCommandMgr::dw_command);
    insert(L"dd", XCommandMgr::dd_command);
    insert(L"dq", XCommandMgr::dq_command);

    insert(L"eb", XCommandMgr::eb_command);
    insert(L"ew", XCommandMgr::ew_command);
    insert(L"ed", XCommandMgr::ed_command);
    insert(L"ea", XCommandMgr::ea_command);
    insert(L"eu", XCommandMgr::eu_command);
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

bool XCommandMgr::command_call_back(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{ 
    if (command.empty())
    {
        return false;
    }

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

bool __stdcall XCommandMgr::t_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_T;
    //…Ë÷√EFlage±Í÷æ
    XCommandMgr::pins()->single_step = true;
    debug_info.context.EFlags |= 0x100;
    return true;
}

bool __stdcall XCommandMgr::p_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_P;
    if (opcode_info.current_opcode == E_CALL_E8 
        || opcode_info.current_opcode == E_CALL_FF
        || opcode_info.current_opcode == E_REP
        || opcode_info.current_opcode == E_REPNE)
    {
        XCommandMgr::pins()->single_step = false;
        XInt3Tab::pins()->insert_p_single_step(debug_info.process, opcode_info.next_address);
    }
    else
    {
        XCommandMgr::pins()->single_step = true;
        debug_info.context.EFlags |= 0x100;
    } 

    return true;
} 

bool __stdcall XCommandMgr::g_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_G;
    std::vector<XString> vt_command;
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 2))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }
    
    std::vector<XString>::iterator it = vt_command.begin();
    it++;
       
    return XInt3Tab::pins()->insert_p_single_step(debug_info.process, it->to_int_0x());
}

bool XCommandMgr::is_single_step()
{
    return this->single_step;
} 

bool __stdcall XCommandMgr::bp_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_BP;
    std::vector<XString> vt_command;
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 2))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }

    std::vector<XString>::iterator it = vt_command.begin();
    it++;
     
    return XInt3Tab::pins()->insert_cc(debug_info.process, it->to_int_0x());
}

bool __stdcall XCommandMgr::bpl_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_BPL;
    return XInt3Tab::pins()->get_cc_table(out_module_data.break_point_tab);
}

bool __stdcall XCommandMgr::bpc_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_BPC;
    std::vector<XString> vt_command;
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 2))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }

    std::vector<XString>::iterator it = vt_command.begin();
    it++;
     
    return XInt3Tab::pins()->delete_cc_inedx(it->to_int());
}

bool __stdcall XCommandMgr::bh_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_BH;

    std::vector<XString> vt_command; 
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 4))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    } 
     
    return XHardwareBreak::pins()->insert(vt_command, debug_info.context);
}

bool __stdcall XCommandMgr::bhl_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_BHL; 
    return XHardwareBreak::pins()->get_hardware_break_table(out_module_data.hard_dware_break_tab);
}

bool __stdcall XCommandMgr::bhc_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_BHC;

    std::vector<XString> vt_command;
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 2))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }

    std::vector<XString>::iterator it = vt_command.begin();
    it++;
      
    return XHardwareBreak::pins()->delete_hardware_break_inedx(debug_info.context, it->to_int());
}

bool __stdcall XCommandMgr::bm_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_BM;

    std::vector<XString> vt_command;
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 4))
    { 
        return false;
    }

    vt_command.erase(vt_command.begin());
    std::vector<XString>::iterator it = vt_command.begin();
    DWORD address = it->to_int_0x();
    it++;

    DWORD length = it->to_int_0x();
    it++;

    bool rw = false;
    if (*it == L"r")
    {
        rw = false;
    }
    else if (*it == L"w")
    {
        rw = true;
    }
    else
    {
        return false;
    }
     
    return XMemoryMgr::pins()->insert_break_point(debug_info.process, address, length, rw);
}

bool __stdcall XCommandMgr::bml_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_BML;
    return XMemoryMgr::pins()->get_memory_table(out_module_data.memory_break_tab);
}

bool __stdcall XCommandMgr::bmc_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_BML;

    std::vector<XString> vt_command;
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 2))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }

    std::vector<XString>::iterator it = vt_command.begin();
    it++;

    return XMemoryMgr::pins()->delete_memory_break_point_inedx(debug_info.process, it->to_int());
}

bool __stdcall XCommandMgr::u_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_U;

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
    if (vt_command.size() >= 3)
    { 
        it++; 
        count = it->to_int();
    } 
        
    return XDecodingASM::pins()->decoding_asm(debug_info.process, address, count, out_module_data.asm_table);
}

bool __stdcall XCommandMgr::r_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_R;

    //±£¡Ù∏√÷∏¡Ó
    return true;
}

bool __stdcall XCommandMgr::lm_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_LM;

    return XModelTab::pins()->get_module_table(out_module_data.module_table);
}

bool __stdcall XCommandMgr::thread_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_THREAD; 

    std::vector<XString> vt_command;
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 1))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }

    if (vt_command.size() == 1)
    {
        return XThreadTab::pins()->get_thread_table(out_module_data.thread_table);
    }

    if (vt_command.size() != 3)
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }

    vt_command.erase(vt_command.begin());
    std::vector<XString>::iterator it = vt_command.begin();
    int inedx = it->to_int(); 
    vt_command.erase(vt_command.begin());
    it = vt_command.begin();

    if (!it->compare(L"k") == 0)
    {
        return false;
    }

    CREATE_THREAD_DEBUG_INFO data; 
    if (!XThreadTab::pins()->get_thread_data(inedx, data))
    {
        return false;
    }

    return XStackData::get_thread_stack_data(data.hThread, debug_info.context, out_module_data.stack_table);
}
   
bool XCommandMgr::k_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{    
    return XStackData::get_thread_stack_data(debug_info.thread, debug_info.context, out_module_data.stack_table);
}

bool __stdcall XCommandMgr::db_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_DB;

    std::vector<XString> vt_command;
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 1))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }

    DWORD address = debug_info.context.Eip;
    DWORD size = D_ROW * D_COL;
    XCommandMgr::pins()->get_d_row_address(vt_command, address, size);
       
    out_module_data.d_memory.type = DME_BYTE;
    return XMemoryMgr::pins()->read_memory(
        debug_info.process,
        address,
        (LPVOID*)&out_module_data.d_memory.memory_byte,
        size);
}

bool __stdcall XCommandMgr::dw_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_DW;

    std::vector<XString> vt_command;
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 1))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }

    DWORD address = debug_info.context.Eip;
    DWORD size = D_ROW * D_COL;
    XCommandMgr::pins()->get_d_row_address(vt_command, address, size);
      
    out_module_data.d_memory.type = DME_WORD;
    return XMemoryMgr::pins()->read_memory(
        debug_info.process,
        address,
        (LPVOID*)&out_module_data.d_memory.memory_word,
        size);
}

bool __stdcall XCommandMgr::dd_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_DD;

    std::vector<XString> vt_command;
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 1))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }

    DWORD address = debug_info.context.Eip;
    DWORD size = D_ROW * D_COL;
    XCommandMgr::pins()->get_d_row_address(vt_command, address, size);
       
    out_module_data.d_memory.type = DME_DWORD;
    return XMemoryMgr::pins()->read_memory(
        debug_info.process, 
        address, 
        (LPVOID*)&out_module_data.d_memory.memory_dword,
        size);
}

bool __stdcall XCommandMgr::dq_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_DQ; 
    return true;
}

bool __stdcall XCommandMgr::eb_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_EB;

    std::vector<XString> vt_command;
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 3))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }
      
    DWORD address = 0; 
    XCommandMgr::pins()->get_e_address(vt_command, address);
     
    BYTE* buffer = nullptr;
    if (!XCommandMgr::pins()->str2type<BYTE>(&buffer, vt_command))
    {
        return false;
    }

    XMemoryMgr::pins()->write_memory(debug_info.process, address, buffer, vt_command.size() * sizeof(BYTE));
    delete[] buffer;
    return true;
}

bool __stdcall XCommandMgr::ew_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_EW;

    std::vector<XString> vt_command;
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 3))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }

    DWORD address = 0;
    XCommandMgr::pins()->get_e_address(vt_command, address);
     
    WORD* buffer = nullptr;
    if (!XCommandMgr::pins()->str2type<WORD>(&buffer, vt_command))
    {
        return false;
    }

    XMemoryMgr::pins()->write_memory(debug_info.process, address, buffer, vt_command.size() * sizeof(WORD));
    delete[] buffer;
    return true;
}

bool __stdcall XCommandMgr::ed_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_ED;

    std::vector<XString> vt_command;
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 3))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }

    DWORD address = 0;
    XCommandMgr::pins()->get_e_address(vt_command, address);
      
    DWORD* buffer = nullptr;
    if (!XCommandMgr::pins()->str2type<DWORD>(&buffer, vt_command))
    {
        return false;
    }

    XMemoryMgr::pins()->write_memory(debug_info.process, address, buffer, vt_command.size() * sizeof(DWORD));
    delete[] buffer;
    return true;
}

bool __stdcall XCommandMgr::ea_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_EA;

    std::vector<XString> vt_command;
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 3))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }

    DWORD address = 0;
    XCommandMgr::pins()->get_e_address(vt_command, address); 
    
    XString str;
    str.vtx2str(vt_command, L" ");
     
    return XMemoryMgr::pins()->write_memory(
        debug_info.process, 
        address, 
        str.get_str().c_str(), 
        str.get_str().length());
}

bool __stdcall XCommandMgr::eu_command(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data)
{
    out_module_data.type = D_EU;

    std::vector<XString> vt_command;
    if (!XCommandMgr::pins()->get_vt_command(command, vt_command, 3))
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }

    DWORD address = 0;
    XCommandMgr::pins()->get_e_address(vt_command, address);
    
    XString str;
    str.vtx2str(vt_command, L" "); 
    return XMemoryMgr::pins()->write_memory(debug_info.process, address, str.w_cstr(), str.length());
}


bool XCommandMgr::get_vt_command(const XString& command, std::vector<XString>& vt_command, int min)
{
    XString str_command = command;
    str_command.get_vt_str_seg(vt_command, L" ");
    if (vt_command.size() < (std::vector<XString>::size_type)min)
    {
        //√¸¡Ó¥ÌŒÛ£¨÷±Ω”∑…
        return false;
    }

    return true;
}

bool XCommandMgr::get_d_row_address(std::vector<XString>& vt, DWORD& address, DWORD& size)
{ 
    if (vt.size() > 1)
    {
        std::vector<XString>::iterator it = vt.begin();
        it++;

        address = it->to_int_0x();

        it++;
        if (it != vt.end())
        {
            size = it->to_int();
        } 
    }

    return true;
}

template<typename T>
bool XCommandMgr::str2type(T** buf, std::vector<XString>& vt)
{
    *buf = new T[vt.size()];
    if (*buf == nullptr)
    {
        return false;
    }

    int i = 0;
    std::vector<XString>::iterator it = vt.begin();
    for (it; it != vt.end(); it++, i++)
    {
        (*buf)[i] = it->to_int_0x();
    } 

    return true;
}

bool XCommandMgr::get_e_address(std::vector<XString>& vt, DWORD& address)
{
    vt.erase(vt.begin());
    std::vector<XString>::iterator it = vt.begin();
    address = it->to_int_0x();
    vt.erase(it);

    return true;
}