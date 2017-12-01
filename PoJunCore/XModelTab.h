#pragma once 
#include "XPJCoreHead.h"

class XModelTab
{ 
private:
    XModelTab();
    ~XModelTab();

public:
    static XModelTab* m_This;
    static XModelTab* pins();

    void insert_dll(LOAD_DLL_DEBUG_INFO *load_dll);

    void remove_dll(DWORD base);

    bool get_module_table(std::map<DWORD, MODULE_INFO>& modules);

private:
    bool handle_to_path(HANDLE handle, WCHAR* path);
      
private: 
    std::map<DWORD, MODULE_INFO> modules;
};

