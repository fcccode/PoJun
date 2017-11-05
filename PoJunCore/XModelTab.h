#pragma once 
#include "XPublicHead.h"
#include <map>

typedef struct _tag_module
{
    HANDLE handle;
    DWORD base;
    XString file_path;
}tag_module, *ptag_module;

class XModelTab
{
public:
    XModelTab();
    ~XModelTab();

    static XModelTab* m_This;
    static XModelTab* pins();

    void insert_dll(LOAD_DLL_DEBUG_INFO *load_dll);

    void remove_dll(DWORD base);

    bool handle_to_path(HANDLE handle, WCHAR* path);

private: 
    std::map<DWORD, tag_module> modules;
};

