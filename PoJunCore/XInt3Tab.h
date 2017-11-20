#pragma once
#include "XPCoreHead.h"
#include <map>

class XInt3Tab
{
public:
    XInt3Tab();
    ~XInt3Tab();

    static XInt3Tab* m_This;
    static XInt3Tab* pins();

    void create_process(CREATE_PROCESS_DEBUG_INFO* cp, HANDLE process);
    
    bool is_start_opcode(DWORD opcode);
    
    bool reduction_oep(HANDLE handle);

    bool insert_cc(HANDLE handle, DWORD address);

    bool remove_cc(HANDLE handle, DWORD address);
      
    bool is_my_cc(HANDLE handle, DWORD address);

    bool set_cc_status(int inedx, bool status);
    
    bool get_cc_table(std::map<DWORD, CC_BREAK_POINT>& out_map);

    bool delete_cc_inedx(int inedx);

    bool insert_single_step(HANDLE handle, DWORD address);

    bool is_single_step(HANDLE handle, DWORD address);

private:
    bool set_opcode(HANDLE handle, DWORD address, BYTE& i_opcode, BYTE& o_opcode);

private:
    BYTE int3;
    DWORD start_oep;  
    BYTE start_opcode;

    //int3管理表
    //DWORD:地址，BYTE:被覆盖的源opcode
    std::map<DWORD, CC_BREAK_POINT> cc_table;
    std::vector<int> cc_table_num_mgr;

    //单步表
    std::map<DWORD, BYTE> single_step_table;
};

