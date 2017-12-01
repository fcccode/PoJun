#include "stdafx.h"
#include "CCommandMgr.h"
#include <XProcess.h>
#include "CUIMgr.h"
#include <XDebugControl.h>

CCommandMgr* CCommandMgr::m_This = 0;
CCommandMgr::CCommandMgr()
{
}


CCommandMgr::~CCommandMgr()
{
}
 
CCommandMgr* CCommandMgr::pins()
{
    if (m_This == 0)
    {
        m_This = new CCommandMgr;
    }

    return m_This;
}
 
void CCommandMgr::command_ui(int type)
{
    switch (type)
    {
    case E_OPEN_FILE:
        { 
            XString FilePath = CUIMgr::pins()->open_file_dlg();
            if (FilePath.empty())
            {
                break;    
            } 
             
            XDebugControl::pins()->start_debug_loop(FilePath, CUIMgr::in_fun, CUIMgr::out_fun, CUIMgr::command_call_back_out, 1);
            break;
        }
    case E_ACTIVE_PROCESS:
        { 
            std::vector<XString> ProcessList;
            XProcess::get_process_list(ProcessList);
            break;
        }
    default:
        break;
    }
} 