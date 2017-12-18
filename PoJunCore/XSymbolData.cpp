#include "stdafx.h"
#include "XSymbolData.h"
#include <DbgHelp.h>
#include "XDebugProcessInfo.h"
#include "XModelTab.h"
#include "XMemoryMgr.h"
#include <XFile.h> 

XSymbolData* XSymbolData::m_This = nullptr;
XSymbolData::XSymbolData()
{
    symbol_init = false;
}

XSymbolData::~XSymbolData()
{
}

XSymbolData* XSymbolData::pins()
{
    if (m_This == nullptr)
    {
        m_This = new XSymbolData;
    }

    return m_This;
}

bool XSymbolData::get_thread_stack_data(HANDLE thread, CONTEXT& context, std::vector<STACK_TABLE>& out_data)
{
    STACKFRAME64 stackFrame = { 0 };
    stackFrame = { 0 };
    stackFrame.AddrPC.Mode = AddrModeFlat;
    stackFrame.AddrPC.Offset = context.Eip;
    stackFrame.AddrStack.Mode = AddrModeFlat;
    stackFrame.AddrStack.Offset = context.Esp;
    stackFrame.AddrFrame.Mode = AddrModeFlat;
    stackFrame.AddrFrame.Offset = context.Ebp;

    CONTEXT Context;
    Context.ContextFlags = CONTEXT_FULL;
    ::GetThreadContext(thread, &Context);

    //获取栈帧
    while (::StackWalk64(
        IMAGE_FILE_MACHINE_I386,
        XDebugProcessInfo::pins()->get_process_handle(),
        XDebugProcessInfo::pins()->get_thread_handle(),
        &stackFrame,
        &Context,
        NULL,
        ::SymFunctionTableAccess64,
        ::SymGetModuleBase64,
        NULL))
    {
        //显示模块名称
        DWORD64 moduleBase = (DWORD)::SymGetModuleBase64(
            XDebugProcessInfo::pins()->get_process_handle(),
            stackFrame.AddrPC.Offset);

        XString module_name = XModelTab::pins()->get_base_name((DWORD)moduleBase);

        //显示函数名称
        BYTE buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)] = { 0 };
        PSYMBOL_INFO pSymInfo = (PSYMBOL_INFO)buffer;
        pSymInfo->SizeOfStruct = sizeof(SYMBOL_INFO);
        pSymInfo->MaxNameLen = MAX_SYM_NAME;

        DWORD64 displacement = 0;

        if (::SymFromAddr(
                XDebugProcessInfo::pins()->get_process_handle(),
                stackFrame.AddrPC.Offset,
                &displacement,
                pSymInfo))
        {
            STACK_TABLE stack;
            stack.module_name = module_name;
            stack.fun_name = pSymInfo->Name;
            DWORD* offset = 0;
            if (XMemoryMgr::pins()->read_memory(
                XDebugProcessInfo::pins()->get_process_handle(),
                (DWORD)(stackFrame.AddrReturn.Offset - 0x4),
                (LPVOID*)&offset,
                sizeof(DWORD)))
            {
                stack.fun_enter = (DWORD)stackFrame.AddrReturn.Offset + *offset;
            }
            if (offset != nullptr)
            {
                delete[] offset;
            }
            stack.stack_base_address = Context.Ebp + D_FUN_RET_OFFSET;
            stack.fun_ret = (DWORD)stackFrame.AddrReturn.Offset;
            stack.call_me_address = (DWORD)stackFrame.AddrReturn.Offset - D_OPCODE_CALL_LENGTH;
            stack.param1 = (DWORD)stackFrame.Params[0];
            stack.param2 = (DWORD)stackFrame.Params[1];
            stack.param3 = (DWORD)stackFrame.Params[2];
            stack.param4 = (DWORD)stackFrame.Params[3];
            out_data.push_back(stack);
        }
    }

    return true;
}

void XSymbolData::set_symbol_path(std::vector<XString>& path)
{
    this->symbol_path.clear();

    std::vector<XString>::iterator it = path.begin();
    for (it; it != path.end(); it++)
    {
        bool dir = false;
        if (!XFile::is_file_exist(*it, dir))
        {
            continue;
        }

        if (dir)
        {
            //枚举目录，搜索pdb, 不枚举子目录
        }
        else
        {
            if (it->get_suffix().compare(L"pdb") == 0)
            {
                this->symbol_path.push_back(*it);
            } 
        }

    } 
}

bool XSymbolData::reload()
{
    if (!this->symbol_init)
    {
        //符号初始化
        BOOL init = ::SymInitialize(
            XDebugProcessInfo::pins()->get_process_handle(),
            NULL,
            FALSE);
        this->symbol_init = (init) ? true : false;
    }

    if (!this->symbol_init)
    {
        return false;
    }
     
    std::map<DWORD, MODULE_INFO> module;
    if (!XModelTab::pins()->get_module_table(module))
    {
        return false;
    }

    std::map<DWORD, MODULE_INFO>::iterator it = module.begin();
    for (it; it != module.end(); it++)
    {
        DWORD64 moduleAddress = ::SymLoadModule64(
            XDebugProcessInfo::pins()->get_process_handle(),
            it->second.hfile,
            NULL,
            NULL,
            (DWORD64)it->second.base,
            0);
    }    

    return true;
}

bool XSymbolData::reload(XString& sym_name)
{
    return true;
}