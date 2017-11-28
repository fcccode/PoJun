#include "stdafx.h"
#include "XInt3Tab.h"


XInt3Tab* XInt3Tab::m_This = 0;
XInt3Tab::XInt3Tab()
{
    this->start_oep = 0; 
    this->int3 = 0xCC;
    this->start_opcode = 0;
    reduction_address = 0;
}
 
XInt3Tab::~XInt3Tab()
{
}
 
XInt3Tab* XInt3Tab::pins()
{
    if (m_This == 0)
    {
        m_This = new XInt3Tab;
    }

    return m_This;
}

void XInt3Tab::create_process(CREATE_PROCESS_DEBUG_INFO* cp, HANDLE process)
{
    this->start_oep = (DWORD)*cp->lpStartAddress;  
    bool ret = set_opcode(process, this->start_oep, this->int3, this->start_opcode);
    if (!ret)
    { 
        XGlobal::show_api_err();
    }
}

bool XInt3Tab::is_start_opcode(DWORD opcode)
{
    if (opcode == this->start_oep)
    {
        return true;
    }

    return false;
}

bool XInt3Tab::reduction_oep(HANDLE handle)
{
    BYTE opcode = 0;
    return set_opcode(handle, this->start_oep, this->start_opcode, opcode);
}

bool XInt3Tab::reduction_cc(HANDLE handle, DWORD address, bool status)
{
    std::map<DWORD, CC_BREAK_POINT>::iterator it = this->cc_table.find(address);
    if (it == cc_table.end())
    {
        return false;
    }
     
    BYTE opcode = 0;
    if (status)
    {
        return set_opcode(handle, address, this->int3, opcode);
    } 
    else
    {
        return set_opcode(handle, address, it->second.opcode, opcode); 
    }
}

bool XInt3Tab::set_reduction_single_step(CONTEXT& context)
{ 
    this->reduction_address = context.Eip;
    context.EFlags |= 0x100;
    return true;
}
  
DWORD XInt3Tab::get_reduction_single_step()
{
    DWORD address = this->reduction_address;
    this->reduction_address = 0;
    return address;
}

bool XInt3Tab::insert_cc(HANDLE handle, DWORD address)
{
    BYTE opcode = 0;
    bool status = set_opcode(handle, address, this->int3, opcode);
    if (status)
    {
        CC_BREAK_POINT cbp;
        cbp.opcode = opcode;
        cbp.activation = true;
        cbp.number = -1;

        for (std::map<DWORD, CC_BREAK_POINT>::size_type i = 0; 
            i < this->cc_table.size() + 1; 
            i++)
        {
            std::vector<int>::iterator it = std::find(cc_table_num_mgr.begin(), cc_table_num_mgr.end(), i);
            if (it == cc_table_num_mgr.end())
            {
                cbp.number = i;
                cc_table_num_mgr.push_back(i);
                break;
            }
        }

        if (cbp.number == -1)
        {
            cbp.number = this->cc_table.size() + 1;
        }

        this->cc_table.insert(std::pair<DWORD, CC_BREAK_POINT>(address, cbp));
    } 
    return status;
}

bool XInt3Tab::remove_cc(HANDLE handle, DWORD address)
{
    std::map<DWORD, CC_BREAK_POINT>::iterator it = this->cc_table.find(address);
    if (it == this->cc_table.end())
    {
        return true;
    }

    BYTE opcode = 0;
    bool status = set_opcode(handle, address, it->second.opcode, opcode);
    if (status)
    {
        this->cc_table.erase(it);
    }
     
    return status;
}

bool XInt3Tab::is_my_cc(HANDLE handle, DWORD address)
{ 
    std::map<DWORD, CC_BREAK_POINT>::iterator it = this->cc_table.find(address);
    if (it != this->cc_table.end())
    { 
        return true;
    }

    return false;
} 

bool XInt3Tab::set_cc_status(int inedx, bool status)
{
    std::map<DWORD, CC_BREAK_POINT>::iterator it = this->cc_table.begin();
    for (it; it != this->cc_table.end(); it++)
    {
        if (it->second.number == inedx)
        {
            it->second.activation = status;
            return true;
        }
    }

    return false;
}

bool XInt3Tab::get_cc_table(std::map<DWORD, CC_BREAK_POINT>& out_map)
{
    out_map = this->cc_table;
    return true;
}
 
bool XInt3Tab::delete_cc_inedx(int inedx)
{
    std::map<DWORD, CC_BREAK_POINT>::iterator it = this->cc_table.begin();
    for (it; it != this->cc_table.end(); it++)
    {
        if (it->second.number == inedx)
        {
            std::vector<int>::iterator nit = std::find(
                this->cc_table_num_mgr.begin(), 
                this->cc_table_num_mgr.end(), inedx);
            if (nit != this->cc_table_num_mgr.end())
            {
                this->cc_table_num_mgr.erase(nit);
            }

            this->cc_table.erase(it);
            return true;
        }
    }

    return false;
}

bool XInt3Tab::insert_p_single_step(HANDLE handle, DWORD address)
{
    BYTE opcode = 0;
    bool status = set_opcode(handle, address, this->int3, opcode);
    if (status)
    {
        this->single_step_table.insert(std::pair<DWORD, BYTE>(address, opcode));
    }
    return status;
}

bool XInt3Tab::is_p_single_step(HANDLE handle, DWORD address)
{
    std::map<DWORD, BYTE>::iterator it = this->single_step_table.find(address);
    if (it != this->single_step_table.end())
    {
        //单步表触发当前单步后直接移除
        BYTE opcode = 0;
        bool status = set_opcode(handle, address, it->second, opcode);
        if (status)
        {
            this->single_step_table.erase(it);
        }
        return status;
    }

    return false;
}

bool XInt3Tab::set_opcode(HANDLE handle, DWORD address, BYTE& i_opcode, BYTE& o_opcode)
{ 
    BOOL status = ::ReadProcessMemory(handle, (LPCVOID)address, (LPVOID)&o_opcode, 1, NULL);
    if (!status)
    {
        return false;
    }

    status = ::WriteProcessMemory(handle, (LPVOID)address, (LPVOID)&i_opcode, 1, NULL);
    if (!status)
    {
        return false;
    }

    return true;
}