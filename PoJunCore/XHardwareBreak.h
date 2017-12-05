#pragma once
#include "XPJCoreHead.h"
   
class XHardwareBreak
{
public:
    XHardwareBreak();
    ~XHardwareBreak();

    static XHardwareBreak* pins();
    static XHardwareBreak* m_This;
     
    bool insert(std::vector<XString>& vt_command, CONTEXT& context);

    bool insert(HARD_DWARE_BREAK_POINT& hb);

    bool get_hardware_break_table(std::vector<HARD_DWARE_BREAK_POINT>& out_tab);

    bool delete_hardware_break_inedx(CONTEXT& context, int inedx);

    bool reduction_hardware_break_point(CONTEXT& context);

private:
    int get_hardware_break_pos(CONTEXT& context);

    bool check_command(std::vector<XString>& vt_command, HARD_DWARE_BREAK_POINT& out_data);

    bool insert_hardware_break(DWORD pos, DWORD_PTR address, DWORD type, DWORD length, CONTEXT& context);
      
    void set_bit(DWORD_PTR& dw, int lowBit, int bits, int newValue);

private:
    std::vector<HARD_DWARE_BREAK_POINT> hard_dware_break_tab;
    int count;
};

