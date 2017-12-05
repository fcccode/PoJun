#include "stdafx.h"
#include "XHardwareBreak.h"
#include "XSQLite3.h"


XHardwareBreak* XHardwareBreak::m_This = nullptr;
XHardwareBreak::XHardwareBreak()
{
    hard_dware_break_tab.resize(4);
    count = 0;
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

bool XHardwareBreak::insert(HARD_DWARE_BREAK_POINT& hb)
{
    this->hard_dware_break_tab[hb.dr_number] = hb;
    this->count++;
    return true;
}

bool XHardwareBreak::insert(std::vector<XString>& vt_command, CONTEXT& context)
{
    int pos = get_hardware_break_pos(context);
    if (pos == -1)
    {
        return false;
    }
      
    HARD_DWARE_BREAK_POINT data;
    data.dr_number = pos;
    if (!check_command(vt_command, data))
    {
        return false;
    } 

    if (!insert_hardware_break(data.dr_number,
            data.address,
            data.type,
            data.length,
            context))
    {
        return false;
    }
     
    this->hard_dware_break_tab[pos] = data;
    this->count++;
    return XSQLite3::pins()->insert_hardwate_break(data);
}

bool XHardwareBreak::get_hardware_break_table(std::vector<HARD_DWARE_BREAK_POINT>& out_tab)
{
    out_tab = this->hard_dware_break_tab;
    return true;
}

bool XHardwareBreak::delete_hardware_break_inedx(CONTEXT& context, int inedx)
{
    if (inedx < 0 || inedx > 4)
    {
        return FALSE;
    } 

    std::vector<HARD_DWARE_BREAK_POINT>::iterator it = hard_dware_break_tab.begin();
    for (it; it != this->hard_dware_break_tab.end(); it++)
    {
        if (it->dr_number == inedx)
        { 
            set_bit(context.Dr7, 16 + inedx * 4, 2, 0);
            set_bit(context.Dr7, 18 + inedx * 4, 2, 0);
            set_bit(context.Dr7, inedx * 2, 1, 0);
            this->hard_dware_break_tab.erase(it);
            break;
        }
    } 

    return true;
}

int XHardwareBreak::get_hardware_break_pos(CONTEXT& context)
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

    out_data.address = it->to_int_0x();
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
    else if (type.compare(L"r") == 0)
    {
        out_data.type = 3;
    }
    else
    {
        return false;
    }
    it++;

    DWORD length = it->to_int();

    if (length == 1)
    {
        out_data.length = 0;
    }
    else if (length == 2)
    {
        out_data.length = 1;
    }
    else if (length == 4)
    {
        out_data.length = 3;
    }
    else if (length == 8)
    {
        out_data.length = 2;
    }
    else
    {
        return false;
    } 
     
    return true;
} 

bool XHardwareBreak::insert_hardware_break(DWORD pos, DWORD_PTR address, DWORD type, DWORD length, CONTEXT& context)
{
    if (pos == 0)
    {
        context.Dr0 = address;
    }
    else if (pos == 1)
    {
        context.Dr1 = address;
    }
    else if (pos == 2)
    {
        context.Dr2 = address;
    }
    else if (pos == 3)
    {
        context.Dr3 = address;
    }
    else
    {
        //插入数量多于4个
        return false;
    }

    context.Dr6 = 0;

    set_bit(context.Dr7, 16 + pos * 4, 2, type);
    set_bit(context.Dr7, 18 + pos * 4, 2, length);
    set_bit(context.Dr7, pos * 2, 1, 1);
    set_bit(context.Dr7, 1 + pos * 2, 1, 1);

    return true;
}

void XHardwareBreak::set_bit(DWORD_PTR& dw, int lowBit, int bits, int newValue)
{
    DWORD_PTR mask = (1 << bits) - 1;
    dw = (dw & ~(mask << lowBit)) | (newValue << lowBit);
}

bool XHardwareBreak::reduction_hardware_break_point(CONTEXT& context)
{
    for (int i = 0; i < this->count; i++)
    {
        HARD_DWARE_BREAK_POINT hb = this->hard_dware_break_tab[i]; 
        if (hb.dr_number < 4)
        {
            insert_hardware_break(hb.dr_number,
                hb.address,
                hb.type,
                hb.length,
                context);
        } 
    } 

    return true;
}