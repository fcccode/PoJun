#include "stdafx.h"
#include "CUIMgr.h"
#include <locale.h>
#include <windows.h>


CUIMgr* CUIMgr::m_This = 0;
CUIMgr::CUIMgr()
{
}


CUIMgr::~CUIMgr()
{
}
 
CUIMgr* CUIMgr::pins()
{
    if (m_This == 0)
    {
        m_This = new CUIMgr;
    }

    return m_This;
}

void CUIMgr::init_local()
{ 
    setlocale(LC_ALL, "chs");
}

void CUIMgr::clear_ui()
{
    system("cls");
}

void CUIMgr::pause()
{
    system("pause");
}

int CUIMgr::show_main()
{
    wprintf(L"�ƾ���̬������ v0.0\r\n"
        L"�����빦�ܺ�: \r\n"
        L"1. ���ļ���ʼ��̬���� \r\n"
        L"2. ���ӵ������б� \r\n"
        L"3. �˳� \r\n"
        L"��������������: ");

    int CommandNumber = 0;
    scanf("%d", &CommandNumber);

    return CommandNumber;
}

XString CUIMgr::open_file_dlg()
{
    BOOL bRet = FALSE;
    OPENFILENAME OPEN = { 0 };
    WCHAR FilePaht[MAX_PATH] = { 0 };

    OPEN.lStructSize = sizeof(OPENFILENAME);
    OPEN.nMaxFile = (MAX_PATH * sizeof(WCHAR));
    ZeroMemory(&OPEN, sizeof(OPENFILENAME));
    OPEN.lStructSize = sizeof(OPENFILENAME);
    OPEN.hwndOwner = NULL;
    OPEN.lpstrFile = FilePaht;
    OPEN.nMaxFile = (MAX_PATH * sizeof(WCHAR));
    OPEN.nFilterIndex = 1;
    OPEN.lpstrFileTitle = NULL;
    OPEN.nMaxFileTitle = 0;
    OPEN.lpstrInitialDir = NULL;
    OPEN.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    bRet = ::GetOpenFileNameW(&OPEN);
    if (bRet = IDOK)
    {
        return FilePaht;
    }
    else
    {
        wprintf(L"���ļ�ʧ��!");
        pause();
        return L"";
    }
}

void __stdcall CUIMgr::in_fun()
{

}

void __stdcall CUIMgr::out_fun()
{

}