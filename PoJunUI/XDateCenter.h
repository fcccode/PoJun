#pragma once 
#include "XPublic.h"
#include <vector>

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

private:
    void clear_out_date();

private:
    XString dbg_process_path;
      
    std::vector<OUT_DATE> out_date;
};

