#include "XDbgThread.h"
#include <windows.h>
#include <XDebugControl.h>
#include "XDateCenter.h" 

XDbgThread* pThis = nullptr;
  
XDbgThread::XDbgThread()
{ 
} 

XDbgThread::~XDbgThread()
{
}

void XDbgThread::run()
{
    pThis = this;
      
    XDebugControl::pins()->start_debug_loop(
        XDateCenter::pins()->get_dbg_process_path(), 
        XDbgThread::in_fun,
        XDbgThread::out_fun,
        XDbgThread::command_call_back_out,
        1); 
}

void __stdcall XDbgThread::in_fun(XString& command)
{
    MessageBox(0, 0, 0, 0);
}

void __stdcall XDbgThread::out_fun(CONTEXT context, std::list<DECODEING_ASM>& asm_tab)
{ 
    XDateCenter::pins()->insert_out_date(context, asm_tab);
    emit pThis->show_asm(); 
}
 
void __stdcall XDbgThread::command_call_back_out(const DEBUG_MODULE_DATA& module_data)
{
    MessageBox(0, 0, 0, 0);
}
