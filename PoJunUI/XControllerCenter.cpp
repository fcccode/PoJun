#include "XControllerCenter.h"
#include "XDateCenter.h"
#include "XDbgThread.h"
#include <XString.h> 

XControllerCenter* XControllerCenter::mThis = nullptr;
XControllerCenter::XControllerCenter()
{
    status = E_SLEEP;
    dbg_thread = nullptr;
}


XControllerCenter::~XControllerCenter()
{
}
 
XControllerCenter* XControllerCenter::pins()
{
    if (mThis == nullptr)
    {
        mThis = new XControllerCenter;
    }

    return mThis;
}

bool XControllerCenter::dbg_new_process(const XString& path)
{ 
    XDateCenter::pins()->set_dbg_process_path(path);

    if (dbg_thread == nullptr)
    {
        dbg_thread = new XDbgThread; 
        if (dbg_thread == nullptr)
        {
            return false;
        }

        connect(dbg_thread, SIGNAL(show_asm()), this, SIGNAL(show_asm()));
    } 

    status = E_NEW_PROCESS; 
    dbg_thread->start(); 
    return true;
} 