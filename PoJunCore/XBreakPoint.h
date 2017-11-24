#pragma once
#include "XPCoreHead.h"
#include <map>

typedef enum _BP_STATUS
{
    BP_NULL = -1,
    BP_OK,
    BP_OEP,
    BP_SINGLE_STEP,
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
      
    BP_STATUS set_cc_status(int inedx, bool status);

    BP_STATUS get_cc_table(std::map<DWORD, CC_BREAK_POINT>& out_map);

    BP_STATUS delete_cc_inedx(int inedx);
      
    BP_STATUS insert_single_step(HANDLE handle, DWORD address);

    BP_STATUS insert_hard_break(std::vector<XString>& vt_command, CONTEXT& context);

    BP_STATUS get_hard_ware_break_tab(std::vector<HARD_DWARE_BREAK_POINT>& out_map);

    BP_STATUS delete_hard_ware_break_inedx(CONTEXT& context, int inedx);
     
};

