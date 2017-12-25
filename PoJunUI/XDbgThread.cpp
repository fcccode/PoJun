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
    emit pThis->command_in(); 

    do 
    {
        Sleep(1000);
        command = XDateCenter::pins()->get_command();
    } while (command.empty());
}

void __stdcall XDbgThread::out_fun(CONTEXT context, std::list<DECODEING_ASM>& asm_tab)
{ 
    XDateCenter::pins()->insert_out_date(context, asm_tab);
    emit pThis->show_asm(); 
}
 
void __stdcall XDbgThread::command_call_back_out(const DEBUG_MODULE_DATA& module_data)
{
    XDateCenter::pins()->set_module_date(module_data);
    emit pThis->show_run_command();
}

void XDbgThread::run_command()
{
    XString command = XDateCenter::pins()->get_command();
    XDebugControl::pins()->run_command(command);
}