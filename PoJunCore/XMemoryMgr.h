#pragma once

#include "XPCoreHead.h"

enum 
{ 
    E_COL = 16,
    E_DB = 16,
    E_WORD = 2,
    E_WORD_ROW = 8,
    E_DWORD = 4
};



class XMemoryMgr
{
public:
    XMemoryMgr();
    ~XMemoryMgr();

    static XMemoryMgr* pins();
    static XMemoryMgr* m_This;

    bool get_memort_byte(HANDLE process, DWORD address, int row, DEBUG_MODULE_DATA::D_MEMORY& dm);

    bool get_memort_word(HANDLE process, DWORD address, int row, DEBUG_MODULE_DATA::D_MEMORY& dm);

    bool get_memort_dword(HANDLE process, DWORD address, int row, DEBUG_MODULE_DATA::D_MEMORY& dm); 
};