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

void XBreakPoint::break_point(EXCEPTION_RECORD* ed, tagDebugInfo& debug_info)
{ 
    if (XInt3Tab::pins()->is_start_opcode(*(DWORD*)&ed->ExceptionAddress))
    {

    }
    else if (XInt3Tab::pins()->is_my_cc(debug_info))
    {

    }
}