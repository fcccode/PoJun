#include "stdafx.h"
#include "XDecodingASM.h" 


XDecodingASM* XDecodingASM::m_This = 0;
XDecodingASM::XDecodingASM()
{
    init = false;
    init_capstone();
}


XDecodingASM::~XDecodingASM()
{
    if (init)
    {
        cs_close(&asm_handle);
    } 
}
 
XDecodingASM* XDecodingASM::pins()
{
    if (m_This == nullptr)
    {
        m_This = new XDecodingASM;
    }

    return m_This;
}

bool XDecodingASM::init_capstone()
{
    if (init)
    {
        return true;
    }

    cs_err err = cs_open(CS_ARCH_X86, CS_MODE_32, &asm_handle);
    if (err)
    {
        return false;
    }

    init = true;
    return true;
}

bool XDecodingASM::decoding_asm(HANDLE process, DWORD address, DWORD count, std::list<DECODEING_ASM>& asm_tab)
{
    if (!init)
    {
        return false;
    }

    unsigned char *opcode_buf = new unsigned char[(count+1)*E_OPCODE_LENGTH];
    if (opcode_buf == nullptr)
    {
        return false;
    }

    BOOL status = ::ReadProcessMemory(process, (LPCVOID)address, (LPVOID)opcode_buf,
        (count+1)*E_OPCODE_LENGTH*sizeof(unsigned char), NULL);
    if (status == FALSE)
    {
        return false;
    }
     
    cs_insn *insn = nullptr;
    int de_count = cs_disasm(asm_handle, opcode_buf, count*E_OPCODE_LENGTH, address, 0, &insn);
    if (de_count == 0)
    {
        return false;
    } 

    for (DWORD i = 0; i < count + 1; i++)
    { 
        DECODEING_ASM decoding;
        decoding.head = insn[i].bytes[0];
        decoding.address = (DWORD)insn[i].address;
        memset(&decoding.opcode, 0x0, E_OPCODE_LENGTH * sizeof(uint8_t));
        memcpy(decoding.opcode, insn[i].bytes, insn[i].size);
        decoding.opcode_length = insn[i].size; 
        decoding.asm_str << insn[i].mnemonic << L" " << insn[i].op_str;
        asm_tab.push_back(decoding);
    }  

    cs_free(insn, de_count);
    return true;
}