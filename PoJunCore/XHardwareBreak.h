#pragma once
#include "XPCoreHead.h"

class XHardwareBreak
{
public:
    XHardwareBreak();
    ~XHardwareBreak();

    static XHardwareBreak* pins();
    static XHardwareBreak* m_This;
     
    bool insert(std::vector<XString>& vt_command, CONTEXT& context);

    bool get_hard_dware_break_table(std::vector<HARD_DWARE_BREAK_POINT>& out_tab);

    bool delete_hard_ware_break_inedx(CONTEXT& context, int inedx);

private:
    int get_hard_dware_break_pos(CONTEXT& context);

    bool check_command(std::vector<XString>& vt_command, HARD_DWARE_BREAK_POINT& out_data);

    bool set_hard_dware_break_exe(int pos, CONTEXT& context, HARD_DWARE_BREAK_POINT& out_data);

    bool set_hard_dware_break_w(int pos, CONTEXT& context, HARD_DWARE_BREAK_POINT& out_data);

    bool set_hard_dware_break_rw(int pos, CONTEXT& context, HARD_DWARE_BREAK_POINT& out_data);

private:
    std::vector<HARD_DWARE_BREAK_POINT> hard_dware_break_tab;
};

