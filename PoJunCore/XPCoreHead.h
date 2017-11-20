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

typedef struct _tagOpcodeInfo
{
    BYTE current_opcode;
    DWORD next_address; 
}OPCODE_INFO;

//输入/输出控制回调
typedef void(__stdcall *pfun_in_fun)(XString& command);
typedef void(__stdcall *pfun_out_fun)(CONTEXT context, const std::list<DECODEING_ASM>& asm_tab);

//命令管理回调
typedef bool(__stdcall *pfun_command_call_back)(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info);

namespace XGlobal
{
    void show_api_err();
};