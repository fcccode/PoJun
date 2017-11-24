#include "stdafx.h"
#include "XHardwareBreak.h"


XHardwareBreak* XHardwareBreak::m_This = nullptr;
XHardwareBreak::XHardwareBreak()
{
    hard_dware_break_tab.resize(4);
}


XHardwareBreak::~XHardwareBreak()
{
}

XHardwareBreak* XHardwareBreak::pins()
{
    if (m_This == nullptr)
    {
        m_This = new XHardwareBreak;
    }

    return m_This;
}

bool XHardwareBreak::insert(std::vector<XString>& vt_command, CONTEXT& context)
{
    int pos = get_hard_dware_break_pos(context);
    if (pos == -1)
    {
        return false;
    }
     
    HARD_DWARE_BREAK_POINT data;
    data.dr_number = pos;
    if (check_command(vt_command, data))
    {
        return false;
    }

    switch (data.type)
    {
    case 0:
        set_hard_dware_break_exe(pos, context, data);
        break;
    case 1:
        set_hard_dware_break_w(pos, context, data);
        break;
    case 2:
        set_hard_dware_break_rw(pos, context, data);
        break; 
    default:
        break;
    }
     
    this->hard_dware_break_tab[pos] = data;
    return true;
}

bool XHardwareBreak::get_hard_dware_break_table(std::vector<HARD_DWARE_BREAK_POINT>& out_tab)
{
    out_tab = this->hard_dware_break_tab;
    return true;
}

bool XHardwareBreak::delete_hard_ware_break_inedx(CONTEXT& context, int inedx)
{
    if (inedx < 0 || inedx > 4)
    {
        return FALSE;
    }

    DWORD dr0_3[4] = { 0x1, 0x4, 0x10, 0x40 };
    context.Dr7 -= dr0_3[inedx];
    return true;
}

int XHardwareBreak::get_hard_dware_break_pos(CONTEXT& context)
{
    char i = 1;
    int nIndex = 0;

    do
    {
        if ((context.Dr7 & i) == 0)
        {
            return nIndex;
        }
        i = i << 2;
        nIndex++;
    } while (nIndex < 4);

    return -1;
}

bool XHardwareBreak::check_command(std::vector<XString>& vt_command, HARD_DWARE_BREAK_POINT& out_data)
{
    std::vector<XString>::iterator it = vt_command.begin();
    it++;

    out_data.address = it->to_int();
    it++;

    XString type = *it;  
    if (type.compare(L"e") == 0)
    {
        out_data.type = 0;
    }
    else if (type.compare(L"w") == 0)
    {
        out_data.type = 1;
    }
    else if (type.compare(L"a") == 0)
    {
        out_data.type = 2;
    }
    else
    {
        return false;
    }

    DWORD length = it->to_int();
    if (length != 1 && length != 2 && length != 4)
    {
        return false;
    }

    out_data.length = length;
    return true;
}

bool XHardwareBreak::set_hard_dware_break_exe(int pos, CONTEXT& context, HARD_DWARE_BREAK_POINT& out_data)
{
    DWORD dr0_3[4] = { 0x1, 0x4, 0x10, 0x40 };
    DWORD ANDLRW[4] = { 0xFFF0FFFF, 0xFF0FFFFF, 0xF0FFFFFF, 0x0FFFFFFF };
    DWORD *dr0_address = nullptr;

    //设置哪一个Dr0~3放地址
    dr0_address = &context.Dr0;
    dr0_address[pos] = out_data.address;

    //设置断点
    context.Dr7 |= dr0_3[pos];
    context.Dr7 |= 0x700;   //设置其它不重要的位
    context.Dr7 &= ANDLRW[pos];

    return true;
}

bool XHardwareBreak::set_hard_dware_break_w(int pos, CONTEXT& context, HARD_DWARE_BREAK_POINT& out_data)
{
    DWORD dr0_3[4] = { 0x1, 0x4, 0x10, 0x40 };
    DWORD ANDLRW[4] = { 0xFFF0FFFF, 0xFF0FFFFF, 0xF0FFFFFF, 0x0FFFFFFF };
    DWORD OREWA[4] = { 0xFFF7FFFF, 0xFF7FFFFF, 0xF7FFFFFF, 0x7FFFFFFF };
    DWORD ORL[5] = { 0, 0x100000, 0x20000, 0, 0x30000 };
    DWORD *dr0_address = nullptr;

    //设置哪一个Dr0~3放地址
    dr0_address = &context.Dr0;
    dr0_address[pos] = out_data.address;

    //设置断点
    context.Dr7 |= dr0_3[pos];
    context.Dr7 |= 0x700;   //设置其它不重要的位
    context.Dr7 &= ANDLRW[pos];
    context.Dr7 |= OREWA[pos];

    //设置长度
    context.Dr7 |= ORL[out_data.length];

    return true;
}

bool XHardwareBreak::set_hard_dware_break_rw(int pos, CONTEXT& context, HARD_DWARE_BREAK_POINT& out_data)
{
    DWORD dr0_3[4] = { 0x1, 0x4, 0x10, 0x40 };
    DWORD ANDLRW[4] = { 0xFFF0FFFF, 0xFF0FFFFF, 0xF0FFFFFF, 0x0FFFFFFF };
    DWORD OREWA[4] = { 0xC0000, 0xC00000, 0xC000000, 0xC0000000 };
    DWORD ORL[5] = { 0, 0x100000, 0x20000, 0, 0x30000 };
    DWORD *dr0_address = nullptr;

    //设置哪一个Dr0~3放地址
    dr0_address = &context.Dr0;
    dr0_address[pos] = out_data.address;

    //设置权限
    context.Dr7 |= dr0_3[pos];
    context.Dr7 |= 0x700;   //设置其它不重要的位
    context.Dr7 &= ANDLRW[pos];
    context.Dr7 |= OREWA[pos];

    //设置长度
    context.Dr7 |= ORL[out_data.length];
    return true;
}
