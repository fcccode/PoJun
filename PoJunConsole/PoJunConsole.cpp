// PoJunConsole.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "CUIMgr.h"
#include "CCommandMgr.h"


int _tmain(int argc, _TCHAR* argv[])
{     
    CUIMgr::pins()->init_local(); 
    int CommandNumber = CUIMgr::pins()->show_main();
    if (3 == CommandNumber)
    {
        return 1;
    }

    CUIMgr::pins()->clear_ui();
    CCommandMgr::pins()->command_ui(CommandNumber); 
	return 0;
}

