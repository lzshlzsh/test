#ifndef _ASM_CODE_H
#define _ASM_CODE_H
#include "common_types.h"

#define COMPAT_TO_LONG 0
#define LONG_TO_COMPAT 1

struct modrm
{
    unsigned rm:3;
    unsigned reg:3;
    unsigned mod:2;
};

extern void PreloadSTRem(REMINDEX irem);
extern void SynchronizeSTRem(REMINDEX irem);
extern void GenOptimizeStackIns(INSINDEX iins, REMINDEX irem);
extern void DisposeFuncArg(INSINDEX iins, int offset);
extern void GenX64Code(INSINDEX iins);
extern void DupIA32Code(INSINDEX iins);
#endif
