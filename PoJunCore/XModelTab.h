#pragma once 
#include "XPJCoreHead.h"

#define PAGE_BASE(pos) (pos & 0xFFFFF000) - 0x1000 

class XModelTab
{ 
private:
    XModelTab();
    ~XModelTab();

public:
    static XModelTab* m_This;
    static XModelTab* pins();

    void insert_exe(MODULE_INFO& mi);

    void insert_dll(LOAD_DLL_DEBUG_INFO *load_dll);
      
    void remove_dll(DWORD base);

    bool get_module_table(std::map<DWORD, MODULE_INFO>& modules);

    bool get_name_base_offset(DWORD address, DWORD& base, DWORD& offset, XString& name);
      
private: 
    std::map<DWORD, MODULE_INFO> modules;
};

