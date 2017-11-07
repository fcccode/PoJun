#include "stdafx.h"
#include "XInt3Tab.h"


XInt3Tab* XInt3Tab::m_This = 0;
XInt3Tab::XInt3Tab()
{
    this->start_oep = 0; 
    this->int3 = 0xCC;
    this->start_opcode = 0;
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

    BYTE opcode = 0;
    BOOL bRet = ::ReadProcessMemory(
        process, 
        (LPCVOID)this->start_oep,
        (LPVOID)&opcode, 
        1, 
        NULL);
    if (bRet == FALSE)
    {
        XGlobal::show_api_err(); 
    }

    bRet = ::WriteProcessMemory(process, (LPVOID)this->start_oep,
        (LPVOID)&this->int3, 1, NULL);
    if (bRet == FALSE)
    {
        XGlobal::show_api_err(); 
    }
     
    this->start_opcode = opcode;
}

bool XInt3Tab::is_start_opcode(DWORD opcode)
{
    if (opcode == this->start_opcode)
    {
        return true;
    }

    return false;
}

bool XInt3Tab::reduction_oep(HANDLE handle)
{
    BYTE opcode = 0;
    return set_opcode(handle, this->start_opcode, this->start_opcode, opcode);
}
 
bool XInt3Tab::insert_cc(HANDLE handle, DWORD address)
{
    BYTE opcode = 0;
    bool status = set_opcode(handle, address, this->int3, opcode);
    if (status)
    {
        this->cc_table.insert(std::pair<DWORD, BYTE>(address, opcode));
    } 
    return status;
}

bool XInt3Tab::remove_cc(HANDLE handle, DWORD address)
{
    std::map<DWORD, BYTE>::iterator it = this->cc_table.find(address);
    if (it == this->cc_table.end())
    {
        return true;
    }

    BYTE opcode = 0;
    bool status = set_opcode(handle, address, it->second, opcode);
    if (status)
    {
        this->cc_table.erase(it);
    }
     
    return status;
}

bool XInt3Tab::is_my_cc(HANDLE handle, DWORD address)
{ 
    std::map<DWORD, BYTE>::iterator it = this->cc_table.find(address);
    if (it != this->cc_table.end())
    { 
        return true;
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