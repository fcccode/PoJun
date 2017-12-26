#include "stdafx.h"
#include "XMemoryMgr.h"
#include <XMemory.h>
 
XMemoryMgr* XMemoryMgr::m_This = nullptr;
XMemoryMgr::XMemoryMgr()
{
    reduction_address = 0;
}


XMemoryMgr::~XMemoryMgr()
{
}

XMemoryMgr* XMemoryMgr::pins()
{
    if (m_This == nullptr)
    {
        m_This = new XMemoryMgr;
    }

    return m_This;
}

bool XMemoryMgr::insert_break_point(HANDLE process, DWORD address, DWORD length, bool rw)
{
    MEMORY_BREAK_POINT mb;
    mb.inedx = get_inedx();
    mb.address = address;
    mb.length = length;
    mb.page_base = PAGE_BASE(address);
    mb.type = rw; 

    DWORD page_count = get_page_count(address, length);
    if (page_count == 1)
    {
        if (set_break_point(process, mb.page_base, mb.old_page_protect))
        {
            this->memory_break_point.insert(std::pair<DWORD, MEMORY_BREAK_POINT>(mb.page_base, mb));
            return true;
        }
         
        return false;
    }

    DWORD start_base = mb.page_base; 
    for (DWORD i = 0; i < page_count; i++, start_base += 0x1000)
    {
        MEMORY_BREAK_POINT smb;
        smb.inedx = get_inedx();
        smb.address = start_base;
        smb.length = 0x1000;
        smb.page_base = start_base;
        smb.type = rw;

        if (set_break_point(process, start_base, smb.old_page_protect))
        {
            this->memory_break_point.insert(std::pair<DWORD, MEMORY_BREAK_POINT>(start_base, mb));
        } 
    }
    
    return true;
} 

CXMEMORY_MGR XMemoryMgr::is_my_break_point(EXCEPTION_DEBUG_INFO *ed)
{
    DWORD base_address = PAGE_BASE(ed->ExceptionRecord.ExceptionInformation[1]);
    std::map<DWORD, MEMORY_BREAK_POINT>::iterator it = this->memory_break_point.find(base_address);
    if (it == this->memory_break_point.end())
    {
        return E_FLASE;
    }

    if (ed->ExceptionRecord.ExceptionInformation[0] != it->second.type)
    {
        return E_FLASE;
    }

    DWORD address = ed->ExceptionRecord.ExceptionInformation[1];
    if (address >= it->second.address && address <= it->second.address + it->second.length)
    {
        return E_TRUE;
    }

    return E_NOT_TYPE;
}

bool XMemoryMgr::reset_protect(HANDLE process, DWORD address, bool status)
{
    DWORD base_address = PAGE_BASE(address);
    std::map<DWORD, MEMORY_BREAK_POINT>::iterator it = this->memory_break_point.find(base_address);
    if (it == this->memory_break_point.end())
    {
        return false;
    }
     
    return set_protect(process, base_address, it->second.old_page_protect, status);
}

bool XMemoryMgr::get_memory_table(std::map<DWORD, MEMORY_BREAK_POINT>& table)
{
    table = this->memory_break_point;
    return true;
}

bool XMemoryMgr::delete_memory_break_point_inedx(HANDLE process, DWORD inedx)
{
    std::map<DWORD, MEMORY_BREAK_POINT>::iterator it = this->memory_break_point.begin();
    for (it; it != this->memory_break_point.end(); it++)
    {
        if (it->second.inedx == inedx)
        {
            reset_protect(process, it->second.page_base);
            
            std::vector<DWORD>::iterator iit 
                = std::find(this->mb_table_num_mgr.begin(), this->mb_table_num_mgr.end(), inedx);
            if (iit != this->mb_table_num_mgr.end())
            {
                this->mb_table_num_mgr.erase(iit);
            }
            return true;
        }
    }

    return false;
}

DWORD XMemoryMgr::get_reduction_memory_break_point()
{
    return this->reduction_address;
}

bool XMemoryMgr::read_memory(HANDLE process, DWORD address, LPVOID* buf, int size)
{     
    *buf = XMemory::allocate<BYTE>(size);
    if (*buf == nullptr)
    {
        return false;
    }
     
    BOOL bRet = ::ReadProcessMemory(process, (LPCVOID)address, *buf, size, NULL);
    if (bRet == FALSE)
    {
        return false;
    }

    return true;
}

bool XMemoryMgr::write_memory(HANDLE process, DWORD address, LPCVOID buf, int length)
{
    BOOL ret = ::WriteProcessMemory(process, (LPVOID)address, buf, length, nullptr);
    if (ret)
    {
        return true;
    }

    return false;
} 

int XMemoryMgr::get_page_count(DWORD address, DWORD length)
{
    if (length < PAGE_SIZE)
    {
        DWORD curr_base = PAGE_BASE(address);
        DWORD is_next_base = PAGE_BASE(address + length);
        if (curr_base == is_next_base)
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }

    DWORD count = length / PAGE_SIZE;
    DWORD mod = (length & (length / (count * PAGE_SIZE)));
    if (mod > 0 && mod < PAGE_SIZE)
    {
        count++; 
    }

    return count;
}

bool XMemoryMgr::set_break_point(HANDLE process, DWORD address, DWORD& old_protect)
{
    BOOL ret = ::VirtualProtectEx(process, (LPVOID)address, 1,
        PAGE_NOACCESS, &old_protect);
    if (ret)
    {
        return true;
    }

    return false;
}

bool XMemoryMgr::set_protect(HANDLE process, DWORD address, DWORD protect, bool status)
{
    DWORD dw = 0;

    if (status)
    {
        this->reduction_address = 0;
        return set_break_point(process, address, dw);
    }

    BOOL ret = ::VirtualProtectEx(process, (LPVOID)address, 1, protect, &dw);
    if (ret)
    {
        this->reduction_address = address;
        return true;
    }

    return false;
}

DWORD XMemoryMgr::get_inedx()
{
    std::vector<DWORD>::iterator it;
    DWORD i = 0;
    for (i = 0; i < this->mb_table_num_mgr.size(); i++)
    {
        it = std::find(this->mb_table_num_mgr.begin(), this->mb_table_num_mgr.end(), i);
        if (it == this->mb_table_num_mgr.end())
        {
            return i;
        }
    }

    return this->mb_table_num_mgr.size() + 1;
}