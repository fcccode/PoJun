#pragma once
#include "XPCoreHead.h"

typedef enum _BP_STATUS
{
    //
    BP_NULL = -1,
    BP_OK,
    BP_OEP, 
    BP_CC
}BP_STATUS;


class XBreakPoint
{
public:
    XBreakPoint();
    ~XBreakPoint();

    static XBreakPoint* pThis;
    static XBreakPoint* pins();

    BP_STATUS break_point(EXCEPTION_RECORD* ed, tagDebugInfo& debug_info);

    BP_STATUS reduction_oep(HANDLE handle);

    BP_STATUS insert_cc(HANDLE handle, DWORD address);


private:

};

