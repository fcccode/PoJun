#pragma once
#include "XPublicHead.h"
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
     
    bool is_my_cc(tagDebugInfo& debug_info);


private:
    BYTE int3;
    DWORD start_oep;  
    DWORD start_opcode;

    //int3管理表
    //DWORD:地址，BYTE:被覆盖的源opcode
    std::map<DWORD, BYTE> cc_table;
};

