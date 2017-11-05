#include "stdafx.h"
#include "XOutStringTab.h"
 
XOutStringTab* XOutStringTab::m_This = 0;
XOutStringTab::XOutStringTab()
{
}


XOutStringTab::~XOutStringTab()
{
}
 
XOutStringTab* XOutStringTab::pins()
{
    if (m_This == 0)
    {
        m_This = new XOutStringTab;
    }

    return m_This;
}

void XOutStringTab::insert_out_string(OUTPUT_DEBUG_STRING_INFO* os, HANDLE pcoess)
{
    if (os->fUnicode)
    {
        //unicode
        WCHAR buffer[512] = { 0 };
        BOOL ret = ::ReadProcessMemory(
            pcoess, 
            (LPCVOID)os->lpDebugStringData, 
            (LPVOID)&buffer,
            os->nDebugStringLength, 
            nullptr);
        if (ret)
        {
            XString str(buffer);
            this->out_string.push_back(str);
        }
    }
    else
    {
        //·Çunicode
        char buffer[512] = { 0 };
        BOOL ret = ::ReadProcessMemory(
            pcoess, 
            (LPCVOID)os->lpDebugStringData, 
            (LPVOID)&buffer, 
            os->nDebugStringLength, 
            nullptr);
        if (ret)
        {
            XString str(buffer);
            this->out_string.push_back(str);
        }
    }
}