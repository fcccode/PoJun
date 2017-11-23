#pragma once 
#include "XPCoreHead.h"

class XModelTab
{
public:
    XModelTab();
    ~XModelTab();

    static XModelTab* m_This;
    static XModelTab* pins();

    void insert_dll(LOAD_DLL_DEBUG_INFO *load_dll);

    void remove_dll(DWORD base);

    bool get_module_table(std::map<DWORD, tag_module>& modules);

private:
    bool handle_to_path(HANDLE handle, WCHAR* path);
      
private: 
    std::map<DWORD, tag_module> modules;
};

