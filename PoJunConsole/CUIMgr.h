#pragma once 
#include <stdlib.h>
#include <XString.h>
#include "XPCoreHead.h"

class CUIMgr
{
public:
    CUIMgr();
    ~CUIMgr();

    static CUIMgr* m_This;
    static CUIMgr* pins();

    void init_local();

    void clear_ui();
    
    void pause();

    int show_main();

    XString open_file_dlg();

    static void __stdcall in_fun(XString& out_command);

    static void __stdcall out_fun(const CONTEXT context, const std::list<DECODEING_ASM>& asm_tab);

    static void __stdcall command_call_back_out(const DEBUG_MODULE_DATA& module_data);

    void show_break_point_tab(const std::map<DWORD, CC_BREAK_POINT>& break_point_tab);
};

