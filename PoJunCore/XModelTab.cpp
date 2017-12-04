#include "stdafx.h"
#include "XModelTab.h" 
#include <XModule.h>


XModelTab* XModelTab::m_This = 0;
XModelTab::XModelTab()
{
    modules.clear();
}


XModelTab::~XModelTab()
{
}
 
XModelTab* XModelTab::pins()
{
    if (m_This == 0)
    {
        m_This = new XModelTab;
    }

    return m_This;
}

void XModelTab::insert_exe(MODULE_INFO& mi)
{
    this->modules.insert(std::pair<DWORD, MODULE_INFO>(mi.base, mi));
}

void XModelTab::insert_dll(LOAD_DLL_DEBUG_INFO *load_dll)
{ 
    MODULE_INFO module;
    module.base = (DWORD)load_dll->lpBaseOfDll;
    module.handle = load_dll->hFile;

    module.file_path = L"";
    if (XModule::handle_to_path(module.handle, module.file_path))
    { 
        this->modules.insert(std::pair<DWORD, MODULE_INFO>(module.base, module));
    }
}

void XModelTab::remove_dll(DWORD base)
{
    std::map<DWORD, MODULE_INFO>::iterator it = this->modules.find(base);
    if (it != this->modules.end())
    {
        this->modules.erase(it);
    }
}

bool XModelTab::get_module_table(std::map<DWORD, MODULE_INFO>& modules)
{
    modules = this->modules;
    return true;
}
 
bool XModelTab::get_name_base_offset(DWORD address, DWORD& base, DWORD& offset, XString& name)
{
    DWORD curr_base = PAGE_BASE(address); 
    std::map<DWORD, MODULE_INFO>::iterator it = this->modules.find(curr_base);
    if (it == this->modules.end())
    {
        return false;
    }

    base = it->second.base;
    offset = address - base; 
    name = it->second.file_path.get_short_name(); 
    return true;
}