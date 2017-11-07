#include "stdafx.h"
#include "XBreakPoint.h"
#include "XInt3Tab.h"


XBreakPoint* XBreakPoint::pThis = 0;
XBreakPoint::XBreakPoint()
{
}


XBreakPoint::~XBreakPoint()
{
}
 
XBreakPoint* XBreakPoint::pins()
{
    if (pThis == nullptr)
    {
        pThis = new XBreakPoint;
    }

    return pThis;
}

BP_STATUS XBreakPoint::break_point(EXCEPTION_RECORD* ed, tagDebugInfo& debug_info)
{ 
    if (XInt3Tab::pins()->is_my_cc(debug_info.process, --debug_info.context.Eip))
    {
        return BP_CC; 
    } 
    else if (XInt3Tab::pins()->is_start_opcode(*(DWORD*)&ed->ExceptionAddress))
    {  
        return BP_OEP;
    }

    return BP_NULL;
}

BP_STATUS XBreakPoint::reduction_oep(HANDLE handle)
{
    bool status = XInt3Tab::pins()->reduction_oep(handle);
    return status ? BP_OK : BP_NULL;
}

BP_STATUS XBreakPoint::insert_cc(HANDLE handle, DWORD address)
{
    bool status = XInt3Tab::pins()->insert_cc(handle, address); 
    return status ? BP_OK : BP_NULL;
}