#pragma once

#include <windows.h>
#include <XString.h> 

#define XEXP __declspec(dllexport)
 
typedef void(__stdcall *pfun_in_fun)();
typedef void(__stdcall *pfun_out_fun)();

typedef struct _tagDebigInfo
{
    DEBUG_EVENT event;
    HANDLE process;
    HANDLE thread;
    CONTEXT context;
}tagDebugInfo, *ptagDebugInfo;

namespace XGlobal
{
    void show_api_err();
};