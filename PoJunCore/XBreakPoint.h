#pragma once
#include "XPublicHead.h"

class XBreakPoint
{
public:
    XBreakPoint();
    ~XBreakPoint();

    static XBreakPoint* pThis;
    static XBreakPoint* pins();

    void break_point(EXCEPTION_RECORD* ed, tagDebugInfo& debug_info);

private:

};

