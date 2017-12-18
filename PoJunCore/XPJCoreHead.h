#pragma once
#include <windows.h>
#include <XString.h>  
#include <list>
#include <map>

//导出
#define XEXP __declspec(dllexport)
   
//调试事件信息结构体
typedef struct TAG_DEBUG_INFO
{
    DEBUG_EVENT event;
    HANDLE process;
    HANDLE thread;
    CONTEXT context;
}DEBUG_INFO, *PDEBUG_INFO;

//解码每行反汇编信息
typedef struct TAG_DECODEING_ASM
{
    BYTE head;
    DWORD address;
    BYTE opcode[16];
    DWORD opcode_length;
    XString asm_str;
}DECODEING_ASM;

//模块信息表
typedef struct TAG_MODULE
{
    HANDLE handle;
    HANDLE hfile;
    DWORD base;
    DWORD size;
    DWORD enter;
    DWORD file_version;
    XString file_path;
}MODULE_INFO, *PMODULE_INFO;

//内部数据
typedef struct TAG_OPCODE_INFO
{
    BYTE current_opcode;
    DWORD next_address; 
}OPCODE_INFO;

//CC断点结构体
typedef struct TAG_CC_BREAK_POINT
{
    XString module_name;
    DWORD offset;
    int number;
    BYTE opcode;
    bool activation;
}CC_BREAK_POINT;

//硬件断点结构体
typedef struct TAG_DWARE_BREAK_POINT
{ 
    DWORD address;
    int dr_number;
    int length;
    int type;
}HARD_DWARE_BREAK_POINT;

//内存断点结构体
typedef struct TAG_MEMORY_BREAK_POINT
{
    DWORD inedx;
    DWORD page_base;
    DWORD address;
    DWORD length;
    //0:'r'，1:'w'
    DWORD type;
    DWORD old_page_protect; 
}MEMORY_BREAK_POINT;

typedef struct TAG_STACK_TABLE
{
    XString module_name;
    XString fun_name;
    DWORD fun_enter;
    DWORD stack_base_address;
    DWORD fun_ret;
    DWORD call_me_address;

    DWORD param1;
    DWORD param2;
    DWORD param3;
    DWORD param4;

}STACK_TABLE;
 
//内部信息集合
typedef struct _tagModuleData
{ 
#define D_P L"{E61EAF6A-D3C1-4F1A-913F-85D2AF9D09AB}"
#define D_T L"{112B283F-0130-4D74-80DC-7D8FC4DDC08F}"
#define D_G L"{D9C50B1F-4EE1-4CA5-9271-70CE5A8E3635}"
#define D_BP L"{7AF8FC3C-87B8-4FA1-B033-B7E09724107D}"
#define D_BPL L"{CF29BBAE-F9D3-4C53-9F7F-8542DD0510C1}"
#define D_BPC L"{8A74A5E0-8067-408A-A484-33CA65725F60}"
#define D_BH L"{D7B6476D-F42D-45E4-B553-8F599A88F740}"
#define D_BHL L"{F0F530F4-48BC-4D17-BD27-8CC45C781851}"
#define D_BHC L"{7DC60301-8175-4A57-A4F2-E71E2157638A}"
#define D_BM L"{3B2C7DA6-40A9-4F9F-B9BE-8C64CFD42115}"
#define D_BML L"{E72F1AA1-BF80-44EA-9A51-264ECA05A3BA}"
#define D_BMC L"{E80B5EC1-5719-4363-9097-29872C0E452D}"
#define D_U L"{42127D49-C665-4E39-9960-372B761834D9}"
#define D_R L"{38753B5D-1DA8-4C4D-AB93-98F6FEFB44C1}"
#define D_LM L"{37DD8D12-5095-4867-A7B6-CA168B3C72DB}"
#define D_THREAD  L"{BFC5A2A6-1E7A-4C76-9562-7E7DF6006E57}"
#define D_DB L"{F0D57CCE-8127-4897-8D27-332046391F5F}"
#define D_DW L"{B6B46B9A-08F1-4172-B83E-1D25BEBD0077}"
#define D_DD L"{3154837C-83E8-4D7D-A3C7-333965C728CC}"
#define D_DQ L"{753F8AAF-13FA-4AE3-B641-887FEB3C4EDC}"
#define D_EB L"{E4DE5BDC-D499-4DEA-911E-0CCFA94EB068}"
#define D_EW L"{4142BA82-E36C-46DF-81E0-7782A49477EA}"
#define D_ED L"{F9765DB1-D365-47B2-A504-31668CAFDAD0}"
#define D_EA L"{E5B926CE-FF1F-45F3-848E-06870F24FD2A}"
#define D_EU L"{08AC0A67-3C27-42C3-A51C-81E5C0AD564E}"
#define D_K L"{FE6DBDB1-B1EA-40EC-97A7-0B4DA52FB811}"
#define D_SYM L"{2ACC639D-C0F6-4F3A-B0CB-A77DD11A373C}"
#define D_RELOAD L"{3F1DB640-64B9-48A2-890E-B502A02ECFE1}"


    //指令类型
    XString type;

    std::map<DWORD, CC_BREAK_POINT> break_point_tab;

    std::vector<HARD_DWARE_BREAK_POINT> hard_dware_break_tab;

    std::map<DWORD, MEMORY_BREAK_POINT> memory_break_tab;

    std::list<DECODEING_ASM> asm_table;
    
    std::map<DWORD, MODULE_INFO> module_table;

    std::vector<CREATE_THREAD_DEBUG_INFO> thread_table;

    std::vector<STACK_TABLE> stack_table;

    struct D_MEMORY
    {  
#define DME_NULL L"{F8313ECE-F25C-4F98-A4A8-D7C8DA8C54A6}"
#define DME_BYTE L"{2F4E9CF6-2FFB-47B5-9183-67DB344D302C}"
#define DME_WORD L"{E8E359EB-A4E2-45AA-A439-E926E7324B9D}"
#define DME_DWORD L"{88D416B8-FE72-4140-ADD7-E5C68180D937}"
         
        XString type;
        union
        {
            BYTE* memory_byte;
            WORD* memory_word;
            DWORD* memory_dword;
        };
    }d_memory; 

}DEBUG_MODULE_DATA;
 

//输入/输出控制回调
typedef void(__stdcall *pfun_in_fun)(XString& command);
typedef void(__stdcall *pfun_out_fun)(CONTEXT context, const std::list<DECODEING_ASM>& asm_tab);
 
 
//命令管理器回调
typedef bool(__stdcall *pfun_command_call_back)(const XString& command, DEBUG_INFO& debug_info, OPCODE_INFO& opcode_info, DEBUG_MODULE_DATA& out_module_data);
//命令执行完毕输出回调
typedef void(__stdcall *pfun_command_call_back_out)(const DEBUG_MODULE_DATA& module_data);

namespace XGlobal
{
    void show_api_err();
};