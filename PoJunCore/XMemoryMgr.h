#pragma once

#include "XPCoreHead.h"
  
#define D_ROW 8
#define D_COL 16

class XMemoryMgr
{
public:
    XMemoryMgr();
    ~XMemoryMgr();

    static XMemoryMgr* pins();
    static XMemoryMgr* m_This;
       
    bool free_get_memory(DEBUG_MODULE_DATA::D_MEMORY& dm);
    
    template<typename T>
    bool read_memory(HANDLE process, DWORD address, DEBUG_MODULE_DATA::D_MEMORY& dm, int size = D_ROW * D_COL);

    bool write_memory(HANDLE process, DWORD address, LPCVOID buf, int length);
};

template<typename T>
bool XMemoryMgr::read_memory(HANDLE process, DWORD address, DEBUG_MODULE_DATA::D_MEMORY& dm, int size)
{
    DEBUG_MODULE_DATA::D_MEMORY::DE_MEMORY type[5] = {
        DEBUG_MODULE_DATA::D_MEMORY::DE_MEMORY::DE_NULL,
        DEBUG_MODULE_DATA::D_MEMORY::DE_MEMORY::DE_BYTE,
        DEBUG_MODULE_DATA::D_MEMORY::DE_MEMORY::DE_WORD,
        DEBUG_MODULE_DATA::D_MEMORY::DE_MEMORY::DE_NULL,
        DEBUG_MODULE_DATA::D_MEMORY::DE_MEMORY::DE_DWORD };

    dm.type = type[sizeof(T)];

    LPVOID* pbuffer = nullptr;
    switch (dm.type)
    {
    case DEBUG_MODULE_DATA::D_MEMORY::DE_BYTE:
        pbuffer = (LPVOID*)&dm.memory_byte;
        break;
    case DEBUG_MODULE_DATA::D_MEMORY::DE_WORD:
        pbuffer = (LPVOID*)&dm.memory_word;
        break;
    case DEBUG_MODULE_DATA::D_MEMORY::DE_DWORD:
        pbuffer = (LPVOID*)&dm.memory_dword;
        break;
    default:
        return false;
    }

    *pbuffer = (LPVOID)new BYTE[size];
    if (*pbuffer == nullptr)
    {
        return false;
    }

    BOOL bRet = ::ReadProcessMemory(process, (LPCVOID)address, *pbuffer, size, NULL);
    if (bRet == FALSE)
    {
        return false;
    }

    return true;
}