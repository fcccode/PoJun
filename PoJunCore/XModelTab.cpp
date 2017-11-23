#include "stdafx.h"
#include "XModelTab.h"
#include <Psapi.h>


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

void XModelTab::insert_dll(LOAD_DLL_DEBUG_INFO *load_dll)
{ 
    tag_module module;
    module.base = (DWORD)load_dll->lpBaseOfDll;
    module.handle = load_dll->hFile;

    WCHAR path[MAX_PATH] = { 0 };
    if (handle_to_path(module.handle, path))
    {
        module.file_path = path;
        this->modules.insert(std::pair<DWORD, tag_module>(module.base, module));
    }
}

void XModelTab::remove_dll(DWORD base)
{
    std::map<DWORD, tag_module>::iterator it = this->modules.find(base);
    if (it != this->modules.end())
    {
        this->modules.erase(it);
    }
}

bool XModelTab::get_module_table(std::map<DWORD, tag_module>& modules)
{
    modules = this->modules;
    return true;
}

bool XModelTab::handle_to_path(HANDLE handle, WCHAR* path)
{
    WCHAR pszFileName[MAX_PATH];
    HANDLE hFileMap;
    PVOID  pMem = nullptr;

    bool ret = true;
    //��ȡ�ļ���С  
    DWORD  dwFileSizeHigh = 0;
    DWORD  dwFileSizeLow = ::GetFileSize(handle, &dwFileSizeHigh);
    if (dwFileSizeLow == 0 && dwFileSizeHigh == 0)
    {
        ret = false;
    }

    //����Mapping����  
    hFileMap = ::CreateFileMapping(handle,
        NULL,
        PAGE_READONLY,
        0,
        1,
        NULL);
    if (!hFileMap)
    {
        ret = false;
        goto _exit;
    }

    pMem = ::MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, 1);
    if (!pMem)
    {
        ret = false;
        goto _exit;
    }

    //��Mapping�������ļ���  
    if (0 == ::GetMappedFileName(::GetCurrentProcess(),
        pMem,
        pszFileName,  //���豸������ʽ����ļ�·��������ʱ����ϵ�鿴����  
        MAX_PATH))
    {
        ret = false;
        goto _exit;
    }

    WCHAR szTemp[MAX_PATH] = { 0 };
    //��ȡ�����ϵ���������������"C:\"  "D:\"�ȣ��������õ�  
    if (0 == ::GetLogicalDriveStrings(512 - 1, szTemp))
    {
        ret = false;
        goto _exit;
    }

    WCHAR  szName[MAX_PATH];
    WCHAR  szDrive[3] = { 0 };
    BOOL   bFound = false;
    //ͨ��ָ��p���ƶ���˳��������е�������Ŀ¼  
    PTCHAR p = szTemp;
    do
    {
        ::CopyMemory(szDrive, p, 2 * sizeof(WCHAR));
        //ͨ��·�������豸������"C:"  
        if (!::QueryDosDevice(szDrive, szName, 512))
        {
            ret = false;
            goto _exit;
        }
        UINT uNameLen = lstrlen(szName);
        if (uNameLen < MAX_PATH)
        {
            //�Ƚ����������豸���ļ������ļ��豸���Ƿ�ƥ��  
            bFound = wcsncmp(pszFileName, szName, uNameLen) == 0;
            if (bFound)
            {
                //���ƥ�䣬˵�����ҵ�������·��  
                TCHAR szTempFile[MAX_PATH];
                wsprintf(szTempFile, L"%s%s", szDrive, pszFileName + uNameLen);
                wcscpy(path, szTempFile);
            }
        }
        //���ﲻ���Ļ�����ȥ����GetLogicalDriveStrings  
        while (*p++);
    } while (!bFound && *p);


_exit:
    if (pMem != nullptr)
    {
        ::UnmapViewOfFile(pMem);
    }

    if (hFileMap != nullptr)
    {
        ::CloseHandle(hFileMap);
    }

    return ret;
}