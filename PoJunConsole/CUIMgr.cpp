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
    wprintf(L"破军动态调试器 v0.0\r\n"
        L"请输入功能号: \r\n"
        L"1. 打开文件开始动态调试 \r\n"
        L"2. 附加到进程列表 \r\n"
        L"3. 退出 \r\n"
        L"请输入数字命令: ");
     
    char command = getchar(); 
    return command - 0x30;
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
        wprintf(L"打开文件失败!");
        pause();
        return L"";
    }
}

void __stdcall CUIMgr::in_fun(XString& out_command)
{
    char comm[64] = { 0 };
    fflush(stdin);
    fgets(comm, 64, stdin);
    fflush(stdin);
    out_command = comm;
    int pos = out_command.rfind(L"\n");
    out_command = out_command.substr(0, pos);
}

void __stdcall CUIMgr::out_fun(const CONTEXT context, const std::list<DECODEING_ASM>& asm_tab)
{
    DWORD dwFlags = 0;
    DWORD dwbite[8] = { 11, 10, 8, 7, 6, 4, 2, 0 };
    WCHAR chbite[8][2][3] = { { L"OV", L"NV" }, { L"DN", L"UP" }, { L"EI", L"DI" }, { L"NG", L"PL" },
    { L"ZR", L"NZ" }, { L"AC", L"NA" }, { L"PE", L"PO" }, { L"CY", L"NC" } };

    wprintf(L"EAX=%08X EDX=%08X ECX=%08X EBX=%08X ESI=%08X EDI=%08X \r\n"
        L"EIP=%08X ESP=%08X EBP=%08X \r\n"
        L"CS=%04X SS=%04X DS=%04X ES=%04X FS=%04X GS=%04X",
        context.Eax, context.Edx, context.Ecx, context.Edx, context.Esi,
        context.Edi, context.Eip, context.Esp, context.Ebp, context.SegCs,
        context.SegSs, context.SegDs, context.SegEs, context.SegFs,
        context.SegGs);
    dwFlags = context.EFlags;
    wprintf(L"        ");

    for (int i = 0; i < 8; i++)
    {
        DWORD m = dwFlags;
        m = m >> dwbite[i] & 1;

        if (m == 1)
        {
            wprintf(L"%s ", chbite[i][0]);
        }
        else
        {
            wprintf(L"%s ", chbite[i][1]);
        }
    }
    wprintf(L"\r\n");

    std::list<DECODEING_ASM>::const_iterator it = asm_tab.cbegin();
    int i = 0;
    for (it; it != asm_tab.cend() && i < 1; it++, i++)
    {
        XString asm_str = it->asm_str;
        XString opcode(it->opcode, it->opcode_length);
        wprintf(L"%p:%-14s   %s [%d] \r\n", it->address, opcode.w_cstr(), asm_str.w_cstr(), it->opcode_length);
    } 
}

void __stdcall CUIMgr::command_call_back_out(const DEBUG_MODULE_DATA& module_data)
{
    if (module_data.type == E_BPL)
    {
        CUIMgr::pins()->show_break_point_tab(module_data.break_point_tab);
    }
    return;
}

void CUIMgr::show_break_point_tab(const std::map<DWORD, CC_BREAK_POINT>& break_point_tab)
{
    WCHAR activation[][64] = { L"未激活", L"已激活" };
    std::map<DWORD, CC_BREAK_POINT>::const_iterator it = break_point_tab.cbegin();
    for (it; it != break_point_tab.cend(); it++)
    {
        wprintf(L"%p    %d    %s \r\n", it->first, it->second.number, activation[it->second.activation]);
    }
}