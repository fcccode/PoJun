#include "stdafx.h"
#include "XPublicHead.h"

void XGlobal::show_api_err()
{
    LPVOID lpMsgBuf;
    ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        (LPTSTR)&lpMsgBuf,
        0,
        NULL);
    ::MessageBox(NULL, (LPCWCHAR)lpMsgBuf, L"Debug Error", MB_OK | MB_ICONINFORMATION);
    ::LocalFree(lpMsgBuf);

    ::ExitProcess(0);
}