// PoJunConsole.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "CUIMgr.h"
#include "CCommandMgr.h"


int _tmain(int argc, _TCHAR* argv[])
{     
    do 
    {
        CUIMgr::pins()->init_local();
        CUIMgr::pins()->clear_ui();
        int CommandNumber = CUIMgr::pins()->show_main(); 
        if (3 == CommandNumber)
        {
            break;
        }
         
        CCommandMgr::pins()->command_ui(CommandNumber);

    } while (true);

     
	return 0;
}

