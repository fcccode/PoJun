#pragma once
#include <windows.h>
#include <XString.h>  
#include <list>

#define XEXP __declspec(dllexport)
  

typedef struct _tagDebigInfo
{
    DEBUG_EVENT event;
    HANDLE process;
    HANDLE thread;
    CONTEXT context;
}tagDebugInfo, *ptagDebugInfo;

typedef struct _tagDecodingASM
{
    BYTE head;
    DWORD address;
    BYTE opcode[16];
    DWORD opcode_length;
    XString asm_str;
}DECODEING_ASM;

typedef void(__stdcall *pfun_in_fun)(XString& command);
typedef void(__stdcall *pfun_out_fun)(CONTEXT context, const std::list<DECODEING_ASM>& asm_tab);

namespace XGlobal
{
    void show_api_err();
};