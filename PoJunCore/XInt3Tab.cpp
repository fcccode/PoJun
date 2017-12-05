#include "stdafx.h"
#include "XInt3Tab.h" 
#include "XModelTab.h" 
#include "XSQLite3.h" 
#include <XModule.h>


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

    //插入进程模块
    MODULE_INFO mi;
    mi.handle = process;
    mi.base = PAGE_BASE((DWORD)cp->lpStartAddress);
    mi.enter = (DWORD)cp->lpStartAddress;  
    XModule::handle_to_path(cp->hFile, mi.file_path);
    mi.size = 0;
    mi.file_version = 0; 
    XModelTab::pins()->insert_exe(mi); 
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
        return set_opcode(handle, address, this->int3, it->second.opcode);
    } 
    else
    {
        return set_opcode(handle, address, it->second.opcode, opcode); 
    }
}

bool XInt3Tab::reduction_break_point(HANDLE process, const XString& file_name, DWORD address)
{
    DWORD base = PAGE_BASE(address);

    bool prompt = false;

    std::map<DWORD, CC_BREAK_POINT> old_table = this->cc_table; 
    std::map<DWORD, CC_BREAK_POINT>::iterator it = old_table.begin();
    for (it; it != old_table.end(); it++)
    {
        if (it->second.module_name != file_name)
        {
            continue;
        }

        CC_BREAK_POINT bp = it->second;
        
        DWORD bp_address = base + it->second.offset;
        if (!set_opcode(process, bp_address, this->int3, bp.opcode))
        {
            continue;
        }

        if (bp.opcode != it->second.opcode && !prompt)
        {
            prompt = true;

            XString msg;
            msg << L"当前地址: " << bp_address << L"与上次设置断点编码不一致，可能存在压缩。请手动激活断点";
            ::MessageBox(nullptr, msg.w_cstr(), L"提示", MB_OK);

            bp.activation = false;
            BYTE opcode = 0;
            set_opcode(process, bp_address, bp.opcode, opcode);
        }

        this->cc_table.insert(std::pair<DWORD, CC_BREAK_POINT>(bp_address, bp));
         
        std::map<DWORD, CC_BREAK_POINT>::iterator cit = this->cc_table.find(it->first);
        if (cit != this->cc_table.end())
        {
            this->cc_table.erase(cit);
        } 
    }
           
    return true;
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

bool XInt3Tab::insert_table(CC_BREAK_POINT& table)
{
    std::map<DWORD, CC_BREAK_POINT>::_Pairib ret =
        this->cc_table.insert(std::pair<DWORD, CC_BREAK_POINT>(this->cc_table.size(), table));
    return ret.second;
}

bool XInt3Tab::insert_cc(HANDLE handle, DWORD address)
{
    BYTE opcode = 0;
    bool status = set_opcode(handle, address, this->int3, opcode);
    if (status)
    {
        DWORD base;
        DWORD offset;
        XString name;
        if (XModelTab::pins()->get_name_base_offset(address, base, offset, name))
        {
            CC_BREAK_POINT cbp;
            cbp.opcode = opcode;
            cbp.module_name = name;
            cbp.offset = offset;
            cbp.activation = true;
            cbp.number = get_index(); 
            if (cbp.number == -1)
            {
                cbp.number = this->cc_table.size() + 1;
            }

            std::map<DWORD, CC_BREAK_POINT>::_Pairib ret =
                this->cc_table.insert(std::pair<DWORD, CC_BREAK_POINT>(address, cbp));
            if (!ret.second)
            {
                set_opcode(handle, address, opcode, opcode);
                status = ret.second;
            }
            else
            {
                XSQLite3::pins()->insert_break_point(cbp);
            }
        } 
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

bool XInt3Tab::set_cc_status(HANDLE handle, int index, bool status)
{
    std::map<DWORD, CC_BREAK_POINT>::iterator it = this->cc_table.begin();
    for (it; it != this->cc_table.end(); it++)
    {
        if (it->second.number == index)
        {
            BYTE opcode = 0;
            it->second.activation = status;
            if (status)
            {
                set_opcode(handle, it->first, this->int3, opcode);
            } 
            else
            {
                set_opcode(handle, it->first, it->second.opcode, opcode);
            }
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

int XInt3Tab::get_index()
{
    for (std::map<DWORD, CC_BREAK_POINT>::size_type i = 0;
        i < this->cc_table.size() + 1;
        i++)
    {
        std::vector<int>::iterator it = std::find(cc_table_num_mgr.begin(), cc_table_num_mgr.end(), i);
        if (it == cc_table_num_mgr.end())
        { 
            cc_table_num_mgr.push_back(i);
            return i;
        }
    }

    return -1;
}