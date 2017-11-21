#pragma once
#include <windows.h>
#include <XString.h>  
#include <list>
#include <map>

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

/*
    cc断点结构体
*/
typedef struct _tagCCBreakPoint
{
    int number;
    BYTE opcode;
    bool activation;
}CC_BREAK_POINT;

/*
    硬件断点结构体
*/
typedef struct _tagHardDwareBreak
{
    DWORD address;
    int dr_number;
    int length;
    int type;
}HARD_DWARE_BREAK;


typedef enum _tagModuleType
{
    E_P,
    E_T,
    E_G,
    E_BP,
    E_BPL,
    E_BPC
}DEBUG_MODULE_TYPE;
  
typedef struct _tagModuleData
{
    DEBUG_MODULE_TYPE type;
    std::map<DWORD, CC_BREAK_POINT> break_point_tab;

    std::vector<HARD_DWARE_BREAK> hard_dware_break_tab;

    std::list<DECODEING_ASM> asm_table;
}DEBUG_MODULE_DATA;
 

//输入/输出控制回调
typedef void(__stdcall *pfun_in_fun)(XString& command);
typedef void(__stdcall *pfun_out_fun)(CONTEXT context, const std::list<DECODEING_ASM>& asm_tab);
 
 
//命令管理器回调
typedef bool(__stdcall *pfun_command_call_back)(const XString& command, tagDebugInfo& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
//命令执行完毕输出回调
typedef void(__stdcall *pfun_command_call_back_out)(const DEBUG_MODULE_DATA& module_data);

namespace XGlobal
{
    void show_api_err();
};