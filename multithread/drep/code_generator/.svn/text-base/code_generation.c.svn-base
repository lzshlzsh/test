#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include "mem_manage.h"
#include "utility.h"
#include "optimization.h"
#include "assemble.h"

#define NUM_OF_EXBB 20  //num of extra exit or root bbs 
#define REGINS_BUFF_SIZE 48
#define REG_BUFF_NUM 8

UINT32 CurrMmapAddr = MMAP_AREA_START;
AVAIL_REGS iGpr, iXmm, iMmx;

#define MAX_T_CODE_CACHE  100
char tCodeCache[MAX_T_CODE_CACHE];
UINT32 ItCodeCache;

void GenMmapSyscall() {
    ADDR base_code_ptr;
    ADDR mprotect_start;
    int mprotect_size;
    
    ASSERT((*(UINT64 *)(ADDR)aFile._mmap_sc_addr==0x5f80cd000000c0b8 && \
        *(UINT64 *)(ADDR)aFile._mmap64_sc_addr==0x5f80cd000000c0b8 && \
        *(UINT64 *)(ADDR)aFile._mremap_sc_addr==0x5b80cd000000a3b8), ("Can not find the location of syscall.\n"));

    if(aFile._mmap_sc_addr<aFile._mmap64_sc_addr) {
        mprotect_start = aFile._mmap_sc_addr;
        mprotect_size = aFile._mmap64_sc_addr - aFile._mmap_sc_addr;
    }
    else {
        mprotect_start = aFile._mmap64_sc_addr;
        mprotect_size = aFile._mmap_sc_addr - aFile._mmap64_sc_addr;
    }
    
    if(aFile._mremap_sc_addr < mprotect_start) {
        mprotect_size = mprotect_size + mprotect_start - aFile._mremap_sc_addr;
        mprotect_start = aFile._mremap_sc_addr;
    }
    else if(aFile._mremap_sc_addr > mprotect_start+mprotect_size) {
        mprotect_size = aFile._mremap_sc_addr - mprotect_start;
    }

    if(aFile._exit_sc_addr < mprotect_start) {
        mprotect_size = mprotect_size + mprotect_start - aFile._exit_sc_addr;
        mprotect_start = aFile._exit_sc_addr;
    }
    else if(aFile._exit_sc_addr > mprotect_start+mprotect_size) {
        mprotect_size = aFile._exit_sc_addr - mprotect_start;
    }

    mprotect_size = mprotect_size + (mprotect_start&0x0fff);
    mprotect_start = (mprotect_start >> 12) << 12;
    mprotect((void *)mprotect_start, mprotect_size, PROT_READ|PROT_WRITE|PROT_EXEC);

/** mmap
      8b 1d ## ## ## ##       mov    base,%ebx
      a1 ## ## ## ##          mov    index,%eax
      40                      inc    %eax
      a3 ## ## ## ##          mov    %eax,index
      8d 04 c3                lea    (%ebx,%eax,8),%eax
      8b 1d ## ## ## ##       mov    mmap_addr,%ebx
      89 18                   mov    %ebx,(%eax)
      f7 c1 ff 0f 00 00       test   $0xfff,%ecx
      74 0c                   je     L1
      81 e1 00 f0 ff ff       and    $0xfffff000,%ecx
      81 c1 00 10 00 00       add    $0x1000,%ecx
L1:   89 48 04                mov    %ecx,0x4(%eax)
      01 0d ## ## ## ##       add    %ecx,mmap_addr
      b8 c0 00 00 00          mov    $0xc0,%eax
      cd 80                   int    $0x80
      e9 ## ## ## ##          jmp    _mmap_sc_addr
*/
    curr_code_ptr = mm_pool._code_cache_info.p_cache_free;
    base_code_ptr = curr_code_ptr;
    *(UINT16 *)curr_code_ptr = 0x1d8b;
    curr_code_ptr += 2;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&aMmapHistory);
    curr_code_ptr += 4;
    *(UINT8 *)curr_code_ptr = 0xa1;
    curr_code_ptr += 1;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&iMapHist);
    curr_code_ptr += 4;
    *(UINT16 *)curr_code_ptr = 0xa340;
    curr_code_ptr += 2;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&iMapHist);
    curr_code_ptr += 4;
    *(UINT32 *)curr_code_ptr = 0x8bc3048d;
    curr_code_ptr += 4;
    *(UINT8 *)curr_code_ptr = 0x1d;
    curr_code_ptr += 1;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&CurrMmapAddr);
    curr_code_ptr += 4;
    *(UINT64 *)curr_code_ptr = 0x00000fffc1f71889;
    curr_code_ptr += 8;
    *(UINT64 *)curr_code_ptr = 0xfffff000e1810c74;
    curr_code_ptr += 8;
    *(UINT64 *)curr_code_ptr = 0x488900001000c181;
    curr_code_ptr += 8;
    *(UINT8 *)curr_code_ptr = 0x04;
    curr_code_ptr += 1;
    *(UINT16 *)curr_code_ptr = 0x0d01;
    curr_code_ptr += 2;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&CurrMmapAddr);
    curr_code_ptr += 4;
    *(UINT64 *)curr_code_ptr = 0xe980cd000000c0b8;
    curr_code_ptr += 8;
    *(UINT32 *)curr_code_ptr = aFile._mmap_sc_addr - curr_code_ptr + 3;
    curr_code_ptr += 4;

    *(UINT8 *)(ADDR)aFile._mmap_sc_addr = 0xe9;
    *(UINT32 *)(ADDR)(aFile._mmap_sc_addr+1) = base_code_ptr - aFile._mmap_sc_addr - 5;

    //mmap64
    base_code_ptr = curr_code_ptr;
    *(UINT16 *)curr_code_ptr = 0x1d8b;
    curr_code_ptr += 2;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&aMmapHistory);
    curr_code_ptr += 4;
    *(UINT8 *)curr_code_ptr = 0xa1;
    curr_code_ptr += 1;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&iMapHist);
    curr_code_ptr += 4;
    *(UINT16 *)curr_code_ptr = 0xa340;
    curr_code_ptr += 2;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&iMapHist);
    curr_code_ptr += 4;
    *(UINT32 *)curr_code_ptr = 0x8bc3048d;
    curr_code_ptr += 4;
    *(UINT8 *)curr_code_ptr = 0x1d;
    curr_code_ptr += 1;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&CurrMmapAddr);
    curr_code_ptr += 4;
    *(UINT64 *)curr_code_ptr = 0x00000fffc1f71889;
    curr_code_ptr += 8;
    *(UINT64 *)curr_code_ptr = 0xfffff000e1810c74;
    curr_code_ptr += 8;
    *(UINT64 *)curr_code_ptr = 0x488900001000c181;
    curr_code_ptr += 8;
    *(UINT8 *)curr_code_ptr = 0x04;
    curr_code_ptr += 1;
    *(UINT16 *)curr_code_ptr = 0x0d01;
    curr_code_ptr += 2;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&CurrMmapAddr);
    curr_code_ptr += 4;
    *(UINT64 *)curr_code_ptr = 0xe980cd000000c0b8;
    curr_code_ptr += 8;
    *(UINT32 *)curr_code_ptr = aFile._mmap64_sc_addr - curr_code_ptr + 3;
    curr_code_ptr += 4;

    *(UINT8 *)(ADDR)aFile._mmap64_sc_addr = 0xe9;
    *(UINT32 *)(ADDR)(aFile._mmap64_sc_addr+1) = base_code_ptr - aFile._mmap64_sc_addr - 5;

/** munmap
     89 15 ## ## ## ##       mov    %edx,spill_edx
     89 35 ## ## ## ##       mov    %esi,spill_esi
     8b 15 ## ## ## ##       mov    base,%edx
     a1 ## ## ## ##          mov    index,%eax
L1:  8b 34 c2                mov    (%edx,%eax,8),%esi
     39 f3                   cmp    %esi,%ebx
     74 03                   je     L2
     48                      dec    %eax
     75 f6                   jne    L1
L2:  3b 05 ## ## ## ##       cmp    index,%eax
     75 1e                   jne    L4
L3:  48                      dec    %eax
     8b 74 c2 04             mov    0x4(%edx,%eax,8),%esi
     f7 c6 01 00 00 00       test   $0x1,%esi
     75 f3                   jne    L3
     8b 74 c2 08             mov    0x8(%edx,%eax,8),%esi
     89 35 ## ## ## ##       mov    %esi,mmap_addr
     a3 ## ## ## ##          mov    %eax,index
     eb 05                   jmp    L5
L4:  83 4c c2 04 01          orl    $0x1,0x4(%edx,%eax,8)
L5:  b8 5b 00 00 00          mov    $0x5b,%eax
     8b 15 ## ## ## ##       mov    spill_edx,%edx
     8b 35 ## ## ## ##       mov    spill_esi,%esi
     cd 80                   int    $0x80
     e9 ## ## ## ##          jmp    munmap_ins_addr
*/
    base_code_ptr = curr_code_ptr;
    *(UINT16 *)curr_code_ptr = 0x1589;
    curr_code_ptr += 2;
    *(UINT32 *)curr_code_ptr = reg_spill_addr;
    curr_code_ptr += 4;
    *(UINT16 *)curr_code_ptr = 0x3589;
    curr_code_ptr += 2;
    *(UINT32 *)curr_code_ptr = reg_spill_addr+4;
    curr_code_ptr += 4;
    *(UINT16 *)curr_code_ptr = 0x158b;
    curr_code_ptr += 2;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&aMmapHistory);
    curr_code_ptr += 4;
    *(UINT8 *)curr_code_ptr = 0xa1;
    curr_code_ptr += 1;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&iMapHist);
    curr_code_ptr += 4;
    *(UINT64 *)curr_code_ptr = 0x480374f339c2348b;
    curr_code_ptr += 8;
    *(UINT32 *)curr_code_ptr = 0x053bf675;
    curr_code_ptr += 4;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&iMapHist);
    curr_code_ptr += 4;
    *(UINT64 *)curr_code_ptr = 0xf704c2748b481e75;
    curr_code_ptr += 8;
    *(UINT64 *)curr_code_ptr = 0x8bf37500000001c6;
    curr_code_ptr += 8;
    *(UINT8 *)curr_code_ptr = 0x74;
    curr_code_ptr += 1;
    *(UINT32 *)curr_code_ptr = 0x358908c2;
    curr_code_ptr += 4;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&CurrMmapAddr);
    curr_code_ptr += 4;
    *(UINT8 *)curr_code_ptr = 0xa3;
    curr_code_ptr += 1;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&iMapHist);
    curr_code_ptr += 4;
    *(UINT16 *)curr_code_ptr = 0x05eb;
    curr_code_ptr += 2;
    *(UINT64 *)curr_code_ptr = 0x005bb80104c24c83;
    curr_code_ptr += 8;
    *(UINT32 *)curr_code_ptr = 0x158b0000;
    curr_code_ptr += 4;
    *(UINT32 *)curr_code_ptr = reg_spill_addr;
    curr_code_ptr += 4;
    *(UINT16 *)curr_code_ptr = 0x358b;
    curr_code_ptr += 2;
    *(UINT32 *)curr_code_ptr = reg_spill_addr+4;
    curr_code_ptr += 4;
    *(UINT16 *)curr_code_ptr = 0x80cd;
    curr_code_ptr += 2;
    *(UINT8 *)curr_code_ptr = 0xe9;
    curr_code_ptr += 1;
    *(UINT32 *)curr_code_ptr = aFile._munmap_sc_addr - curr_code_ptr + 3;
    curr_code_ptr += 4;

    *(UINT8 *)(ADDR)aFile._munmap_sc_addr = 0xe9;
    *(UINT32 *)(ADDR)(aFile._munmap_sc_addr+1) = base_code_ptr - aFile._munmap_sc_addr - 5;

/** mremap
      83 fe 01                cmp    $0x1,%esi
      0f 85 88 00 00 00       jne    L5
      39 d1                   cmp    %edx,%ecx
      0f 8d 7d 00 00 00       jge    L7  
      8b 3d ## ## ## ##       mov    base,%edi
      a1 ## ## ## ##          mov    index,%eax
L1:   8b 34 c7                mov    (%edi,%eax,8),%esi
      39 f3                   cmp    %esi,%ebx
      74 03                   je     L2
      48                      dec    %eax
      75 f6                   jne    L1
L2:   3b 05 ## ## ## ##       cmp    index,%eax
      74 3e                   je     L4
      
      89 de                   mov    %ebx,%esi
      01 d6                   add    %edx,%esi
      3b 74 c7 08             cmp    0x8(%edi,%eax,8),%esi
      7e 56                   jle    L7
      
      83 4c c7 04 01          orl    $0x1,0x4(%edi,%eax,8)
      a1 ## ## ## ##          mov    index,%eax
      40                      inc    %eax
      a3 ## ## ## ##          mov    %eax,index
      8d 34 c7                lea    (%edi,%eax,8),%esi
      8b 3d ## ## ## ##       mov    mmap_addr,%edi
      89 3e                   mov    %edi,(%esi)
      89 d0                   mov    %edx,%eax
      25 00 f0 ff ff          and    $0xfffff000,%eax
      01 c0                   add    %eax,%eax
L3:   89 46 04                mov    %eax,0x4(%esi)
      01 05 ## ## ## ##       add    %eax,mmap_addr
      be 03 00 00 00          mov    $0x3,%esi
      eb 29                   jmp    L5 <main+0x78>
L4:   8d 34 c7                lea    0x0(%edi,%eax,3), %esi
      89 d0                   mov    %edx,%eax
      a9 ff 0f 00 00          test   $0xfff,%eax
      74 0a                   je     L6
      25 00 f0 ff ff          and    $0xfffff000,%eax
      05 00 10 00 00          add    $0x1000,%eax
L6:   2b 46 04                sub    0x4(%esi),%eax
      01 46 04                add    %eax,0x4(%esi)
      01 05 ## ## ## ##       add    %eax,0x8056234
L7:   be 01 00 00 00          mov    $0x1,%esi
      89 df                   mov    %ebx,%edi
L5:   b8 a3 00 00 00          mov    $0xa3,%eax
      cd 80                   int    $0x80
      e9 ## ## ## ##          jmp    mremap_ins_addr
*/
    base_code_ptr = curr_code_ptr;
    *(UINT32 *)curr_code_ptr = 0x0f01fe83;
    curr_code_ptr += 4;
    *(UINT64 *)curr_code_ptr = 0x0fd1390000008885;
    curr_code_ptr += 8;
    *(UINT8 *)curr_code_ptr = 0x8d;
    curr_code_ptr += 1;
    *(UINT32 *)curr_code_ptr = 0x0000007d;
    curr_code_ptr += 4;
    *(UINT16 *)curr_code_ptr = 0x3d8b;
    curr_code_ptr += 2;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&aMmapHistory);
    curr_code_ptr += 4;
    *(UINT8 *)curr_code_ptr = 0xa1;
    curr_code_ptr += 1;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&iMapHist);
    curr_code_ptr += 4;
    *(UINT64 *)curr_code_ptr = 0x480374f339c7348b;
    curr_code_ptr += 8;
    *(UINT32 *)curr_code_ptr = 0x053bf675;
    curr_code_ptr += 4;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&iMapHist);
    curr_code_ptr += 4;
    *(UINT16 *)curr_code_ptr = 0x3e74;
    curr_code_ptr += 2;
    *(UINT32 *)curr_code_ptr = 0xd601de89;
    curr_code_ptr += 4;
    *(UINT32 *)curr_code_ptr = 0x08c7743b;
    curr_code_ptr += 4;
    *(UINT16 *)curr_code_ptr = 0x567e;
    curr_code_ptr += 2;
    *(UINT16 *)curr_code_ptr = 0x4c83;
    curr_code_ptr += 2;
    *(UINT32 *)curr_code_ptr = 0xa10104c7;
    curr_code_ptr += 4;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&iMapHist);
    curr_code_ptr += 4;
    *(UINT16 *)curr_code_ptr = 0xa340;
    curr_code_ptr += 2;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&iMapHist);
    curr_code_ptr += 4;
    *(UINT8 *)curr_code_ptr = 0x8d;
    curr_code_ptr += 1;
    *(UINT32 *)curr_code_ptr = 0x3d8bc734;
    curr_code_ptr += 4;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&CurrMmapAddr);
    curr_code_ptr += 4;
    *(UINT32 *)curr_code_ptr = 0xd0893e89;
    curr_code_ptr += 4;
    *(UINT8 *)curr_code_ptr = 0x25;
    curr_code_ptr += 1;
    *(UINT32 *)curr_code_ptr = 0xfffff000;
    curr_code_ptr += 4;
    *(UINT32 *)curr_code_ptr = 0x4689c001;
    curr_code_ptr += 4;
    *(UINT8 *)curr_code_ptr = 0x04;
    curr_code_ptr += 1;
    *(UINT16 *)curr_code_ptr = 0x0501;
    curr_code_ptr += 2;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&CurrMmapAddr);
    curr_code_ptr += 4;
    *(UINT64 *)curr_code_ptr = 0x8d29eb00000003be;
    curr_code_ptr += 8;
    *(UINT16 *)curr_code_ptr = 0xc734;
    curr_code_ptr += 2;
    *(UINT8 *)curr_code_ptr = 0x89;
    curr_code_ptr += 1;
    *(UINT64 *)curr_code_ptr = 0x0a7400000fffa9d0;
    curr_code_ptr += 8;
    *(UINT64 *)curr_code_ptr = 0x100005fffff00025;
    curr_code_ptr += 8;
    *(UINT64 *)curr_code_ptr = 0x04460104462b0000;
    curr_code_ptr += 8;
    *(UINT16 *)curr_code_ptr = 0x0501;
    curr_code_ptr += 2;
    *(UINT32 *)curr_code_ptr = (UINT32)(ADDR)(&CurrMmapAddr);
    curr_code_ptr += 4;
    *(UINT16 *)curr_code_ptr = 0x01be;
    curr_code_ptr += 2;
    *(UINT64 *)curr_code_ptr = 0x00a3b8df89000000;
    curr_code_ptr += 8;
    *(UINT32 *)curr_code_ptr = 0x80cd0000;
    curr_code_ptr += 4;
    *(UINT8 *)curr_code_ptr = 0xe9;
    curr_code_ptr += 1;
    *(UINT32 *)curr_code_ptr = aFile._mremap_sc_addr - curr_code_ptr + 3;
    curr_code_ptr += 4;

    *(UINT8 *)(ADDR)aFile._mremap_sc_addr = 0xe9;
    *(UINT32 *)(ADDR)(aFile._mremap_sc_addr+1) = base_code_ptr - aFile._mremap_sc_addr - 5;
    CodeCacheAlloc(curr_code_ptr-mm_pool._code_cache_info.p_cache_free);

#ifdef _STATISTIC
    //_exit
    *(UINT16 *)(ADDR)aFile._exit_sc_addr = 0x336a;
    *(UINT8 *)(ADDR)(aFile._exit_sc_addr+2) = 0x68;
    *(UINT32 *)(ADDR)(aFile._exit_sc_addr+3) = (UINT32)(ADDR)BtExit;
    *(UINT8 *)(ADDR)(aFile._exit_sc_addr+7) = 0xcb;
#endif

    mprotect((void *)mprotect_start, mprotect_size, PROT_READ|PROT_EXEC);
}

void RemAllocateReg(REMINDEX irem) {
    REMINDEX jrem;
    int torder;

    if(aFun[ifun]._rem_base==BT_R_ESP && aRem[irem]._offset<aFun[ifun]._callee_arg_off)
        aRem[irem]._allotted_reg = EX_ALIAS_MEM;
    else if(aRem[irem]._rem_size<32 || aRem[irem]._weight==0)
        aRem[irem]._allotted_reg = EX_ALIAS_MEM;
    else if(aRem[irem]._gpr_num && aRem[irem]._xmm_num)
        aRem[irem]._allotted_reg = EX_ALIAS_MEM;
    else if(aRem[irem]._gpr_num && iGpr<EX_XMM8) {
        aRem[irem]._allotted_reg = iGpr;
        iGpr = (AVAIL_REGS)((int)iGpr + 1);
    }
    else if(aRem[irem]._xmm_num && iXmm<EX_MM0) {
        aRem[irem]._allotted_reg = iXmm;
        iXmm = (AVAIL_REGS)((int)iXmm + 1);
    }
    else if(aRem[irem]._gpr_num+aRem[irem]._xmm_num==0) {
        if(iGpr<EX_XMM8 && aRem[irem]._trans_num>aRem[irem]._trans_xmm_num) {
            aRem[irem]._allotted_reg = iGpr;
            iGpr = (AVAIL_REGS)((int)iGpr + 1);
        }
      #ifdef _USE_XMM_HIGH
        else if(aRem[irem]._trans_xmm_num==0 && iXmm<EX_MM0) {
            aRem[irem]._allotted_reg = iXmm;
            torder = 1;
            jrem = aRem[irem]._next;
            while(jrem) {
                if(aRem[jrem]._gpr_num+aRem[jrem]._xmm_num+aRem[jrem]._trans_xmm_num==0) {
                    aRem[jrem]._allotted_reg = iXmm;
                    aRem[jrem]._xmm_order = (UINT8)torder;
                    if(torder==3)
                        break;
                    torder ++;
                }
                jrem = aRem[jrem]._next;
            }
            iXmm = (AVAIL_REGS)((int)iXmm + 1);
        }
      #endif
        else if(iXmm < EX_MM0) {
            aRem[irem]._allotted_reg = iXmm;
            iXmm = (AVAIL_REGS)((int)iXmm + 1);
        }
      #ifdef _USE_MMX_REG
        else if(aRem[irem]._trans_xmm_num==0 && iMmx < EX_XMM0) {
            aRem[irem]._allotted_reg = iMmx;
            iMmx = (AVAIL_REGS)((int)iMmx + 1);
        }
      #endif
        else if(iGpr < EX_XMM8){
            aRem[irem]._allotted_reg = iGpr;
            iGpr = (AVAIL_REGS)((int)iGpr + 1);
        }
        else
            aRem[irem]._allotted_reg = EX_ALIAS_MEM;
    }
  else
      aRem[irem]._allotted_reg = EX_ALIAS_MEM;
    
  #ifdef _NO_STACK_SWITCH
    if(aRem[irem]._allotted_reg == EX_ALIAS_MEM)
        aRem[irem]._allotted_reg = EX_NONE;
  #endif

  #ifdef _NO_REGISTER_PROMOTION
    aRem[irem]._allotted_reg = EX_ALIAS_MEM;
  #endif
}
/** no simd as spill
void RemAllocateReg(REMINDEX irem) {
    REMINDEX jrem;
    int torder;

    if(aFun[ifun]._rem_base==BT_R_ESP && aRem[irem]._offset<aFun[ifun]._callee_arg_off)
        aRem[irem]._allotted_reg = EX_ALIAS_MEM;
    else if(aRem[irem]._rem_size<32 || aRem[irem]._weight==0)
        aRem[irem]._allotted_reg = EX_ALIAS_MEM;
    else if(aRem[irem]._gpr_num && aRem[irem]._xmm_num)
        aRem[irem]._allotted_reg = EX_ALIAS_MEM;
    else if(aRem[irem]._gpr_num && iGpr<EX_XMM8) {
        aRem[irem]._allotted_reg = iGpr;
        iGpr = (AVAIL_REGS)((int)iGpr + 1);
    }
    else if(aRem[irem]._xmm_num && iXmm<EX_MM0) {
        aRem[irem]._allotted_reg = iXmm;
        iXmm = (AVAIL_REGS)((int)iXmm + 1);
    }
    else if(aRem[irem]._gpr_num+aRem[irem]._xmm_num==0 && iGpr<EX_XMM8) {
        aRem[irem]._allotted_reg = iGpr;
        iGpr = (AVAIL_REGS)((int)iGpr + 1);
    }
    else
      aRem[irem]._allotted_reg = EX_ALIAS_MEM;
    
  #ifdef _NO_STACK_SWITCH
    if(aRem[irem]._allotted_reg == EX_ALIAS_MEM)
        aRem[irem]._allotted_reg = EX_NONE;
  #endif

  #ifdef _NO_REGISTER_PROMOTION
    aRem[irem]._allotted_reg = EX_ALIAS_MEM;
  #endif
}
*/

void ModifyRemIns(REMINDEX irem) {
    RMINSINDEX irem_ins;
    INSINDEX iins;
    int i, opr_no;

    for(i=0; i<aRem[irem]._rem_instr->NumOfElem; i++) {
        irem_ins = aRem[irem]._rem_instr->ArrayBase[i];
        iins = aRemIns[irem_ins]._iins;
        opr_no = aRemIns[irem_ins]._operand_no;
        if((aIns[iins]._operand[opr_no].lval.sdword!=aRem[irem]._offset || aIns[iins]._op==BT_Ipush) && (aBb[aIns[iins]._ibb]._last_instr_type>T_ENTRY && aBb[aIns[iins]._ibb]._last_instr_type<T_BRANCH)) {
            aIns[iins]._opt_addr = irem;
            continue;
        }
        
        GenOptimizeStackIns(iins, irem);

        if(aRem[irem]._allotted_reg>EX_NONE && aRem[irem]._allotted_reg<EX_XMM8) {
            aIns[iins]._operand[opr_no].type = BT_OP_REG;
            aIns[iins]._operand[opr_no].base = aRem[irem]._allotted_reg-EX_R8+BT_R_R8D;
        }
        else if(aRem[irem]._allotted_reg>=EX_XMM8 && aRem[irem]._allotted_reg<EX_MM0) {
            aIns[iins]._operand[opr_no].type = BT_OP_XMMREG;
            aIns[iins]._operand[opr_no].base = aRem[irem]._allotted_reg-EX_XMM8+BT_R_XMM8;
        }
        else if(aRem[irem]._allotted_reg>=EX_MM0 && aRem[irem]._allotted_reg<EX_XMM0) {
            aIns[iins]._operand[opr_no].type = BT_OP_MMXREG;
            aIns[iins]._operand[opr_no].base = aRem[irem]._allotted_reg-EX_MM0+BT_R_MM0;
        }
        aIns[iins]._operand[opr_no].index = INVALID;
        aIns[iins]._operand[opr_no].scale = 0;
        aIns[iins]._operand[opr_no].lval.udword = 0;
    }
}

void ModifyArgIns() {
    OUTLPINDEX iOutLoop;
    REMINDEX irem, jrem;
    int i, temp;

    iOutLoop = 1;
    while(iOutLoop < nOutLp) {
        if(aOutLoop[iOutLoop]._flag&LOOP_OPT_CANCLED) {
            iOutLoop ++;
            continue;
        }

        irem = aOutLoop[iOutLoop]._rem_list;
        jrem = INVALID;
        while(irem) {
            if(aRem[irem]._offset >= aFun[ifun]._caller_off) {
                int off = aRem[irem]._offset - aFun[ifun]._caller_off;
                for(i=0; i<aRem[irem]._rem_instr->NumOfElem; i++) {
                    temp = aRem[irem]._rem_instr->ArrayBase[i];
                    DisposeFuncArg(aRemIns[temp]._iins, off);
                }
                
                if(jrem) {
                    aRem[jrem]._next = aRem[irem]._next;
                    //delete irem;
                    irem = jrem;
                }
                else {
                    ASSERT(irem==aOutLoop[iOutLoop]._rem_list, ("Error of coding!\n"));
                    jrem = aRem[irem]._next;
                    aOutLoop[iOutLoop]._rem_list = jrem;

                    //delete irem;
                    irem = jrem;
                    jrem = INVALID;
                    continue;
                }
            }
            
            jrem = irem;
            irem = aRem[irem]._next;
        }

        iOutLoop ++;
    }
}

void ModeSwitch(int direction) {
 #if 0   
    if(direction == COMPAT_TO_LONG)
    {
        cache_ptr[0] = 0x6a;
        cache_ptr[1] = 0x33;
        
        cache_ptr[2] = 0x68;
        *((UINT32 *)(curr_code_ptr+3)) = curr_code_ptr + 8;
        
        cache_ptr[7] = 0xcb;
        
        curr_code_ptr += 8;
    }
    else
    {
        cache_ptr[0] = 0x6a;
        cache_ptr[1] = 0x23;
        
        cache_ptr[2] = 0x68;
        *((UINT32 *)(curr_code_ptr+3)) = curr_code_ptr + 9;

        cache_ptr[7] = 0x48;
        cache_ptr[8] = 0xcb;

        curr_code_ptr += 9;
    }
  #else
    ADDR switch_code_addr = MmAllocGlobalV(8);
    
    if(direction == COMPAT_TO_LONG) {
      #ifdef _USE_MMX_REG
      if(iMmx>EX_MM0) {
        *(UINT16 *)curr_code_ptr = 0x35dd;
        *(UINT32 *)(curr_code_ptr+2) = fpsave_addr;
        curr_code_ptr += 6;
      }
      #endif

        *(UINT16 *)(switch_code_addr+4) = 0x33;
        *(UINT16 *)curr_code_ptr = 0x2dff;
        *((UINT32 *)(curr_code_ptr+2)) = (UINT32)switch_code_addr;
        
        curr_code_ptr += 6;
        *(UINT32 *)switch_code_addr = (UINT32)curr_code_ptr;
    }
    else {
        *(UINT16 *)(switch_code_addr+4) = 0x23;
        *(UINT16 *)curr_code_ptr = 0x2cff;
        *(UINT8 *)(curr_code_ptr+2) = 0x25;
        *((UINT32 *)(curr_code_ptr+3)) = (UINT32)switch_code_addr;

        curr_code_ptr += 7;
        *(UINT32 *)switch_code_addr = (UINT32)curr_code_ptr;

      #ifdef _USE_MMX_REG
      if(iMmx>EX_MM0) {
        *(UINT16 *)curr_code_ptr = 0x25dd;
        *(UINT32 *)(curr_code_ptr+2) = fpsave_addr;
        curr_code_ptr += 6;
      }
      #endif
    }  
  #endif
}

void Preload(REMINDEX irem) {
    while(irem) {
        PreloadSTRem(irem);
        irem = aRem[irem]._next;
    }
}

void Synchronization(REMINDEX irem) {
    REM_INS iremins;
    int i;

    while(irem) {
        if(aFun[ifun]._opt_target==LOOP && aRem[irem]._need_sync)
            SynchronizeSTRem(irem);

        irem = aRem[irem]._next;
    }
}

void MprotectStack(OUTLPINDEX iOutLoop, BOOL flag) {
    REGIONINDEX iregion;
    REMINDEX irem;
    char *cache_ptr = (char *)curr_code_ptr;
    
    int max=-10000000, min=10000000;
    int temp;

  #ifdef _NO_STACK_SWITCH
    return;
  #endif

    return;
  #if 0
    //code to save the registers which will be used in mprotect func
    cache_ptr[0] = 0x89;
    cache_ptr[1] = 0x4;
    cache_ptr[2] = 0x25;
    *(UINT32 *)(cache_ptr+3) = reg_spill_addr;  //eax

    cache_ptr[7] = 0x89;
    cache_ptr[8] = 0x1c;
    cache_ptr[9] = 0x25;
    *(UINT32 *)(cache_ptr+10) = reg_spill_addr+4; //ebx

    cache_ptr[14] = 0x89;
    cache_ptr[15] = 0xc;
    cache_ptr[16] = 0x25;
    *(UINT32 *)(cache_ptr+17) = reg_spill_addr+8;  //ecx

    cache_ptr[21] = 0x89;
    cache_ptr[22] = 0x14;
    cache_ptr[23] = 0x25;
    *(UINT32 *)(cache_ptr+24) = reg_spill_addr+12;  //edx

    curr_code_ptr += 28;

    if((aOutLoop[iOutLoop]._flag&LOOP_OPT_REGION)==0) {
        irem = aOutLoop[iOutLoop]._rem_list;
        while(irem) {
            temp = aRem[irem]._offset;
            if(temp > max)
                max = temp;

            if(temp < min)
                min = temp;
            irem = aRem[irem]._next;
        }
    }
    else {
        iregion = aOutLoop[iOutLoop]._region;
        while(iregion) {
            irem = aRegion[iregion]._rem_list;
            while(irem) {
                temp = aRem[irem]._offset;
                if(temp > max)
                    max = temp;

                if(temp < min)
                    min = temp;
                irem = aRem[irem]._next;
            }
            iregion = aRegion[iregion]._next;
        }
    }

    cache_ptr = (char *)curr_code_ptr;

    /*mov   %esp/%ebp,%ebx
      add    $min,%ebx*/
    cache_ptr[0] = 0x89;
    if(aFun[ifun]._rem_base==BT_R_ESP)
        cache_ptr[1] = 0xe3;
    else
        cache_ptr[1] = 0xeb;
    if(min>-127 && min<127) {
        cache_ptr[2] = 0x83;
        cache_ptr[3] = 0xc3;
        cache_ptr[4] = (INT8)min;
        curr_code_ptr += 5;
    }
    else {
        cache_ptr[2] = 0x81;
        cache_ptr[3] = 0xc3;
        *(int *)(cache_ptr+4) = min;

        curr_code_ptr += 8;
    }

    /*shr    $0xc,%ebx
      shl    $0xc,%ebx
      mov    %esp/%ebp,%ecx*/
    *(UINT32 *)curr_code_ptr = 0xc10cebc1;
    curr_code_ptr += 4;
    if(aFun[ifun]._rem_base==BT_R_ESP)
        *(UINT32 *)curr_code_ptr = 0xe1890ce3;
    else
        *(UINT32 *)curr_code_ptr = 0xe9890ce3;
    curr_code_ptr += 4;

    cache_ptr = (char *)curr_code_ptr;

    /*add    $max,%ecx*/
    if(max>-127 && max<127) {
        cache_ptr[0] = 0x83;
        cache_ptr[1] = 0xc1;
        cache_ptr[2] = (INT8)max;

        curr_code_ptr += 3;
    }
    else {
        cache_ptr[0] = 0x81;
        cache_ptr[1] = 0xc1;
        *(int *)(cache_ptr+2) = max;

        curr_code_ptr += 6;
    }

    /*sub    %ebx,%ecx
      xor    %edx,%edx*/
    if(flag) //prot_none
    {
        *(UINT32 *)curr_code_ptr = 0xd231d929;
        curr_code_ptr += 4;
    }
    else //prot_read | prot_write
    {
        *(UINT32 *)curr_code_ptr = 0x03bad929;
        curr_code_ptr += 4;

        *(UINT32 *)curr_code_ptr = 0;
        curr_code_ptr += 3;
    }

    /*mov    $0x7d,%eax*/
    *(UINT8 *)curr_code_ptr = 0xb8;
    curr_code_ptr += 1;

    *(UINT32 *)curr_code_ptr = 0x7d;
    curr_code_ptr += 4;

    /*int    $0x80*/
    *(UINT8 *)curr_code_ptr = 0xcd;
    curr_code_ptr += 1;
    *(UINT8 *)curr_code_ptr = 0x80;
    curr_code_ptr += 1;

    //code to restore the registers which will be used in mprotect func
    cache_ptr = (char *)curr_code_ptr;

    cache_ptr[0] = 0x8b;
    cache_ptr[1] = 0x4;
    cache_ptr[2] = 0x25;
    *(UINT32 *)(cache_ptr+3) = reg_spill_addr;  //eax

    cache_ptr[7] = 0x8b;
    cache_ptr[8] = 0x1c;
    cache_ptr[9] = 0x25;
    *(UINT32 *)(cache_ptr+10) = reg_spill_addr+4;  //ebx

    cache_ptr[14] = 0x8b;
    cache_ptr[15] = 0xc;
    cache_ptr[16] = 0x25;
    *(UINT32 *)(cache_ptr+17) = reg_spill_addr+8;  //ecx

    cache_ptr[21] = 0x8b;
    cache_ptr[22] = 0x14;
    cache_ptr[23] = 0x25;
    *(UINT32 *)(cache_ptr+24) = reg_spill_addr+12;  //edx

    curr_code_ptr += 28;
  #endif
}

void StackSwitch() {
    INSINDEX iins;
    int arg_off, i = 0;
    char *cache_ptr = (char *)curr_code_ptr;

    if(aFun[ifun]._flag&FUN_NO_RESTORE_ESP) {
        iins = aBb[aFun[ifun]._ibb_entry]._ins_first;
        aIns[iins]._opt_addr = (ADDR32)curr_code_ptr;
        for(i=0; i<aIns[iins]._size; i++)
            *(UINT8 *)(curr_code_ptr+i) = aIns[iins]._binary[i];
        curr_code_ptr += aIns[iins]._size;

        iins ++;
        aIns[iins]._opt_addr = (ADDR32)curr_code_ptr;
        for(i=0; i<aIns[iins]._size; i++)
            *(UINT8 *)(curr_code_ptr+i) = aIns[iins]._binary[i];
        curr_code_ptr += aIns[iins]._size;

        aBb[aFun[ifun]._ibb_entry]._ins_first = iins + 1;
        i = 0;
        cache_ptr = (char *)curr_code_ptr;
    }
    //mov esp, old_esp
    cache_ptr[i++] = 0x89;
    cache_ptr[i++] = 0x25;
    *(UINT32 *)(cache_ptr+i) = (UINT32)(UINT64)(&(aFun[ifun]._old_esp));
    i += 4;

    //mov eax, temp_register
    cache_ptr[i++] = 0xa3;
    *(UINT32 *)(cache_ptr+i) = reg_spill_addr;
    i += 4;

    //cmp $0xa0000000, %esp
    cache_ptr[i++] = 0x81;
    cache_ptr[i++] = 0xfc;
    *(UINT32 *)(cache_ptr+i) = (UINT32)(STACK_AREA_START+vm_stack_size+PAGE_SIZE);
    i += 4;

    cache_ptr[i++] = 0x7f;
    cache_ptr[i++] = 0x0b;

    //and %esp, 0x0f
    cache_ptr[i++] = 0x83;
    cache_ptr[i++] = 0xe4;
    cache_ptr[i++] = 0x0f;

    //or new_esp, %esp
    cache_ptr[i++] = 0x81;
    cache_ptr[i++] = 0xcc;
    *(UINT32 *)(cache_ptr+i) = (UINT32)(opt_stack->_shadow_stack_base);
    i += 4;

    //jmp +X
    cache_ptr[i++] = 0xeb;
    cache_ptr[i++] = 0x10;

    //mov %esp, %eax
    cache_ptr[i++] = 0x89;
    cache_ptr[i++] = 0xe0;

    //and $0xfffff000,%esp
    cache_ptr[i++] = 0x81;
    cache_ptr[i++] = 0xe4;
    *(UINT32 *)(cache_ptr+i) = 0xfffff000;
    i += 4;

    //and $0xf, %eax
    cache_ptr[i++] = 0x83;
    cache_ptr[i++] = 0xe0;
    cache_ptr[i++] = 0x0f;

    //sub 0x10, %esp
    cache_ptr[i++] = 0x83;
    cache_ptr[i++] = 0xec;
    cache_ptr[i++] = 0x10;

    //or %%eax, %%esp
    cache_ptr[i++] = 0x09;
    cache_ptr[i++] = 0xc4;
    
    if(aFun[ifun]._max_off-aFun[ifun]._caller_off>=0) {
        //mov old_esp, eax
        cache_ptr[i++] = 0xa1;
        *(UINT32 *)(cache_ptr+i) = (UINT32)(UINT64)(&(aFun[ifun]._old_esp));
        i += 4;

        arg_off = (aFun[ifun]._max_off-aFun[ifun]._caller_off+16)/16*16 - 4;  //align the stack

        while(arg_off>=0) {
            if(arg_off > 127) {
                cache_ptr[i++] = 0xff;
                cache_ptr[i++] = 0xb0;
                *(int *)(cache_ptr+i) = arg_off;
                i += 4;
            }
            else {
                cache_ptr[i++] = 0xff;
                cache_ptr[i++] = 0x70;
                cache_ptr[i++] = (char)arg_off;
            }

            arg_off -= 4;
        }
    }
    //mov temp_register, eax
    cache_ptr[i++] = 0xa1;
    *(UINT32 *)(cache_ptr+i) = reg_spill_addr;
    i+= 4;

    curr_code_ptr += i;
}

BBINDEX HandleCallInOptCode(INSINDEX iins) {
    BBINDEX ibb, tbb;
    INSINDEX tins;
    REMINDEX trem;
    RMINSINDEX trem_ins;
    char reg_instr_buff[REGINS_BUFF_SIZE];
    ADDR buff_ptr;

    char *p_code_cache, *p_instr_code;

    AVAIL_REGS unreg_regname[REG_BUFF_NUM], reg_regname[REG_BUFF_NUM];
    int unreg_regnum, reg_regnum;

    int i, j;
    int rem_off_bak, push_off = 0;
    
    ibb = aIns[iins]._ibb;
    while(iins<aBb[ibb]._ins_last&& aIns[iins]._op!=BT_Ipush) {
        GenX64Code(iins);
        iins = aIns[iins]._succ;
    }

    buff_ptr = (ADDR)reg_instr_buff;
    if(aIns[iins]._op==BT_Ipush) {
        tbb = ibb;
        tins = iins;

        unreg_regnum = 0;
        reg_regnum = 0;

        while(aBb[tbb]._last_instr_type>T_ENTRY && aBb[tbb]._last_instr_type<T_BRANCH) {
            while(tins) {
                if(aIns[tins]._op==BT_Ipush)
                    push_off += 4;
                
                tins = aIns[tins]._succ;
            }
            tbb = aBb[tbb]._next;
            tins = aBb[tbb]._ins_first;
        }

        tbb = ibb;
        tins = iins;

        while(aBb[tbb]._last_instr_type>T_ENTRY && aBb[tbb]._last_instr_type<T_BRANCH) {
            while(tins < aBb[tbb]._ins_last) {
                if(aIns[tins]._opt_addr) {
                    trem = aIns[tins]._opt_addr;
                    t_array = aRem[trem]._rem_instr;
                    
                    for(i=0; i<t_array->NumOfElem; i++) {
                        trem_ins = t_array->ArrayBase[i];
                        if(aRemIns[trem_ins]._iins == tins)
                            break;
                    }
                    ASSERT(i<t_array->NumOfElem, ("Error occured in handle push.\n"));
                    if(aIns[tins]._src_opnd_start <= aRemIns[trem_ins]._operand_no) {
                        for(j=0; j<reg_regnum; j++) {
                            if(reg_regname[j]==aRem[trem]._allotted_reg)
                                break;
                        }

                        if(j==reg_regnum) {
                            for(j=0; j<unreg_regnum; j++) {
                                if(unreg_regname[j]==aRem[trem]._allotted_reg)
                                    break;
                            }

                            if(j==unreg_regnum) {
                                unreg_regname[unreg_regnum] = aRem[trem]._allotted_reg;
                                unreg_regnum += 1;
                                SynchronizeSTRem(trem);
                            }
                        }
                    }
                    else {
                        for(j=0; j<reg_regnum; j++) {
                            if(reg_regname[j]==aRem[trem]._allotted_reg)
                                break;
                        }

                        if(j==reg_regnum) {
                            reg_regname[reg_regnum] = aRem[trem]._allotted_reg;
                            reg_regnum += 1;
                            rem_off_bak = aRem[trem]._offset;
                            aRem[trem]._offset = rem_off_bak+push_off;
                            PreloadSTRem(trem);
                            aRem[trem]._offset = rem_off_bak;
                        }
                    }
                }
                
                tins = aIns[tins]._succ;
            }
            tbb = aBb[tbb]._next;
            tins = aBb[tbb]._ins_first;
        }
    }

    ModeSwitch(LONG_TO_COMPAT);

    while(1) {
        while(iins < aBb[aIns[iins]._ibb]._ins_last) {
            aIns[iins]._opt_addr = (ADDR32)curr_code_ptr;
            for(i=0; i<aIns[iins]._size; i++)
                *(char *)(curr_code_ptr+i) = aIns[iins]._binary[i];

            curr_code_ptr += aIns[iins]._size;

            iins = aIns[iins]._succ;
        }

        //call instruction                
        aIns[iins]._opt_addr = (ADDR32)curr_code_ptr;
        p_code_cache = (char *)curr_code_ptr;
        p_instr_code = aIns[iins]._binary;

        if(p_instr_code[0]==(char)0xff && (p_instr_code[1]&0x0c0)==0 && (p_instr_code[1]&0x07)==0x5) {
            p_code_cache[0] = p_instr_code[0];
            p_code_cache[1] = (p_instr_code[1]&0xf8)|0x4;
            p_code_cache[2] = 0x25;

            *(int *)(p_code_cache+3) = *(int *)(p_instr_code+2);

            curr_code_ptr += 7;
        }
        else {
            for(i=0; i<aIns[iins]._size; i++)
                p_code_cache[i] = p_instr_code[i];
            
            curr_code_ptr = curr_code_ptr + aIns[iins]._size;
        }
        
        if(aBb[aBb[ibb]._next]._last_instr_type>T_ENTRY && aBb[aBb[ibb]._next]._last_instr_type<T_BRANCH) {
            ibb = aBb[ibb]._next;
            iins = aBb[ibb]._ins_first;
        }
        else
            break;
    }

    ModeSwitch(COMPAT_TO_LONG);
    
    if(buff_ptr-(ADDR)reg_instr_buff) {
        for(i=0; i<buff_ptr-(ADDR)reg_instr_buff; i++)
            *(char *)(curr_code_ptr+i) = reg_instr_buff[i];

        curr_code_ptr += i;
    }

  return ibb;
}

void OptimizingBb(BBINDEX ibb) {
    INSINDEX iins, jins, tins;
    BBLKINDEX ibblk;
    OPERAND *p_operand;
    char *instr_code;
    REGISTER_TYPE d_reg, s_reg;
    int i, j, m, n;

    BOOL promotable;

    ibblk = aBb[ibb]._succ_bb;
    if(aBblk[ibblk]._ibb!=ibb)
        ibblk = aBblk[ibblk]._next;
  #if 0  //code to delelte more instructions in one-bb-loop, debug doesnot pass.
    if(aBblk[ibblk]._ibb == ibb) {
        iins = aBb[ibb]._ins_first;
        while(iins) {
            if(aIns[iins]._op==BT_Imov && aIns[iins]._operand[1].type==BT_OP_REG &&\
                aIns[iins]._operand[1].base>BT_R_EDI && aIns[iins]._operand[1].base<BT_R_RAX) {
                d_reg = aIns[iins]._operand[0].base;
                s_reg = aIns[iins]._operand[1].base;

                for(jins=iins+1; jins<=aBb[ibb]._ins_last; jins++) {
                    if(aIns[jins]._use&aIns[iins]._def) {
                        if((aIns[jins]._def&aIns[iins]._def) && aIns[jins]._op!=BT_Imov)
                            break;
                        if(aIns[jins]._op==BT_Imov && (aIns[jins]._binary[0]&0xf0)==0xa0)
                            break;
                        if(aIns[jins]._operand[1].base<=BT_R_DI && aIns[jins]._operand[1].base+16==d_reg)
                            break;

                        if(aIns[jins]._def&aIns[iins]._def)
                            j = aIns[jins]._src_opnd_start;
                        else
                            j = 0;

                        for(; j<aIns[jins]._opndnum; j++) {
                            p_operand = aIns[jins]._operand + j;

                            if(p_operand->base==d_reg || p_operand->index==d_reg) {
                                instr_code = aIns[jins]._binary;
                                n = 0;
                                if(instr_code[n] == 0x66 || instr_code[n] == (char)0xf2 || instr_code[n] == (char)0xf3)
                                    n += 1;
                                if((instr_code[n]&0x0f8) != 0x40) {
                                    for(m=aIns[jins]._size; m>n; m--)
                                        instr_code[m] = instr_code[m-1];

                                    m = n;
                                    instr_code[n++] = 0x40;
                                    aIns[jins]._size ++;
                                }
                                else {
                                    m = n;
                                    n ++;
                                }

                                if(instr_code[n] == 0x0f)
                                    n += 1;

                                if(p_operand->type == BT_OP_MEM) {
                                    //ASSERT(p_operand->base!=p_operand->index, ("unhandled case in optimizing BB.\n"));
                                    if(p_operand->base == d_reg) {
                                        instr_code[m] = instr_code[m] | 0x1;
                                        if(p_operand->index==d_reg)
                                            instr_code[m] = instr_code[m] | 0x2;

                                        n ++;
                                        if((instr_code[n]&0x0c0)==0 && s_reg == BT_R_R13D) {
                                            instr_code[n] |= 0x40;
                                            instr_code[aIns[jins]._size++] = 0;
                                        }
                                        if(p_operand->index == BT_NONE) {
                                            if(s_reg==BT_R_R12D) {
                                                for(m=aIns[jins]._size; m>n+1; m--)
                                                    instr_code[m] = instr_code[m-1];
                                                instr_code[m] = 0x24;
                                                aIns[jins]._size ++;
                                            }
                                        }
                                        else
                                            n ++;

                                        instr_code[n] = (instr_code[n] & 0x0f8) | (s_reg-BT_R_R8D);
                                        if(p_operand->index==d_reg)
                                            instr_code[n] = (instr_code[n] & 0x0c7) | ((s_reg-BT_R_R8D)<<3);
                                    }
                                    else {
                                        instr_code[m] = instr_code[m] | 0x2;
                                        n += 2; //opcode & modrm
                                        instr_code[n] = (instr_code[n] & 0x0c7) | ((s_reg-BT_R_R8D)<<3);
                                    }

                                    aIns[jins]._use = aIns[jins]._use & (~aIns[iins]._def);
                                    aIns[jins]._use = aIns[jins]._use | aIns[iins]._use;

                                    if(j<aIns[jins]._dest_opnd_num && (aIns[jins]._def&aIns[iins]._def))
                                        aIns[jins]._def |= aIns[iins]._use;
                                }
                                else if(p_operand->type == BT_OP_REG) {
                                    if(aIns[jins]._op!=BT_Ipextrd)
                                        n += 1; //opcode 
                                    else
                                        n += 2;
                                    if((instr_code[n]&0x7)==d_reg-BT_R_EAX) {
                                        instr_code[m] = instr_code[m] | 0x1;
                                        instr_code[n] = (instr_code[n] & 0x0f8) | (s_reg-BT_R_R8D);
                                    }
                                    else {
                                        ASSERT((instr_code[n]&0x38)==(d_reg-BT_R_EAX)<<3, ("The src reg does not in the reg bits.\n"));
                                        instr_code[m] = instr_code[m] | 0x4;
                                        instr_code[n] = (instr_code[n] & 0x0c7) | ((s_reg-BT_R_R8D)<<3);
                                    }

                                    aIns[jins]._use &= (~aIns[iins]._def);
                                    aIns[jins]._use |= aIns[iins]._use;

                                    if(j<aIns[jins]._dest_opnd_num && (aIns[jins]._def&aIns[iins]._def)) {
                                        aIns[jins]._def &= (~aIns[iins]._def);
                                        aIns[jins]._def |= aIns[iins]._use;
                                    }
                                }
                            }
                        }
                    }
                    else if(aIns[jins]._def & aIns[iins]._def)
                        break;
                }

                if(jins<aBb[ibb]._ins_last) {
                    if((aIns[jins]._use&aIns[iins]._def)==0) {
                        aIns[iins]._size = 0;

                        if(aBb[ibb]._ins_first == iins) {
                            jins = aIns[iins]._succ;
                            aBb[ibb]._ins_first = jins;
                            aIns[jins]._prev = INVALID;
                        }
                        else {
                            jins = aIns[iins]._prev;
                            aIns[jins]._succ = aIns[iins]._succ;
                            aIns[aIns[iins]._succ]._prev = jins;
                        }
                    }
                }
                else {
                    promotable = FALSE;
                    tins = aBb[ibb]._ins_first;
                    while(tins) {
                        if(aIns[tins]._use&aIns[iins]._def) 
                            break;
                        if(aIns[tins]._def&aIns[iins]._def){
                            promotable = TRUE;
                            break;
                        }
                        tins = aIns[tins]._succ;
                    }

                    if(promotable) {
                        for(i=0; i<aIns[iins]._size; i++)
                            tCodeCache[ItCodeCache++] = aIns[iins]._binary[i];

                        ASSERT(ItCodeCache<MAX_T_CODE_CACHE, ("Temp code cache is overflow.\n"));

                        if(aBb[ibb]._ins_first == iins) {
                            jins = aIns[iins]._succ;
                            aBb[ibb]._ins_first = jins;
                            aIns[jins]._prev = INVALID;
                        }
                        else {
                            jins = aIns[iins]._prev;
                            aIns[jins]._succ = aIns[iins]._succ;
                            aIns[aIns[iins]._succ]._prev = jins;
                        }
                        //aIns[iins]._succ = INVALID;
                    }
                }
            }

            iins = aIns[iins]._succ;
        }

        return;
    }
  #endif
    iins = aBb[ibb]._ins_first;
    //iins = aIns[iins]._succ;
    while(iins) {
        if(aIns[iins]._op==BT_Imov && aIns[iins]._operand[1].type==BT_OP_REG &&\
            aIns[iins]._operand[1].base>BT_R_EDI && aIns[iins]._operand[1].base<BT_R_RAX) {
            ASSERT(aIns[iins]._operand[0].type==BT_OP_REG, ("unexpected case.\n"));
            d_reg = aIns[iins]._operand[0].base;
            s_reg = aIns[iins]._operand[1].base;
            
            for(jins=iins+1; jins<=aBb[ibb]._ins_last; jins++) {
                if(aIns[jins]._use&aIns[iins]._def) {
                    if((aIns[jins]._def&aIns[iins]._def) && aIns[jins]._op!=BT_Imov)
                        break;
                    if(aIns[jins]._op==BT_Imov && (aIns[jins]._binary[0]&0xf0)==0xa0)
                        break;
                    if(aIns[jins]._operand[1].base<=BT_R_DI && aIns[jins]._operand[1].base+16==d_reg)
                        break;

                    if(aIns[jins]._def&aIns[iins]._def)
                        j = aIns[jins]._src_opnd_start;
                    else
                        j = 0;
                    for(; j<aIns[jins]._opndnum; j++) {
                        p_operand = aIns[jins]._operand + j;

                        if(p_operand->base==d_reg || p_operand->index==d_reg) {
                            instr_code = aIns[jins]._binary;
                            n = 0;
                            if(instr_code[n] == 0x66 || instr_code[n] == (char)0xf2 || instr_code[n] == (char)0xf3)
                                n += 1;
                            if((instr_code[n]&0x0f8) != 0x40) {
                                for(m=aIns[jins]._size; m>n; m--)
                                    instr_code[m] = instr_code[m-1];

                                m = n;
                                instr_code[n++] = 0x40;
                                aIns[jins]._size ++;
                            }
                            else {
                                m = n;
                                n ++;
                            }

                            if(instr_code[n] == 0x0f)
                                n += 1;

                            if(p_operand->type == BT_OP_MEM) {
                                //ASSERT(p_operand->base!=p_operand->index, ("unhandled case in optimizing BB.\n"));
                                if(p_operand->base == d_reg) {
                                    instr_code[m] = instr_code[m] | 0x1;
                                    if(p_operand->index==d_reg)
                                        instr_code[m] = instr_code[m] | 0x2;

                                    n ++;
                                    if((instr_code[n]&0x0c0)==0 && s_reg == BT_R_R13D) {
                                        instr_code[n] |= 0x40;
                                        instr_code[aIns[jins]._size++] = 0;
                                    }
                                    if(p_operand->index == BT_NONE) {
                                        if(s_reg==BT_R_R12D) {
                                            for(m=aIns[jins]._size; m>n+1; m--)
                                                instr_code[m] = instr_code[m-1];
                                            instr_code[m] = 0x24;
                                            aIns[jins]._size ++;
                                        }
                                    }
                                    else
                                        n ++;

                                    instr_code[n] = (instr_code[n] & 0x0f8) | (s_reg-BT_R_R8D);
                                    if(p_operand->index==d_reg)
                                        instr_code[n] = (instr_code[n] & 0x0c7) | ((s_reg-BT_R_R8D)<<3);
                                }
                                else {
                                    instr_code[m] = instr_code[m] | 0x2;
                                    n += 2; //opcode & modrm
                                    instr_code[n] = (instr_code[n] & 0x0c7) | ((s_reg-BT_R_R8D)<<3);
                                }

                                aIns[jins]._use = aIns[jins]._use & (~aIns[iins]._def);
                                aIns[jins]._use = aIns[jins]._use | aIns[iins]._use;

                                if(j<aIns[jins]._dest_opnd_num && (aIns[jins]._def&aIns[iins]._def))
                                    aIns[jins]._def |= aIns[iins]._use;
                            }
                            else if(p_operand->type == BT_OP_REG) {
                                if(aIns[jins]._op!=BT_Ipextrd)
                                    n += 1; //opcode 
                                else
                                    n += 2;
                                if((instr_code[n]&0x7)==d_reg-BT_R_EAX) {
                                    instr_code[m] = instr_code[m] | 0x1;
                                    instr_code[n] = (instr_code[n] & 0x0f8) | (s_reg-BT_R_R8D);
                                }
                                else {
                                    ASSERT((instr_code[n]&0x38)==(d_reg-BT_R_EAX)<<3, ("The src reg does not in the reg bits.\n"));
                                    instr_code[m] = instr_code[m] | 0x4;
                                    instr_code[n] = (instr_code[n] & 0x0c7) | ((s_reg-BT_R_R8D)<<3);
                                }

                                aIns[jins]._use = aIns[jins]._use & (~aIns[iins]._def);
                                aIns[jins]._use = aIns[jins]._use | aIns[iins]._use;

                                if(j<aIns[jins]._dest_opnd_num && (aIns[jins]._def&aIns[iins]._def))
                                    aIns[jins]._def |= aIns[iins]._use;
                            }
                        }
                    }
                }
                if(aIns[jins]._def & aIns[iins]._def)
                    break;
            }

            if(jins<aBb[ibb]._ins_last && (aIns[jins]._use&aIns[iins]._def)==0) {
                aIns[iins]._size = 0;
                if(aBb[ibb]._ins_first == iins) {
                    jins = aIns[iins]._succ;
                    aBb[ibb]._ins_first = jins;
                    aIns[jins]._prev = INVALID;
                }
                else {
                    jins = aIns[iins]._prev;
                    aIns[jins]._succ = aIns[iins]._succ;
                    aIns[aIns[iins]._succ]._prev = jins;
                }
            }
        }
        else if((aIns[iins]._op==BT_Imovaps||aIns[iins]._op==BT_Imovapd) && aIns[iins]._operand[1].type==BT_OP_XMMREG && \
            aIns[iins]._operand[1].base>=BT_R_XMM8 && aIns[iins]._operand[1].base<=BT_R_XMM15) {
            ASSERT(aIns[iins]._operand[0].type==BT_OP_XMMREG, ("unexpected case.\n"));
            d_reg = aIns[iins]._operand[0].base;
            s_reg = aIns[iins]._operand[1].base;
            
            for(jins=iins+1; jins<=aBb[ibb]._ins_last; jins++) {
                if(aIns[jins]._use&aIns[iins]._def) {
                    if(aIns[jins]._def&aIns[iins]._def)
                        break;

                    for(j=0; j<aIns[jins]._opndnum; j++) {
                        p_operand = aIns[jins]._operand + j;

                        if(p_operand->base==d_reg) {
                            ASSERT(p_operand->type == BT_OP_XMMREG, ("unexpected case.\n"));
                            instr_code = aIns[jins]._binary;
                            n = 0;
                            if(instr_code[n] == 0x66 || instr_code[n] == (char)0xf2 || instr_code[n] == (char)0xf3)
                                n += 1;
                            if((instr_code[n]&0x0f8) != 0x40) {
                                for(m=aIns[jins]._size; m>n; m--)
                                    instr_code[m] = instr_code[m-1];

                                m = n;
                                instr_code[n++] = 0x40;
                                aIns[jins]._size ++;
                            }
                            else {
                                m = n;
                                n ++;
                            }

                            if(instr_code[n] == 0x0f)
                                n += 1;

                            if(aIns[jins]._op!=BT_Ipextrd)
                                n += 1; //opcode 
                            else
                                n += 2;
                            if((instr_code[n]&0x7)==d_reg-BT_R_XMM0) {
                                instr_code[m] = instr_code[m] | 0x1;
                                instr_code[n] = (instr_code[n] & 0x0f8) | (s_reg-BT_R_XMM8);
                            }
                            else {
                                ASSERT((instr_code[n]&0x38)==(d_reg-BT_R_XMM0)<<3, ("The src reg does not in the reg bits.\n"));
                                instr_code[m] = instr_code[m] | 0x4;
                                instr_code[n] = (instr_code[n] & 0x0c7) | ((s_reg-BT_R_XMM8)<<3);
                            }

                            aIns[jins]._use = aIns[jins]._use & (~aIns[iins]._def);
                            aIns[jins]._use = aIns[jins]._use | aIns[iins]._use;

                            if(j<aIns[jins]._dest_opnd_num && (aIns[jins]._def&aIns[iins]._def))
                                aIns[jins]._def |= aIns[iins]._use;
                        }
                    }
                }
                if(aIns[jins]._def & aIns[iins]._def)
                    break;
            }

            if(jins<aBb[ibb]._ins_last && (aIns[jins]._use&aIns[iins]._def)==0) {
                aIns[iins]._size = 0;
                if(aBb[ibb]._ins_first == iins) {
                    jins = aIns[iins]._succ;
                    aBb[ibb]._ins_first = jins;
                    aIns[jins]._prev = INVALID;
                }
                else {
                    jins = aIns[iins]._prev;
                    aIns[jins]._succ = aIns[iins]._succ;
                    aIns[aIns[iins]._succ]._prev = jins;
                }
            }
        }

        iins = aIns[iins]._succ;
    }

  #if 0
    bins = nIns - 1;
    b_reg = BT_R_XMM8;
    iins = aBb[ibb]._ins_first;
    iins = aIns[iins]._succ;
    while(iins) {
        if((aIns[iins]._op>=BT_Idivsd && aIns[iins]._op<=BT_Isqrtsd)) {
            if(aIns[iins]._operand[1].type == BT_OP_MEM) {
                aIns[nIns]._op = BT_Imovsd_sse;
                aIns[nIns]._opndnum = 2;
                aIns[nIns]._src_opnd_num = 1;
                aIns[nIns]._dest_opnd_num = 1;
                aIns[nIns]._src_opnd_start = 1;
                aIns[nIns]._operand[0].type = BT_OP_XMMREG;
                aIns[nIns]._operand[0].size = aIns[iins]._operand[0].size;
                b_reg = (b_reg-BT_R_XMM8)%3 + BT_R_XMM8;
                aIns[nIns]._operand[0].base = b_reg;
                aIns[nIns]._operand[1] = aIns[iins]._operand[1];
                aIns[nIns]._ibb = ibb;
                aIns[nIns]._binary[0] = 0xf2;
                aIns[nIns]._binary[1] = 0x44;
                aIns[nIns]._binary[2] = 0x0f;
                aIns[nIns]._binary[3] = 0x10;
                if((aIns[iins]._binary[1]&0x0f8)==0x40) {
                    aIns[nIns]._binary[1] = aIns[nIns]._binary[1] | (aIns[iins]._binary[1]&0x3);
                    for(i=aIns[iins]._size; i>3; i--)
                        aIns[nIns]._binary[i] = aIns[iins]._binary[i];
                    aIns[nIns]._size = aIns[iins]._size;
                }
                else {
                    for(i=aIns[iins]._size; i>3; i--)
                        aIns[nIns]._binary[i] = aIns[iins]._binary[i-1];
                    aIns[nIns]._size = aIns[iins]._size + 1;
                }
                aIns[nIns]._binary[4] = (aIns[nIns]._binary[4]&0x0c7) | ((b_reg-BT_R_XMM8)<<3);

                aIns[nIns]._prev = aIns[iins]._prev;
                aIns[nIns]._succ = iins;

                aIns[iins]._operand[1].type = BT_OP_XMMREG;
                aIns[iins]._operand[1].lval.udword = 0;
                aIns[iins]._operand[1].base = b_reg;
                aIns[iins]._operand[1].index = BT_NONE;
                aIns[iins]._operand[1].scale = 0;
                if((aIns[iins]._binary[1]&0x0f8)!=0x40) {
                    aIns[iins]._binary[4] = aIns[iins]._binary[3];
                    aIns[iins]._binary[3] = aIns[iins]._binary[2];
                    aIns[iins]._binary[2] = aIns[iins]._binary[1];
                }
                aIns[iins]._binary[1] = 0x41;
                aIns[iins]._binary[4] = (aIns[iins]._binary[4]&0x0f8)|0x0c0|(b_reg-BT_R_XMM8);
                aIns[iins]._size = 5;

                aIns[aIns[iins]._prev]._succ = nIns;
                aIns[iins]._prev = nIns;

                jud = aBb[ibb]._ins_num + nIns - bins;
                aIns[jins]._use[0] = aIns[nIns]._operand[1].base;
                aIns[jins]._use[1] = aIns[nIns]._operand[1].index;
                aIns[jins]._def[0] = b_reg;
                jud = iins - fins;
                aIns[jins]._use[0] = b_reg;
                aIns[jins]._use[1] = aIns[iins]._operand[0].base;
                aIns[jins]._use[2] = BT_NONE;

                nIns ++;
                b_reg = b_reg + 1;
            }
        }

        iins = aIns[iins]._succ;
    }

    b_reg = BT_R_XMM8;
    iins = aBb[ibb]._ins_first;
    iins = aIns[iins]._succ;
    while(iins) {
        need_advance = FALSE;
        if(iins<=aBb[ibb]._ins_last)
            jud = iins - fins;
        else
            jud = aBb[ibb]._ins_num + iins - bins;
        d_reg = aIns[jins]._def[0];

        if((aIns[iins]._op==BT_Imov||aIns[iins]._op==BT_Imovsd_sse||aIns[iins]._op==BT_Imovd) && aIns[iins]._operand[1].type==BT_OP_MEM) {
            jins = aIns[iins]._succ;
            if(jins<=aBb[ibb]._ins_last)
                tud = jins - fins;
            else
                tud = aBb[ibb]._ins_num + jins - bins;
            if(aUseDef[tud]._use[0]==d_reg || aUseDef[tud]._use[1]==d_reg || aUseDef[tud]._use[2]==d_reg)
                need_advance = TRUE;

            jins = aIns[jins]._succ;
            if(jins<=aBb[ibb]._ins_last)
                tud = jins - fins;
            else
                tud = aBb[ibb]._ins_num + jins - bins;
            if(aUseDef[tud]._use[0]==d_reg || aUseDef[tud]._use[1]==d_reg || aUseDef[tud]._use[2]==d_reg)
                need_advance = TRUE;

            if(need_advance) {
                n = 0;
                jins = aIns[iins]._prev;
                while(jins>aBb[ibb]._ins_first && n<=5) {
                    if(jins<=aBb[ibb]._ins_last)
                        tud = jins - fins;
                    else
                        tud = aBb[ibb]._ins_num + jins - bins;

                    d_reg = aUseDef[tud]._def[0];
                    if(d_reg!=BT_NONE && (aIns[jins]._use[0]==d_reg||aIns[jins]._use[1]==d_reg||aIns[jins]._use[2]==d_reg))
                        break;  //||aIns[jins]._def[0]==d_reg need for unoptimized code
                    d_reg = aUseDef[tud]._def[1];
                    if(d_reg!=BT_NONE && (aIns[jins]._use[0]==d_reg||aIns[jins]._use[1]==d_reg||aIns[jins]._use[2]==d_reg))
                        break;

                    d_reg = aIns[jins]._def[0];
                    if(aUseDef[tud]._use[0]==d_reg || aUseDef[tud]._use[1]==d_reg || aUseDef[tud]._use[2]==d_reg||aUseDef[tud]._def[0]==d_reg)
                        break;
                    n ++;
                    jins = aIns[jins]._prev;
                }

                if(n>2) {
                    jins = aIns[jins]._succ;
                    while(!IS_LONGLATENCY_INS(aIns[jins]._op) && n>2) {
                        jins = aIns[jins]._succ;
                        n --;
                    }
                    if(n>10) {
                        while(aIns[aIns[jins]._succ]._op==BT_Imovsd_sse && n>10) {
                            jins = aIns[jins]._succ;
                            n --;
                        }
                    }

                    aIns[aIns[iins]._prev]._succ = aIns[iins]._succ;
                    aIns[aIns[iins]._succ]._prev = aIns[iins]._prev;
                    aIns[iins]._prev = jins;
                    aIns[iins]._succ = aIns[jins]._succ;
                    aIns[aIns[jins]._succ]._prev = iins;
                    aIns[jins]._succ = iins;
                }
                else if(aIns[iins]._op == BT_Imovsd_sse && jins!=aBb[ibb]._ins_first && d_reg==aIns[jins]._def[0]){  //dedicated for 410.bwaves, for other benchmarks, needed to be tuned ******
                    ASSERT(iins<aBb[ibb]._ins_last, ("unhandled case.\n"));
                    m = last_advance_ins[0];
                    n = 0;
                    for(i=1; i<2; i++) {
                        if(m>last_advance_ins[i]) {
                            m = last_advance_ins[i];
                            n = i;
                        }
                    }
                        
                    if(iins>last_advance_ins[n]+10) {
                        jins = aIns[iins]._succ;
                        while(jins!=aBb[ibb]._ins_last) {
                            if(jins<=aBb[ibb]._ins_last)
                                tud = jins - fins;
                            else
                                tud = aBb[ibb]._ins_num + jins - bins;
                            if(aIns[jins]._op==BT_Imovsd_sse && aUseDef[tud]._def[0]==d_reg)
                                break;
                            jins = aIns[jins]._succ;
                        }

                        b_reg = BT_R_XMM8 + n;
                        if(jins==aBb[ibb]._ins_last) {
                            last_advance_ins[b_reg-BT_R_XMM8] = iins;
                            aIns[nIns]._op = BT_Imovsd_sse;
                            aIns[nIns]._opndnum = 2;
                            aIns[nIns]._src_opnd_num = 1;
                            aIns[nIns]._dest_opnd_num = 1;
                            aIns[nIns]._src_opnd_start = 1;
                            aIns[nIns]._operand[0].type = BT_OP_XMMREG;
                            aIns[nIns]._operand[0].size = aIns[iins]._operand[0].size;
                            aIns[nIns]._operand[0].base = b_reg;
                            aIns[nIns]._operand[1] = aIns[iins]._operand[1];
                            aIns[nIns]._ibb = ibb;
                            aIns[nIns]._binary[0] = 0xf2;
                            aIns[nIns]._binary[1] = 0x44;
                            aIns[nIns]._binary[2] = 0x0f;
                            aIns[nIns]._binary[3] = 0x10;
                            if((aIns[iins]._binary[1]&0x0f8)==0x40) {
                                for(i=aIns[iins]._size; i>3; i--)
                                    aIns[nIns]._binary[i] = aIns[iins]._binary[i];
                                aIns[nIns]._binary[1] = aIns[nIns]._binary[1] | (aIns[iins]._binary[1]&0x3);
                                aIns[nIns]._size = aIns[iins]._size;
                            }
                            else {
                                for(i=aIns[iins]._size; i>3; i--)
                                    aIns[nIns]._binary[i] = aIns[iins]._binary[i-1];
                                aIns[nIns]._size = aIns[iins]._size + 1;
                            }
                            aIns[nIns]._binary[4] = (aIns[nIns]._binary[4]&0x0c7) | ((b_reg-BT_R_XMM8)<<3);

                            aIns[nIns]._prev = aIns[iins]._prev;
                            aIns[nIns]._succ = iins;

                            aIns[iins]._operand[1].type = BT_OP_XMMREG;
                            aIns[iins]._operand[1].lval.udword = 0;
                            aIns[iins]._operand[1].base = b_reg;
                            aIns[iins]._operand[1].index = BT_NONE;
                            aIns[iins]._operand[1].scale = 0;
                            if((aIns[iins]._binary[1]&0x0f8)!=0x40) {
                                aIns[iins]._binary[4] = aIns[iins]._binary[3];
                                aIns[iins]._binary[3] = aIns[iins]._binary[2];
                                aIns[iins]._binary[2] = aIns[iins]._binary[1];
                            }
                            aIns[iins]._binary[1] = 0x41;
                            aIns[iins]._binary[4] = (aIns[iins]._binary[4]&0x0f8)|0x0c0|(b_reg-BT_R_XMM8);
                            aIns[iins]._size = 5;

                            aIns[aIns[iins]._prev]._succ = nIns;
                            aIns[iins]._prev = nIns;

                            jud = aBb[ibb]._ins_num + nIns - bins;
                            aIns[jins]._use[0] = aIns[nIns]._operand[1].base;
                            aIns[jins]._use[1] = aIns[nIns]._operand[1].index;
                            aIns[jins]._def[0] = b_reg;
                            jud = iins - fins;
                            aIns[jins]._use[0] = b_reg;
                            aIns[jins]._use[1] = BT_NONE;
                            aIns[jins]._use[2] = BT_NONE;

                            iins = aIns[nIns]._prev;
                            nIns ++;
                        }
                        else {
                            ASSERT(jins<aBb[ibb]._ins_last, ("unhandled case.\n"));
                            last_advance_ins[b_reg-BT_R_XMM8] = jins;
                            if((aIns[iins]._binary[1]&0x0f8)!=0x40) {
                                for(i=aIns[iins]._size; i>1; i--)
                                    aIns[iins]._binary[i] = aIns[iins]._binary[i-1];
                                aIns[iins]._binary[1] = 0x44;
                                aIns[iins]._size ++;
                            }
                            else
                                aIns[iins]._binary[1] |= 0x4;
                            aIns[iins]._binary[4] = (aIns[iins]._binary[4]&0x0c7) | ((b_reg-BT_R_XMM8)<<3);
                            aIns[jins]._def[0] = b_reg;

                            jins = aIns[iins]._succ;
                            while(1) {
                                if(jins<=aBb[ibb]._ins_last)
                                    tud = jins - fins;
                                else
                                    tud = aBb[ibb]._ins_num + jins - bins;
                                if(aUseDef[tud]._use[0]==d_reg || aUseDef[tud]._use[1]==d_reg || aUseDef[tud]._use[2]==d_reg ||aUseDef[tud]._def[0]==d_reg) {
                                    if(aIns[jins]._op == BT_Imovsd_sse && aUseDef[tud]._def[0]==d_reg)
                                        break;
                                    ASSERT((aIns[jins]._op>=BT_Idivsd&&aIns[jins]._op<=BT_Iaddsd)||aIns[jins]._op==BT_Imovsd_sse, ("unhandled case.\n"));
                                    if((aIns[jins]._binary[1]&0x0f8)!=0x40) {
                                        for(i=aIns[jins]._size; i>1; i--)
                                            aIns[jins]._binary[i] = aIns[jins]._binary[i-1];
                                        aIns[jins]._binary[1] = 0x40;
                                        aIns[jins]._size ++;
                                    }
                                    
                                    if(aUseDef[tud]._def[0]==d_reg) {
                                        aIns[jins]._binary[1] |= 0x4;
                                        aIns[jins]._binary[4] = (aIns[jins]._binary[4]&0x0c7) | ((b_reg-BT_R_XMM8)<<3);
                                        aUseDef[tud]._def[0] = b_reg;
                                        for(i=0; i<3; i++) {
                                            if(aUseDef[tud]._use[i]==d_reg)
                                                aUseDef[tud]._use[i]=b_reg;
                                        }
                                    }
                                    else if(aIns[jins]._op==BT_Imovsd_sse) {
                                        aIns[jins]._binary[1] |= 0x4;
                                        aIns[jins]._binary[4] = (aIns[jins]._binary[4]&0x0c7) | ((b_reg-BT_R_XMM8)<<3);
                                        for(i=0; i<3; i++) {
                                            if(aUseDef[tud]._use[i]==d_reg)
                                                aUseDef[tud]._use[i]=b_reg;
                                        }
                                    }
                                    else {
                                        aIns[jins]._binary[1] |= 0x1;
                                        aIns[jins]._binary[4] = (aIns[jins]._binary[4]&0x0f8) | (b_reg-BT_R_XMM8);
                                        for(i=0; i<3; i++) {
                                            if(aUseDef[tud]._use[i]==d_reg)
                                                aUseDef[tud]._use[i]=b_reg;
                                        }
                                    }
                                }
                                jins = aIns[jins]._succ;
                            }
                            iins = aIns[iins]._prev;
                        }
                    }
                }
            }
        }

        iins = aIns[iins]._succ;
    }
  #endif

}

void OptimizingLoop() {
    BBINDEX ibb, pbb, tbb, tpbb;
    BBLKINDEX tbblk1, tbblk2, tsucc; 
    INSINDEX iins;
    OUTLPINDEX iOutLoop;
    REGIONINDEX iregion;
    BBINDEX root_bb[NUM_OF_EXBB], exit_bb[NUM_OF_EXBB];
    OUTLPINDEX root_loop_list[NUM_OF_EXBB], exit_loop_list[NUM_OF_EXBB];
    int ex_root_index = 0, ex_exit_index = 0;

    char *p_code_cache, *p_instr_code;
    BOOL adjust_esp = FALSE, adjust_ebp = FALSE;
    int i;

    ibb = aFun[ifun]._ibb_entry;
    pbb = INVALID;

    while(ibb) {
        iOutLoop = 1;
        while(iOutLoop < nOutLp) {
            if(aOutLoop[iOutLoop]._flag&LOOP_OPT_CANCLED) {
                iOutLoop ++;
                continue;
            }
            if(ArraySExist(aOutLoop[iOutLoop]._member, ibb))
                break;
            iOutLoop ++;
        }

        if(iOutLoop<nOutLp) {
            if((aOutLoop[iOutLoop]._flag&LOOP_OPT_REGION)==0 && aBb[ibb]._ins_num>5)
                OptimizingBb(ibb);

            if(aOutLoop[iOutLoop]._entry==ibb) {
                tbblk1 = aBb[ibb]._pred_bb;
                if(!ArraySExist(aOutLoop[iOutLoop]._member, pbb)) {
                    while(tbblk1) {
                        tpbb = aBblk[tbblk1]._ibb;
                        if(!ArraySExist(aOutLoop[iOutLoop]._member, tpbb) && tpbb!=pbb)
                            break;

                        tbblk1 = aBblk[tbblk1]._next;
                    }

                    if(tbblk1) {
                        tbb = BbNew();
                        aBb[tbb]._opt_code_addr = (ADDR32)curr_code_ptr;
                        aBb[ibb]._flag |= BB_OPTIMIZED;
                        while(tbblk1) {
                            tpbb = aBblk[tbblk1]._ibb;
                            if(!ArraySExist(aOutLoop[iOutLoop]._member, tpbb) && tpbb!=pbb) {
                                tsucc = aBb[tpbb]._succ_bb;
                                while(tsucc) {
                                    if(aBblk[tsucc]._ibb == ibb)
                                        aBblk[tsucc]._ibb = tbb;

                                    tsucc = aBblk[tsucc]._next;
                                }
                            }
                            tbblk1 = aBblk[tbblk1]._next;
                        }
                    }

                    MprotectStack(iOutLoop, TRUE);
                    ModeSwitch(COMPAT_TO_LONG);
                    if((aOutLoop[iOutLoop]._flag&LOOP_OPT_REGION)==0)
                        Preload(aOutLoop[iOutLoop]._rem_list);
                }
                else {
                    ASSERT(ex_root_index<NUM_OF_EXBB, ("ASSERT FAILED! The num of extra root bb array is overflow!\n"))
                    //add a new block, and set up the block link
                    tbb = BbNew();

                    tbblk2 = BblkNew();
                    aBblk[tbblk2]._ibb = ibb;
                    
                    aBb[tbb]._succ_bb_num = 1;
                    aBb[tbb]._succ_bb = tbblk2;

                    tbblk1 = aBb[ibb]._pred_bb;
                    while(tbblk1) {
                        tpbb = aBblk[tbblk1]._ibb;
                        if(!ArraySExist(aOutLoop[iOutLoop]._member, tpbb)) {
                            tsucc = aBb[tpbb]._succ_bb;
                            while(tsucc) {
                                if(aBblk[tsucc]._ibb == ibb)
                                    aBblk[tsucc]._ibb = tbb;

                                tsucc = aBblk[tsucc]._next;
                            }
                        }
                        tbblk1 = aBblk[tbblk1]._next;
                    }

                    root_bb[ex_root_index] = tbb;
                    root_loop_list[ex_root_index] = iOutLoop;
                    ex_root_index += 1;
                }
            }

            if(aOutLoop[iOutLoop]._flag&LOOP_OPT_REGION) {
                iregion = aOutLoop[iOutLoop]._region;
                while(iregion) {
                    if(aRegion[iregion]._ibb==ibb)
                        break;
                    iregion = aRegion[iregion]._next;
                }
                if(iregion) {
                    OptimizingBb(ibb);
                    Preload(aRegion[iregion]._rem_list);
                }
            }

            aBb[ibb]._opt_code_addr = (ADDR32)curr_code_ptr;
            aBb[ibb]._flag |= BB_OPTIMIZED;
            iins = aBb[ibb]._ins_first;

            if(aBb[ibb]._last_instr_type>T_ENTRY && aBb[ibb]._last_instr_type<T_BRANCH) {
                //ASSERT((aBb[ibb]._flag&BB_INS_SCHEDULED)==0, ("unhandled case.\n"));
                ibb = HandleCallInOptCode(iins);
            }
            else {
                while(iins!=aBb[ibb]._ins_last) {
                    GenX64Code(iins);
                    iins = aIns[iins]._succ;
                }

                aIns[iins]._opt_addr = (ADDR32)curr_code_ptr;
                p_instr_code = aIns[iins]._binary;
                if(aIns[iins]._op>BT_Iljmp && aIns[iins]._op<BT_Iloop) {
                    if((p_instr_code[0]&0xf0) == 0x70) {
                        *((UINT8 *)curr_code_ptr) = 0x0f;
                        curr_code_ptr += 1;
                        *((UINT8 *)curr_code_ptr) = 0x80 | (p_instr_code[0]&0x0f);
                        curr_code_ptr += 1;
                        *((int *)curr_code_ptr) = *(signed char *)(p_instr_code+1);
                        curr_code_ptr += 4;

                        aIns[iins]._size += 3;
                    }
                    else {
                        p_code_cache = (char *)curr_code_ptr;
                        for(i=0; i<aIns[iins]._size; i++)
                            p_code_cache[i] = p_instr_code[i];

                        curr_code_ptr += aIns[iins]._size;
                    }
                }
                else if(aIns[iins]._op == BT_Ijmp) {
                    if(p_instr_code[0] == (char)0xeb) {
                        *((UINT8 *)curr_code_ptr) = 0xe9;
                        curr_code_ptr += 1;
                        *((int *)curr_code_ptr) = *(signed char *)(p_instr_code+1);
                        curr_code_ptr += 4;

                        aIns[iins]._size += 3;
                    }
                    else {
                        p_code_cache = (char *)curr_code_ptr;
                        for(i=0; i<aIns[iins]._size; i++)
                            p_code_cache[i] = p_instr_code[i];

                        curr_code_ptr += aIns[iins]._size;
                    }
                }
                else
                    GenX64Code(iins);
            }

            if(aOutLoop[iOutLoop]._flag&LOOP_OPT_REGION) {
                if(iregion)
                    Synchronization(aRegion[iregion]._rem_list);
            }

            if(ArrayExist(aOutLoop[iOutLoop]._exit, ibb)) {
                tbblk1 = aBb[ibb]._succ_bb;
                while(tbblk1) {
                    tpbb = aBblk[tbblk1]._ibb;
                    if(!ArraySExist(aOutLoop[iOutLoop]._member, tpbb)) {
                        if(aBb[ibb]._next == tpbb) {
                            if((aOutLoop[iOutLoop]._flag&LOOP_OPT_REGION)==0)
                                Synchronization(aOutLoop[iOutLoop]._rem_list);
                            ModeSwitch(LONG_TO_COMPAT);
                            MprotectStack(iOutLoop, FALSE);
                        }
                        else {
                            ASSERT(ex_exit_index<NUM_OF_EXBB, ("ASSERT FAILED! The num of extra exit bb array is overflow!\n"))
                            //add a new block, and set up the block link
                            tbb = BbNew();
                            
                            tbblk2 = BblkNew();
                            aBblk[tbblk2]._next = INVALID;
                            aBblk[tbblk2]._ibb = ibb;

                            tbblk2 = BblkNew();
                            aBblk[tbblk2]._next = INVALID;
                            aBblk[tbblk2]._ibb = tpbb;

                            aBb[tbb]._succ_bb_num = 1;
                            aBb[tbb]._succ_bb = tbblk2;

                            //p_block->succ = tbb
                            aBblk[tbblk1]._ibb = tbb;

                            exit_bb[ex_exit_index] = tbb;
                            exit_loop_list[ex_exit_index] = iOutLoop;
                            ex_exit_index += 1;
                        }
                    }

                    tbblk1 = aBblk[tbblk1]._next;
                }
            }
        }
        else if(aBb[ibb]._last_instr_type == T_RET) {
            aBb[ibb]._opt_code_addr = (ADDR32)curr_code_ptr;
            iins = aBb[ibb]._ins_first;
            while(iins < aBb[ibb]._ins_last) {
                DupIA32Code(iins);
                iins ++;
            }

            FATAL(aIns[iins]._op!=BT_Iret, ("Generate optimized code: Assert failed!\n"))
        #ifndef _NO_STACK_SWITCH
            if((aFun[ifun]._flag&FUN_NO_RESTORE_ESP)==0) {
                //mov old_esp, esp  stack switch code
                *(UINT8 *)curr_code_ptr = 0x8b;
                curr_code_ptr += 1;
                *(UINT16 *)curr_code_ptr = 0x2524;
                curr_code_ptr += 2;
                *(UINT32 *)curr_code_ptr = (UINT32)(UINT64)(&(aFun[ifun]._old_esp));
                curr_code_ptr += 4;
            }
        #endif

            aIns[iins]._opt_addr = (ADDR32)curr_code_ptr;
            p_code_cache = (char *)curr_code_ptr;

            for(i=0; i<aIns[iins]._size; i++)
                p_code_cache[i] = aIns[iins]._binary[i];

            curr_code_ptr += aIns[iins]._size;
        }
        else {
            aBb[ibb]._opt_code_addr = (ADDR32)curr_code_ptr;
            iins = aBb[ibb]._ins_first;
            while(iins < aBb[ibb]._ins_last) {
                DupIA32Code(iins);
                iins ++;
            }

            aIns[iins]._opt_addr = (ADDR32)curr_code_ptr;
            if(aIns[iins]._op>BT_Iljmp && aIns[iins]._op<BT_Iloop) {
                if((aIns[iins]._binary[0]&0xf0) == 0x70) {
                    *((UINT8 *)curr_code_ptr) = 0x0f;
                    curr_code_ptr += 1;
                    *((UINT8 *)curr_code_ptr) = 0x80 | (aIns[iins]._binary[0]&0x0f);
                    curr_code_ptr += 1;
                    *((INT32 *)curr_code_ptr) = *(INT8 *)(aIns[iins]._binary+1);
                    curr_code_ptr += 4;

                    aIns[iins]._size += 3;
                }
                else {
                    p_instr_code = aIns[iins]._binary;
                    
                    *((UINT8 *)curr_code_ptr) = p_instr_code[0];
                    curr_code_ptr += 1;
                    *((UINT8 *)curr_code_ptr) = p_instr_code[1];
                    curr_code_ptr += 1;
                    *((INT32 *)curr_code_ptr) = *(INT32 *)(p_instr_code+2);
                    curr_code_ptr += 4;
                }
            }
            else if(aIns[iins]._op == BT_Ijmp) {
                if(aIns[iins]._binary[0] == (char)0xeb) {
                    *((UINT8 *)curr_code_ptr) = 0xe9;
                    curr_code_ptr += 1;
                    *((int *)curr_code_ptr) = *(signed char *)(aIns[iins]._binary+1);
                    curr_code_ptr += 4;

                    aIns[iins]._size += 3;
                }
                else {
                    p_code_cache = (char *)curr_code_ptr;
                    for(i=0; i<aIns[iins]._size; i++)
                        p_code_cache[i] = aIns[iins]._binary[i];

                    curr_code_ptr += aIns[iins]._size;
                }
            }
            else {
                p_code_cache = (char *)curr_code_ptr;
                for(i=0; i<aIns[iins]._size; i++)
                    p_code_cache[i] = aIns[iins]._binary[i];

                curr_code_ptr += aIns[iins]._size;
            }
        }

        if(ItCodeCache) {
            p_code_cache = (char *)curr_code_ptr;
            for(i=0; i<ItCodeCache; i++)
                p_code_cache[i] = tCodeCache[i];
            curr_code_ptr += ItCodeCache;

            ItCodeCache = 0;
        }

        pbb = ibb;
        ibb = aBb[ibb]._next;
    }

    for(i=0; i<ex_root_index; i++) {
        aBb[root_bb[i]]._opt_code_addr = (ADDR32)curr_code_ptr;
        aBb[root_bb[i]]._flag |= BB_OPTIMIZED;
        
        MprotectStack(root_loop_list[i], TRUE);
        ModeSwitch(COMPAT_TO_LONG);
        if((aOutLoop[iOutLoop]._flag&LOOP_OPT_REGION)==0)
            Preload(aOutLoop[root_loop_list[i]]._rem_list);

        *(UINT8 *)curr_code_ptr = 0xe9;
        curr_code_ptr += 1;
        tbb = aBblk[aBb[root_bb[i]]._succ_bb]._ibb;
        *(UINT32 *)curr_code_ptr = aBb[tbb]._opt_code_addr - (ADDR32)curr_code_ptr - 4;
        curr_code_ptr += 4;
    }

    for(i=0; i<ex_exit_index; i++) {
        aBb[exit_bb[i]]._opt_code_addr = (ADDR32)curr_code_ptr;
        
        if((aOutLoop[iOutLoop]._flag&LOOP_OPT_REGION)==0)
            Synchronization(aOutLoop[exit_loop_list[i]]._rem_list);
        ModeSwitch(LONG_TO_COMPAT);
        MprotectStack(exit_loop_list[i], FALSE);

        *(UINT8 *)curr_code_ptr = 0xe9;
        curr_code_ptr += 1;
        tbb = aBblk[aBb[exit_bb[i]]._succ_bb]._ibb;
        *(UINT32 *)curr_code_ptr = aBb[tbb]._opt_code_addr - (ADDR32)curr_code_ptr - 4;
        curr_code_ptr += 4;
    }
}

void OptimizingFunc() {
    BBINDEX ibb;
    INSINDEX iins;

    char *p_code_cache, *p_instr_code;
    int i;
    
    ibb = aFun[ifun]._ibb_entry;
    while(ibb) {
        aBb[ibb]._opt_code_addr = (ADDR32)curr_code_ptr;
        aBb[ibb]._flag |= BB_OPTIMIZED;
        iins = aBb[ibb]._ins_first;

        if(ibb == aFun[ifun]._ibb_entry) {
            while(iins < aBb[ibb]._ins_last) {
                aIns[iins]._opt_addr = (ADDR32)curr_code_ptr;
                p_code_cache = (char *)curr_code_ptr;

                for(i=0; i<aIns[iins]._size; i++)
                    p_code_cache[i] = aIns[iins]._binary[i];
                curr_code_ptr = curr_code_ptr + aIns[iins]._size;

                if(IS_SUB_IMM_ESP(aIns[iins]._binary)) {
                    MprotectStack(1, TRUE);
                    ModeSwitch(COMPAT_TO_LONG);
                    Preload(aOutLoop[1]._rem_list);

                    ASSERT(iins!=aBb[ibb]._ins_last, ("Instr sub ##, %esp is the last instr of entry block.\n"));
                    iins ++;
                    break;
                }

                iins ++;
            }
            
        }
        
        if(aBb[ibb]._last_instr_type>T_ENTRY && aBb[ibb]._last_instr_type<T_BRANCH) {
            //ASSERT((aBb[ibb]._flag&BB_INS_SCHEDULED)==0, ("unhandled case.\n"));
            ibb = HandleCallInOptCode(iins);
        }
        else if(aBb[ibb]._last_instr_type == T_RET) {
            ASSERT(ibb!=aFun[ifun]._ibb_entry, ("The entry block is end with RET.\n"));

            while(iins<aBb[ibb]._ins_last && aIns[iins]._op!=BT_Ipop && !IS_ADD_IMM_ESP(aIns[iins]._binary)) {
                GenX64Code(iins);
                iins ++;
            }
            
            Synchronization(aOutLoop[1]._rem_list);
            ModeSwitch(LONG_TO_COMPAT);
            MprotectStack(1, FALSE);
            
            while(iins < aBb[ibb]._ins_last) {
                aIns[iins]._opt_addr = (ADDR32)curr_code_ptr;
                p_code_cache = (char *)curr_code_ptr;

                for(i=0; i<aIns[iins]._size; i++)
                    p_code_cache[i] = aIns[iins]._binary[i];
                curr_code_ptr += aIns[iins]._size;

                iins ++;
            }

            FATAL(aIns[iins]._op!=BT_Iret, ("Generate optimized code: Assert failed!\n"))
        #ifndef _NO_STACK_SWITCH
            if((aFun[ifun]._flag&FUN_NO_RESTORE_ESP)==0) {
                //mov old_esp, esp  stack switch code
                *(UINT8 *)curr_code_ptr = 0x8b;
                curr_code_ptr += 1;
                *(UINT16 *)curr_code_ptr = 0x2524;
                curr_code_ptr += 2;
                *(UINT32 *)curr_code_ptr = (UINT32)(UINT64)(&(aFun[ifun]._old_esp));
                curr_code_ptr += 4;
            }
        #endif

            aIns[iins]._opt_addr = (ADDR32)curr_code_ptr;
            p_code_cache = (char *)curr_code_ptr;

            for(i=0; i<aIns[iins]._size; i++)
                p_code_cache[i] = aIns[iins]._binary[i];

            curr_code_ptr += aIns[iins]._size;
        }
        else {
            if(ibb!=aFun[ifun]._ibb_entry && aBb[ibb]._ins_num>10)
                OptimizingBb(ibb);

            while(iins!=aBb[ibb]._ins_last) {
                GenX64Code(iins);
                iins = aIns[iins]._succ;
            }

            aIns[iins]._opt_addr = (ADDR32)curr_code_ptr;
            p_instr_code = aIns[iins]._binary;
            if(aIns[iins]._op>BT_Iljmp && aIns[iins]._op<BT_Iloop) {
                if((p_instr_code[0]&0xf0) == 0x70) {
                    *((UINT8 *)curr_code_ptr) = 0x0f;
                    curr_code_ptr += 1;
                    *((UINT8 *)curr_code_ptr) = 0x80 | (p_instr_code[0]&0x0f);
                    curr_code_ptr += 1;
                    *((int *)curr_code_ptr) = *(signed char *)(p_instr_code+1);
                    curr_code_ptr += 4;

                    aIns[iins]._size += 3;
                }
                else {
                    p_code_cache = (char *)curr_code_ptr;
                    for(i=0; i<aIns[iins]._size; i++)
                        p_code_cache[i] = p_instr_code[i];

                    curr_code_ptr += aIns[iins]._size;
                }
            }
            else if(aIns[iins]._op == BT_Ijmp) {
                if(p_instr_code[0] == (char)0xeb) {
                    *((UINT8 *)curr_code_ptr) = 0xe9;
                    curr_code_ptr += 1;
                    *((int *)curr_code_ptr) = *(signed char *)(p_instr_code+1);
                    curr_code_ptr += 4;

                    aIns[iins]._size += 3;
                }
                else {
                    p_code_cache = (char *)curr_code_ptr;
                    for(i=0; i<aIns[iins]._size; i++)
                        p_code_cache[i] = p_instr_code[i];

                    curr_code_ptr += aIns[iins]._size;
                }
            }
            else
                GenX64Code(iins);
        } 

        ibb = aBb[ibb]._next;
    }
}

void SelectOptTarget() {
    BBINDEX ibb;
    BBLKINDEX ibblk;
    INSINDEX iins;
    OUTLPINDEX iOutLoop;
    INNLPINDEX iInnLoop;
    REGIONINDEX iregion;
    int t_percent, loop_num = 0, hot_loop_num = 0, tot_insnum = 0;
    int outloop_call_num = 0, inloop_call_num = 0;
    int i;

    ibb = aFun[ifun]._ibb_entry;
    iins = aBb[ibb]._ins_first;
    while(iins <= aBb[ibb]._ins_last) {
        if(aIns[iins]._op==BT_Ipush)
            aFun[ifun]._caller_off += 4;
        else if(IS_SUB_IMM_ESP(aIns[iins]._binary)) {
            if(aFun[ifun]._rem_base==BT_R_ESP)
                aFun[ifun]._caller_off += aIns[iins]._operand[1].lval.sdword;
            break;
        }
        iins ++;
    }

    while(ibb) {
        tot_insnum += aBb[ibb]._ins_num;
        if(aBb[ibb]._last_instr_type>T_ENTRY && aBb[ibb]._last_instr_type<T_BRANCH) {
            iOutLoop = 1;
            while(iOutLoop < nOutLp) {
                if(ArraySExist(aOutLoop[iOutLoop]._member, ibb))
                    break;
                iOutLoop ++;
            }

            if(iOutLoop==nOutLp)
                outloop_call_num ++;
            else
                inloop_call_num ++;
        }
        
        ibb = aBb[ibb]._next;
    }

    iOutLoop = 1;
    while(iOutLoop < nOutLp) {
        if(aOutLoop[iOutLoop]._samples*11>aFun[ifun]._samples)
            hot_loop_num ++;
        iOutLoop += 1;
    }

    loop_num = nOutLp-1;

    OUTPUT(("\toutloop call: %d  inloop call: %d  loop num: %d  callee arg off: %d\n", \
            outloop_call_num, inloop_call_num, loop_num, aFun[ifun]._callee_arg_off));
  
    if(outloop_call_num<2 && inloop_call_num==0 && hot_loop_num>=2)
        aFun[ifun]._opt_target = FUNC;
    else
        aFun[ifun]._opt_target = LOOP;

    aFun[ifun]._opt_target = LOOP;

    if(aFun[ifun]._opt_target==LOOP) {
        iOutLoop = 1;
        while(iOutLoop < nOutLp) {
            if(aOutLoop[iOutLoop]._samples*10<aFun[ifun]._samples || (aOutLoop[iOutLoop]._flag&LOOP_UNREDUCIBLE) ||\
                (aOutLoop[iOutLoop]._flag&LOOP_CONTAIN_JUMPIN) || aOutLoop[iOutLoop]._call_num>0) {
                aOutLoop[iOutLoop]._flag |= LOOP_OPT_CANCLED;
                loop_num -= 1;
            }
            iOutLoop ++;
        }
        if(loop_num>5)
            aFun[ifun]._flag |= FUN_OPT_CANCLED;
    }
    else {
        if(inloop_call_num>3)
            aFun[ifun]._flag |= FUN_OPT_CANCLED;
    }

    if(aFun[ifun]._flag & FUN_OPT_CANCLED) {
            OUTPUT(("****************OPTIMIZATION CANCLED****************\n"));
    }
    else {
        OUTPUT(("\toptimization target (0:LOOP 1:FUNC): %d\n", aFun[ifun]._opt_target))
        if(aFun[ifun]._opt_target==LOOP) {
            OUTPUT(("\toptimized loop num: %d\n", loop_num))
            iOutLoop = 1;
            while(iOutLoop < nOutLp) {
                if((aOutLoop[iOutLoop]._flag&LOOP_OPT_CANCLED) || (aOutLoop[iOutLoop]._member->NumOfElem<10)) {
                    iOutLoop ++;
                    continue;
                }

                t_percent = 0;
                t_array = aOutLoop[iOutLoop]._member;
                for(i=0; i<t_array->NumOfElem; i++) {
                    ibb = t_array->ArrayBase[i];
                    if(aBb[ibb]._samples*10 > aFun[ifun]._samples) {
                        if(aBb[ibb]._pred_bb_num != 2)
                            break;
                        ibblk = aBb[ibb]._pred_bb;
                        if(aBblk[ibblk]._ibb!=ibb && aBblk[aBblk[ibblk]._next]._ibb!=ibb)
                            break;
                        
                        t_percent += aBb[ibb]._samples;
                    }

                    if(aBb[ibb]._samples*2 > aFun[ifun]._samples)
                        break;
                }

                if(i==t_array->NumOfElem && t_percent*10>aFun[ifun]._samples*6 && aFun[ifun]._rem_base==BT_R_ESP) {
                    aOutLoop[iOutLoop]._flag |= LOOP_OPT_REGION;
                    for(i=0; i<t_array->NumOfElem; i++) {
                        ibb = t_array->ArrayBase[i];
                        if(aBb[ibb]._samples*10 > aFun[ifun]._samples) {
                            iregion = RegionNew();
                            aRegion[iregion]._ibb = ibb;
                            if(aOutLoop[iOutLoop]._region) {
                                aRegion[iregion]._next = aOutLoop[iOutLoop]._region;
                                aOutLoop[iOutLoop]._region = iregion;
                            }
                            else
                                aOutLoop[iOutLoop]._region = iregion;
                        }
                    }
                }

                OUTPUT(("\t\tcall in loop: %d  instr num: %d\n", aOutLoop[iOutLoop]._call_num, aOutLoop[iOutLoop]._instr_num))
                iOutLoop ++;
            }
        }
    }
}

void GenerateOptimizedCode() {
    OUTLPINDEX iOutLoop;
    REGIONINDEX iregion;
    BBINDEX ibb, tbb;
    INSINDEX iins;
    REMINDEX irem;
    BBLKINDEX tbblk;
    int i;

    char *p_code_cache;

#ifndef _NO_STACK_SWITCH
    StackSwitch();
#endif

    iOutLoop = 1;
    while(iOutLoop < nOutLp) {
        if((aOutLoop[iOutLoop]._flag&LOOP_OPT_CANCLED) || (aFun[ifun]._opt_target==FUNC && iOutLoop!=1)) {
            iOutLoop ++;
            continue;
        }

        iGpr = EX_R8;
        iXmm = EX_XMM8;
        iMmx = EX_MM0;

        if(aOutLoop[iOutLoop]._flag&LOOP_OPT_REGION) {
            iregion = aOutLoop[iOutLoop]._region;
            while(iregion) {
                if(aRegion[iregion]._rem_num) {

                    irem = aRegion[iregion]._rem_list;
                    while(irem) {
                        if(aRem[irem]._allotted_reg!=EX_NONE) {
                            irem = aRem[irem]._next;
                            continue;
                        }

                        RemAllocateReg(irem);
                        ModifyRemIns(irem);

                        irem = aRem[irem]._next;
                    }
                }
                iregion = aRegion[iregion]._next;
            }
        }
        else {
            irem = aOutLoop[iOutLoop]._rem_list;
            i = 0;
            while(irem && i<16) {
                if(aRem[irem]._gpr_num!=0 && aRem[irem]._xmm_num==0) {
                    RemAllocateReg(irem);
                    ModifyRemIns(irem);
                }
                else if(aRem[irem]._gpr_num==0 && aRem[irem]._xmm_num!=0) {
                    RemAllocateReg(irem);
                    ModifyRemIns(irem);
                }

                i ++;
                irem = aRem[irem]._next;
            }

            irem = aOutLoop[iOutLoop]._rem_list;
            while(irem) {
                if(aRem[irem]._allotted_reg!=EX_NONE) {
                    irem = aRem[irem]._next;
                    continue;
                }

                RemAllocateReg(irem);
                ModifyRemIns(irem);

                irem = aRem[irem]._next;
            }
        }
        iOutLoop ++;
    }

    if(aFun[ifun]._opt_target==LOOP)
        OptimizingLoop();
    else
        OptimizingFunc();

    //adjust the displacement
    ibb = aFun[ifun]._ibb_entry;
    while(ibb) {
        ADDR p_opt_instr;
        INT32 offset;
        iins = aBb[ibb]._ins_last;
        p_opt_instr = aIns[iins]._opt_addr;

        tbblk = aBb[ibb]._succ_bb;
        if(aIns[iins]._op>BT_Iljmp && aIns[iins]._op<BT_Iloop && *(char *)p_opt_instr==0x0f) {
            tbblk = aBblk[tbblk]._next;
            tbb = aBblk[tbblk]._ibb;
            offset = aBb[tbb]._opt_code_addr - (INT32)p_opt_instr - 6;
            *(INT32 *)(p_opt_instr+2) = offset;
        }
        else if(aIns[iins]._op==BT_Icall && *(char *)p_opt_instr==(char)0xe8) {
            offset = aIns[iins]._addr_next + aIns[iins]._operand[0].lval.sdword - (INT32)p_opt_instr - 5;
            *(INT32 *)(p_opt_instr+1) = offset;
        }
        else if(aIns[iins]._op==BT_Ijmp && *(char *)p_opt_instr==(char)0xe9) {
            tbb = aBblk[tbblk]._ibb;
            offset = aBb[tbb]._opt_code_addr - (INT32)p_opt_instr - 5;
            *(INT32 *)(p_opt_instr+1) = offset;
        }
        else if(aIns[iins]._op==BT_Ijmpin) {
            INSINDEX tins1, tins2;
            OUTLPINDEX tOutLoop;
            ADDR32 p_jump_target, p_jump_retarget, temp;
            int target_num = 0;
            
            tins1 = iins - 1;
            ASSERT(IS_JUMPIN_REG(aIns[iins]._binary), ("The instruction is not jmpin reg.\n"));
            ASSERT((*(UINT8 *)(aIns[tins1]._binary)&0x0ff)==(UINT8)0x8b && \
                aIns[iins]._operand[0].base==aIns[tins1]._operand[0].base, ("jumpin pattern failed.\n"));
            ASSERT(aIns[tins1]._operand[1].type==BT_OP_MEM && aIns[tins1]._operand[1].base==BT_NONE,("jumpin pattern failed!\n"));

            p_jump_target = aIns[tins1]._operand[1].lval.udword;

            tbblk = aBb[ibb]._pred_bb;
            while(tbblk) {
                if(aBb[aBblk[tbblk]._ibb]._next==ibb)
                    break;
                tbblk = aBblk[tbblk]._next;
            }
            ASSERT(tbblk!=INVALID, ("Find pred bb error.\n"));
            tbb = aBblk[tbblk]._ibb;
            tins2 = aBb[tbb]._ins_last - 1;
            while(tins2 >= aBb[tbb]._ins_first) {
                if(aIns[tins2]._op==BT_Icmp) {
                    if(aIns[tins2]._binary[0]==(char)0x83) {
                        ASSERT(aIns[tins2]._operand[0].type==BT_OP_REG, ("Find switch case range.\n"));
                        if(aIns[tins2]._operand[0].base==aIns[tins1]._operand[1].index)
                            target_num = aIns[tins2]._operand[1].lval.sdword;
                    }
                    else if(aIns[tins2]._binary[0]==(char)0x3d)
                        target_num = aIns[tins2]._operand[0].lval.sdword;
                }
                tins2 --;
            }

            if(target_num==0) {
                WARNING(("The switch case pattern does not find.\n"))
                target_num = 4;
                temp = *(ADDR32 *)(ADDR)(p_jump_target+target_num*4);
                while(temp>=aFile._text_start_addr && temp<=aFile._text_end_addr) {
                    target_num += 1;
                    temp = *(ADDR32 *)(ADDR)(p_jump_target+target_num*4);
                }
            }

            p_jump_retarget = (ADDR32)MmAllocGlobalV((target_num+1)*4);
            for(i=0; i<=target_num; i++) {
                temp = *(ADDR32 *)(ADDR)(p_jump_target+i*4);
                ASSERT(aFun[ifun]._func_size!=0, ("Error while find function size.\n"));
                if(temp>aFun[ifun]._entry_addr && temp<aFun[ifun]._entry_addr+aFun[ifun]._func_size) {
                    tbb = HashSearch(temp);
                    if(tbb==INVALID) {
                        tbb = aFun[ifun]._ibb_head;
                        while(tbb) {
                            if(temp<aBb[aBb[tbb]._next]._entry_addr)
                                break;
                            tbb = aBb[tbb]._next;
                        }
                        ASSERT(tbb!=INVALID, ("The jump target is not a block.\n"));

                        tins1 = aBb[tbb]._ins_first;
                        while(tins1 && aIns[tins1]._addr!=temp) {
                            tins1 = aIns[tins1]._addr_next;
                        }
                        *(ADDR32 *)(ADDR)(p_jump_retarget+i*4) = aIns[tins1]._opt_addr;
                    }
                    else
                        *(ADDR32 *)(ADDR)(p_jump_retarget+i*4) = aBb[tbb]._opt_code_addr;

                    tOutLoop = 1;
                    while(tOutLoop < nOutLp) {
                        if(ArrayExist(aOutLoop[tOutLoop]._member, tbb) && (aOutLoop[tOutLoop]._entry!=tbb))
                            aOutLoop[tOutLoop]._flag |= FUN_OPT_CANCLED;
                        tOutLoop ++;
                    }
                }
                else
                    *(ADDR32 *)(ADDR)(p_jump_retarget+i*4) = temp;
            }

            ASSERT(*(UINT32 *)(ADDR)(aIns[iins]._opt_addr-4)==p_jump_target, ("Cannot find the pointer to jump target address in code cache.\n"));
            *(UINT32 *)(ADDR)(aIns[iins]._opt_addr-4) = p_jump_retarget;
        }
    
        ibb = aBb[ibb]._next;
    }
}

#ifdef _PROMOTE_NON_STACK
void PromoteNonStack() {
    OPERAND *p_operand;
    char *p_code_cache;
    BBINDEX ibb, pbb, tbb, tpbb;
    INSINDEX iins;
    OUTLPINDEX iOutLoop;
    REMINDEX irem;
    BBLKINDEX tbblk, tsucc;
    int i;

    curr_code_ptr = mm_pool._code_cache_info.p_cache_free;
    aFun[ifun]._opt_code_addr = (ADDR32)curr_code_ptr;

    ibb = aFun[ifun]._ibb_entry;
    while(ibb) {
        if(aBb[ibb]._entry_addr == 0x805178d)
            break;
        ibb = aBb[ibb]._next;
    }

    ASSERT(ibb&&aBb[ibb]._entry_addr == 0x805178d, ("Cannot find BB index.\n"));
    iOutLoop = 1;
    while(iOutLoop < nOutLp) {
        if(aOutLoop[iOutLoop]._flag&LOOP_OPT_CANCLED) {
            iOutLoop ++;
            continue;
        }
        if(ArraySExist(aOutLoop[iOutLoop]._member, ibb))
            break;
        iOutLoop ++;
    }

    aFun[ifun]._rem_base = BT_R_EDX;
    if(iOutLoop < nOutLp)
        RemInBb(ibb, iOutLoop, 1);

    RemListSort(iOutLoop);

    curr_code_ptr = mm_pool._code_cache_info.p_cache_free;
    aFun[ifun]._opt_code_addr = (ADDR32)curr_code_ptr;

    iGpr = EX_R8;
    iXmm = EX_XMM8;
    iMmx = EX_MM0;
    irem = aOutLoop[iOutLoop]._rem_list;
    while(irem) {
        if(aRem[irem]._gpr_num && aRem[irem]._xmm_num)
            aRem[irem]._allotted_reg = EX_NONE;
        else if(aRem[irem]._gpr_num && iGpr<EX_XMM8) {
            aRem[irem]._allotted_reg = iGpr;
            iGpr = (AVAIL_REGS)((int)iGpr + 1);
        }
        else if(aRem[irem]._xmm_num && iXmm<EX_MM0) {
            aRem[irem]._allotted_reg = iXmm;
            iXmm = (AVAIL_REGS)((int)iXmm + 1);
        }
        else if(aRem[irem]._gpr_num+aRem[irem]._xmm_num==0) {
            if(iGpr<EX_XMM8 && aRem[irem]._trans_num>aRem[irem]._trans_xmm_num) {
                aRem[irem]._allotted_reg = iGpr;
                iGpr = (AVAIL_REGS)((int)iGpr + 1);
            }
            else if(iXmm < EX_MM0) {
                aRem[irem]._allotted_reg = iXmm;
                iXmm = (AVAIL_REGS)((int)iXmm + 1);
            }
          #ifdef _USE_MMX_REG
            else if(aRem[irem]._trans_xmm_num==0 && iMmx < EX_XMM0) {
                aRem[irem]._allotted_reg = iMmx;
                iMmx = (AVAIL_REGS)((int)iMmx + 1);
            }
          #endif
            else if(iGpr < EX_XMM8){
                aRem[irem]._allotted_reg = iGpr;
                iGpr = (AVAIL_REGS)((int)iGpr + 1);
            }
            else
                aRem[irem]._allotted_reg = EX_NONE;
        }

        ModifyRemIns(irem);

        irem = aRem[irem]._next;
    }

    
    ibb = aFun[ifun]._ibb_entry;
    pbb = INVALID;

    while(ibb) {
        if(ArraySExist(aOutLoop[iOutLoop]._member, ibb)) {
            OptimizingBb(ibb);

            if(aOutLoop[iOutLoop]._entry==ibb) {
                tbblk = aBb[ibb]._pred_bb;
                ASSERT(!ArraySExist(aOutLoop[iOutLoop]._member, pbb), ("unexpected case.\n"));
                while(tbblk) {
                    tpbb = aBblk[tbblk]._ibb;
                    if(!ArraySExist(aOutLoop[iOutLoop]._member, tpbb) && tpbb!=pbb)
                        break;

                    tbblk = aBblk[tbblk]._next;
                }

                if(tbblk) {
                    tbb = BbNew();
                    aBb[tbb]._opt_code_addr = (ADDR32)curr_code_ptr;
                    aBb[ibb]._flag |= BB_OPTIMIZED;
                    while(tbblk) {
                        tpbb = aBblk[tbblk]._ibb;
                        if(!ArraySExist(aOutLoop[iOutLoop]._member, tpbb) && tpbb!=pbb) {
                            tsucc = aBb[tpbb]._succ_bb;
                            while(tsucc) {
                                if(aBblk[tsucc]._ibb == ibb)
                                    aBblk[tsucc]._ibb = tbb;

                                tsucc = aBblk[tsucc]._next;
                            }
                        }
                        tbblk = aBblk[tbblk]._next;
                    }
                }

                ModeSwitch(COMPAT_TO_LONG);
                
            }

            aBb[ibb]._opt_code_addr = (ADDR32)curr_code_ptr;
            aBb[ibb]._flag |= BB_OPTIMIZED;
            iins = aBb[ibb]._ins_first;

            while(iins!=aBb[ibb]._ins_last) {
                if(aIns[iins]._addr == 0x80517bd)
                    Preload(aOutLoop[iOutLoop]._rem_list);
                GenX64Code(iins);
                iins = aIns[iins]._succ;
            }

            aIns[iins]._opt_addr = (ADDR32)curr_code_ptr;
            if(aIns[iins]._op>BT_Iljmp && aIns[iins]._op<BT_Iloop) {
                if((aIns[iins]._binary[0]&0xf0) == 0x70) {
                    *((UINT8 *)curr_code_ptr) = 0x0f;
                    curr_code_ptr += 1;
                    *((UINT8 *)curr_code_ptr) = 0x80 | (aIns[iins]._binary[0]&0x0f);
                    curr_code_ptr += 1;
                    *((int *)curr_code_ptr) = *(signed char *)(aIns[iins]._binary+1);
                    curr_code_ptr += 4;

                    aIns[iins]._size += 3;
                }
                else {
                    p_code_cache = (char *)curr_code_ptr;
                    for(i=0; i<aIns[iins]._size; i++)
                        p_code_cache[i] = aIns[iins]._binary[i];

                    curr_code_ptr += aIns[iins]._size;
                }
            }
            else if(aIns[iins]._op == BT_Ijmp) {
                if(aIns[iins]._binary[0] == (char)0xeb) {
                    *((UINT8 *)curr_code_ptr) = 0xe9;
                    curr_code_ptr += 1;
                    *((int *)curr_code_ptr) = *(signed char *)(aIns[iins]._binary+1);
                    curr_code_ptr += 4;

                    aIns[iins]._size += 3;
                }
                else {
                    p_code_cache = (char *)curr_code_ptr;
                    for(i=0; i<aIns[iins]._size; i++)
                        p_code_cache[i] = aIns[iins]._binary[i];

                    curr_code_ptr += aIns[iins]._size;
                }
            }
            else
                GenX64Code(iins);

            if(ArrayExist(aOutLoop[iOutLoop]._exit, ibb)) {
                tbblk = aBb[ibb]._succ_bb;
                while(tbblk) {
                    tpbb = aBblk[tbblk]._ibb;
                    if(!ArraySExist(aOutLoop[iOutLoop]._member, tpbb)) {
                        if(aBb[ibb]._next == tpbb) {
                            if((aOutLoop[iOutLoop]._flag&LOOP_OPT_REGION)==0)
                                Synchronization(aOutLoop[iOutLoop]._rem_list);
                            ModeSwitch(LONG_TO_COMPAT);
                        }
                        else {
                            WARNING(("unexpected case.\n"))
                        }
                    }

                    tbblk = aBblk[tbblk]._next;
                }
            }
        }
        else {
            aBb[ibb]._opt_code_addr = (ADDR32)curr_code_ptr;
            iins = aBb[ibb]._ins_first;
            while(iins < aBb[ibb]._ins_last) {
                aIns[iins]._opt_addr = (ADDR32)curr_code_ptr;

                p_code_cache = (char *)curr_code_ptr;
                for(i=0; i<aIns[iins]._size; i++)
                    p_code_cache[i] = aIns[iins]._binary[i];
                curr_code_ptr = curr_code_ptr + aIns[iins]._size;
    
                iins ++;
            }

            aIns[iins]._opt_addr = (ADDR32)curr_code_ptr;
            if(aIns[iins]._op>BT_Iljmp && aIns[iins]._op<BT_Iloop) {
                if((aIns[iins]._binary[0]&0xf0) == 0x70) {
                    *((UINT8 *)curr_code_ptr) = 0x0f;
                    curr_code_ptr += 1;
                    *((UINT8 *)curr_code_ptr) = 0x80 | (aIns[iins]._binary[0]&0x0f);
                    curr_code_ptr += 1;
                    *((INT32 *)curr_code_ptr) = *(INT8 *)(aIns[iins]._binary+1);
                    curr_code_ptr += 4;

                    aIns[iins]._size += 3;
                }
                else {
                    *((UINT8 *)curr_code_ptr) = aIns[iins]._binary[0];
                    curr_code_ptr += 1;
                    *((UINT8 *)curr_code_ptr) = aIns[iins]._binary[1];
                    curr_code_ptr += 1;
                    *((INT32 *)curr_code_ptr) = *(INT32 *)(aIns[iins]._binary+2);
                    curr_code_ptr += 4;
                }
            }
            else if(aIns[iins]._op == BT_Ijmp) {
                if(aIns[iins]._binary[0] == (char)0xeb) {
                    *((UINT8 *)curr_code_ptr) = 0xe9;
                    curr_code_ptr += 1;
                    *((int *)curr_code_ptr) = *(signed char *)(aIns[iins]._binary+1);
                    curr_code_ptr += 4;

                    aIns[iins]._size += 3;
                }
                else {
                    p_code_cache = (char *)curr_code_ptr;
                    for(i=0; i<aIns[iins]._size; i++)
                        p_code_cache[i] = aIns[iins]._binary[i];

                    curr_code_ptr += aIns[iins]._size;
                }
            }
            else {
                p_code_cache = (char *)curr_code_ptr;
                for(i=0; i<aIns[iins]._size; i++)
                    p_code_cache[i] = aIns[iins]._binary[i];

                curr_code_ptr += aIns[iins]._size;
            }
        }

        pbb = ibb;
        ibb = aBb[ibb]._next;
    }

        //adjust the displacement
    ibb = aFun[ifun]._ibb_entry;
    while(ibb) {
        ADDR p_opt_instr;
        INT32 offset;
        iins = aBb[ibb]._ins_last;
        p_opt_instr = aIns[iins]._opt_addr;

        tbblk = aBb[ibb]._succ_bb;
        if(aIns[iins]._op>BT_Iljmp && aIns[iins]._op<BT_Iloop && *(char *)p_opt_instr==0x0f) {
            tbblk = aBblk[tbblk]._next;
            tbb = aBblk[tbblk]._ibb;
            offset = aBb[tbb]._opt_code_addr - (INT32)p_opt_instr - 6;
            *(INT32 *)(p_opt_instr+2) = offset;
        }
        else if(aIns[iins]._op==BT_Icall && *(char *)p_opt_instr==(char)0xe8) {
            offset = aIns[iins]._addr_next + aIns[iins]._operand[0].lval.sdword - (INT32)p_opt_instr - 5;
            *(INT32 *)(p_opt_instr+1) = offset;
        }
        else if(aIns[iins]._op==BT_Ijmp && *(char *)p_opt_instr==(char)0xe9) {
            tbb = aBblk[tbblk]._ibb;
            offset = aBb[tbb]._opt_code_addr - (INT32)p_opt_instr - 5;
            *(INT32 *)(p_opt_instr+1) = offset;
        }
        else if(aIns[iins]._op==BT_Ijmpin) {
            WARNING(("Existing jmpin.\n"))
        }
    
        ibb = aBb[ibb]._next;
    }

    CodeCacheAlloc(curr_code_ptr-mm_pool._code_cache_info.p_cache_free);
}
#endif

