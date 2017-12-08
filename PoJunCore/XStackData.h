#pragma once
#include "XPJCoreHead.h"

#define D_OPCODE_CALL_LENGTH 0x5
#define D_FUN_RET_OFFSET     0x4  

class XStackData
{
public:
    XStackData();
    ~XStackData();

    static bool get_thread_stack_data(HANDLE thread, CONTEXT& context, std::vector<STACK_TABLE>& out_data);
};

