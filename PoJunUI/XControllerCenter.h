#pragma once
#include <windows.h>
#include <QObject>
#include <XPJCoreHead.h>


class XDbgThread;

typedef enum 
{
    E_SLEEP,
    E_NEW_PROCESS,
    E_ATTACHED_PROCESS
}DBG_STATUS;

class XControllerCenter : public QObject
{ 
    Q_OBJECT
private:
    XControllerCenter();
    ~XControllerCenter();

public:
    static XControllerCenter* mThis;
    static XControllerCenter* pins();

public:
    bool dbg_new_process(const XString& path);

signals: 
    void show_asm();

private:
    DBG_STATUS status; 

    XDbgThread* dbg_thread;
};