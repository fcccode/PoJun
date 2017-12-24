#pragma once



#include "XPJCoreHead.h"   
//#include <ImageHlp.h>

#define D_OPCODE_CALL_LENGTH 0x5
#define D_FUN_RET_OFFSET     0x4  

 

class XSymbolData
{
private:
    XSymbolData();
    ~XSymbolData();

public:
    static XSymbolData* m_This;
    static XSymbolData* pins();

    static bool get_thread_stack_data(HANDLE thread, CONTEXT& context, std::vector<STACK_TABLE>& out_data);

    void set_symbol_path(std::vector<XString>& path);
    
    bool reload();

    bool reload(XString& sym_name);
     

private:
    std::vector<XString> symbol_path;

    bool symbol_init;
     
};