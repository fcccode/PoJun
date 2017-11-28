#pragma once
#include "XPJCoreHead.h"
#include <XString.h> 
#include <capstone.h> 

enum
{
    E_OPCODE_LENGTH = 0x10
}; 
  
class XDecodingASM
{
public:
    XDecodingASM();
    ~XDecodingASM();

    static XDecodingASM* m_This;
    static XDecodingASM* pins();

    bool decoding_asm(HANDLE process, DWORD address, DWORD count, std::list<DECODEING_ASM>& asm_tab);
    
private:
    bool init_capstone();

    bool init;

    csh  asm_handle;
};

