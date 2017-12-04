#pragma once

#include "XPJCoreHead.h"
#include "XModelTab.h"
 
#define D_ROW 8
#define D_COL 16
#define PAGE_SIZE 0x1000  

typedef enum
{
    E_FLASE,
    E_TRUE,
    E_NOT_TYPE
}CXMEMORY_MGR;

class XMemoryMgr
{
public:
    XMemoryMgr();
    ~XMemoryMgr();

    static XMemoryMgr* pins();
    static XMemoryMgr* m_This;

    bool insert_break_point(HANDLE process, DWORD address, DWORD length, bool rw);

    CXMEMORY_MGR is_my_break_point(EXCEPTION_DEBUG_INFO *ed);

    bool reset_protect(HANDLE process, DWORD address, bool status = false);
    
    bool get_memory_table(std::map<DWORD, MEMORY_BREAK_POINT>& table);

    bool delete_memory_break_point_inedx(HANDLE process, DWORD inedx);

    DWORD get_reduction_memory_break_point();

public:
    bool read_memory(HANDLE process, DWORD address, LPVOID* buf, int size = D_ROW * D_COL);

    bool write_memory(HANDLE process, DWORD address, LPCVOID buf, int length);

private:
    int get_page_count(DWORD address, DWORD length);

    bool set_break_point(HANDLE process, DWORD address, DWORD& old_protect);

    bool set_protect(HANDLE process, DWORD address, DWORD protect, bool status);

    DWORD get_inedx();

private:
    std::map<DWORD, MEMORY_BREAK_POINT> memory_break_point;
    std::vector<DWORD> mb_table_num_mgr;

    DWORD reduction_address;
};