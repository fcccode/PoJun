#include "stdafx.h"
#include "XMemoryMgr.h"
 
XMemoryMgr* XMemoryMgr::m_This = nullptr;
XMemoryMgr::XMemoryMgr()
{
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

bool XMemoryMgr::get_memort_byte(HANDLE process, DWORD address, int row, XString& str_mem_data)
{
    BYTE* buffer = new BYTE[row * E_COL];
    if (!get_memort(process, address, row * E_COL, buffer))
    {
        delete[] buffer;
        return false;
    } 

    for (int i_row = 0; i_row < row; i_row++)
    {
        str_mem_data << XString(buffer + i_row * E_DB, E_DB) << L"     ";

        for (int i = 0; i < E_DB; i++)
        {
            char ch = *(char*)(buffer + i_row * E_DB + i);
            if (ch > 0x7F || ch == 0x00 || ch == 0x07 || ch == 0x08 
                || ch == 0x0A || ch == 0x0D || ch == 0x20 || ch == 0x25
                || ch == 0xFF)
            {
                str_mem_data << XString('.');
            }
            else
            {
                str_mem_data << XString(ch);
            }
        }

        str_mem_data << L"\r\n"; 
    }

    delete[] buffer;
    return true;
}

bool XMemoryMgr::get_memort_word(HANDLE process, DWORD address, int row, XString& str_mem_data)
{
    int i_size = E_COL;
    BYTE* buffer = new BYTE[row * i_size];
    if (!get_memort(process, address, row * i_size, buffer))
    {
        delete[] buffer;
        return false;
    }
     
    for (int i_row = 0; i_row < row; i_row++)
    {
        for (int i_col = 0; i_col < i_size; i_col)
        {
            BYTE low = *(buffer + i_row * E_DB + i_col++);
            BYTE high = *(buffer + i_row * E_DB + i_col++);
              
            XString::byte2str(high, str_mem_data);
            XString::byte2str(low, str_mem_data);
            str_mem_data << L"  ";
        }
          
        str_mem_data << L"\r\n";
    }

    delete[] buffer;
    return true;
}

bool XMemoryMgr::get_memort_dword(HANDLE process, DWORD address, int row, XString& str_mem_data)
{ 
    int i_size = E_DWORD;
    BYTE* buffer = new BYTE[row * i_size];
    if (!get_memort(process, address, row * i_size, buffer))
    {
        delete[] buffer;
        return false;
    }

    for (int i_row = 0; i_row < row; i_row++)
    {
        BYTE low = *(buffer + i_row * E_DWORD);
        BYTE high = *(buffer + i_row * E_DWORD + 1);
        BYTE lowex = *(buffer + i_row * E_DWORD + 2);
        BYTE highex = *(buffer + i_row * E_DWORD + 3);

        XString::byte2str(highex, str_mem_data);
        XString::byte2str(lowex, str_mem_data);
        XString::byte2str(high, str_mem_data);
        XString::byte2str(low, str_mem_data);
        str_mem_data << L"  ";

        str_mem_data << L"\r\n";
    }

    delete[] buffer;
    return true;
}

bool XMemoryMgr::get_memort(HANDLE process, DWORD address, int size, BYTE* buffer)
{ 
    BOOL bRet = ::ReadProcessMemory(process, (LPCVOID)address, (LPVOID)buffer, size, NULL);
    if (bRet == FALSE)
    {
        return false;
    } 

    return true;
}