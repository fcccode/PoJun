#pragma once
#include <XPJCoreHead.h>
#include <QObject>
#include <XString.h> 

typedef struct _out_date
{
    CONTEXT context;
    std::list<DECODEING_ASM> asm_tab;
}OUT_DATE;