#include "XDateCenter.h"


XDateCenter* XDateCenter::m_This = nullptr;
XDateCenter::XDateCenter()
{
}


XDateCenter::~XDateCenter()
{
}
 
XDateCenter* XDateCenter::pins()
{
    if (m_This == nullptr)
    {
        m_This = new XDateCenter;
    }

    return m_This;
}

void XDateCenter::set_dbg_process_path(const XString& path)
{
    this->dbg_process_path = path;
}

XString XDateCenter::get_dbg_process_path()
{
    return this->dbg_process_path;
}

void XDateCenter::insert_out_date(CONTEXT context, std::list<DECODEING_ASM>& asm_tab)
{
    OUT_DATE out_date;
    out_date.context = context;
    out_date.asm_tab = asm_tab;

    this->out_date.push_back(out_date);
}

bool XDateCenter::get_out_date(std::vector<OUT_DATE>& out_date)
{
    out_date = this->out_date;
    clear_out_date();
    return true;
}

void XDateCenter::clear_out_date()
{
    std::vector<OUT_DATE>::iterator it = out_date.begin();
    for (it; it != out_date.end(); it++)
    {
        it->asm_tab.clear();
    }

    out_date.clear();
}

void XDateCenter::set_command(const XString& command)
{
    this->command_in = command;
}

XString XDateCenter::get_command()
{
    XString command = this->command_in;
    this->command_in = L"";
    return command;
}

void XDateCenter::set_module_date(const DEBUG_MODULE_DATA& module_data)
{
    this->module_date = module_data;
}

DEBUG_MODULE_DATA XDateCenter::get_module_date()
{
    return this->module_date;
}

void XDateCenter::clear_module_date()
{
    //clear
}