#include "stdafx.h"
#include "XInt3Tab.h"


XInt3Tab* XInt3Tab::m_This = 0;
XInt3Tab::XInt3Tab()
{
    this->start_oep = 0; 
    this->int3 = 0xCC;
    this->opcode = 0;
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

    DWORD opcode = 0;
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

bool XInt3Tab::is_my_cc(tagDebugInfo& debug_info)
{ 
    std::map<DWORD, BYTE>::iterator it = this->cc_table.find(--debug_info.context.Eip);
    if (it != this->cc_table.end())
    {
        BOOL bRet = ::WriteProcessMemory(
            debug_info.process, 
            (LPVOID)it->first,
            (LPVOID)it->second, 
            1, 
            NULL);
        if (bRet == FALSE)
        {
            XGlobal::show_api_err();
        }
    }

    return true;
}