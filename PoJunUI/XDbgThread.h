#pragma once

#include <QThread>
#include "XPublic.h"

class XDbgThread : public QThread
{
    Q_OBJECT 
public:
    XDbgThread();
    ~XDbgThread();

protected:
    virtual void run();

    static void __stdcall in_fun(XString& command);

    static void __stdcall out_fun(CONTEXT context, std::list<DECODEING_ASM>& asm_tab);

    static void __stdcall command_call_back_out(const DEBUG_MODULE_DATA& module_data);

signals:
    void show_asm();

    void command_in();

    void show_run_command();

public slots:
    void run_command();
};

