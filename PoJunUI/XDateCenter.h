#pragma once 
#include "XPublic.h"
#include <vector>
#include <XPJCoreHead.h>

class XDateCenter
{
public:
    XDateCenter();
    ~XDateCenter();

    static XDateCenter* m_This;
    static XDateCenter* pins();

    void set_dbg_process_path(const XString& path);

    XString get_dbg_process_path();

    void insert_out_date(CONTEXT context, std::list<DECODEING_ASM>& asm_tab);

    bool get_out_date(std::vector<OUT_DATE>& out_date);

    void set_command(const XString& command);

    XString get_command();

    void set_module_date(const DEBUG_MODULE_DATA& module_data);

    DEBUG_MODULE_DATA get_module_date();

    void clear_module_date();

private:
    void clear_out_date();

private:
    XString dbg_process_path;
      
    std::vector<OUT_DATE> out_date;

    XString command_in;

    DEBUG_MODULE_DATA module_date;
};

