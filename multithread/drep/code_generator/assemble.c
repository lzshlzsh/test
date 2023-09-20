#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem_manage.h"
#include "utility.h"
#include "assemble.h"
#include "optimization.h"

void PreloadSTRem(REMINDEX irem) {
    AVAIL_REGS reg = aRem[irem]._allotted_reg;
    INT32 oper_size = aRem[irem]._rem_size;
    INT32 offset = aRem[irem]._offset;
    REGISTER_TYPE base = aFun[ifun]._rem_base;
    char *p_code_cache = (char *)curr_code_ptr;
    struct modrm t_modrm;

    INT32 index = 0;

    if(reg==EX_NONE || reg==EX_ALIAS_MEM)
        return;

    if(base == BT_R_ESP)
        t_modrm.rm = 4;
  #ifdef _PROMOTE_NON_STACK
    else if(base == BT_R_EDX)
        t_modrm.rm = 2;
  #endif
    else 
        t_modrm.rm = 5;
        
    if(reg<EX_XMM8) {
        if(oper_size == 32)
            p_code_cache[index++] = 0x44;
        else
            p_code_cache[index++] = 0x4c;
        
        p_code_cache[index++] = 0x8b;
            
        if(offset>-127 && offset<127) {
            t_modrm.mod = 1;
            t_modrm.reg = reg - EX_R8;

            p_code_cache[index++] = *(char *)(&t_modrm);
            if(base == BT_R_ESP)
                p_code_cache[index++] = 0x24;
            p_code_cache[index++] = (INT8)offset;
        }
        else {
            t_modrm.mod = 2;
            t_modrm.reg = reg - EX_R8;

            p_code_cache[index++] = *(char *)(&t_modrm);
            if(base == BT_R_ESP)
                p_code_cache[index++] = 0x24;
            *(INT32 *)(p_code_cache+index) = offset;
            index += 4;
        }
    }
    else if(reg<EX_MM0) {
      #ifdef _USE_XMM_HIGH
        if(aRem[irem]._xmm_order) {
            p_code_cache[index++] = 0x66;
            p_code_cache[index++] = 0x44;
            p_code_cache[index++] = 0x0f;
            p_code_cache[index++] = 0x3a;
            p_code_cache[index++] = 0x22;
        }
        else
      #endif
        if(oper_size==32) {
            p_code_cache[index++] = 0x66;
            p_code_cache[index++] = 0x44;
            p_code_cache[index++] = 0x0f;
            p_code_cache[index++] = 0x6e;
        }
        else if(oper_size==64) {
            p_code_cache[index++] = 0xf2;
            p_code_cache[index++] = 0x44;
            p_code_cache[index++] = 0x0f;
            p_code_cache[index++] = 0x10;
        }
        else {
            p_code_cache[index++] = 0x44;
            p_code_cache[index++] = 0x0f;
            p_code_cache[index++] = 0x28;
        }
        
        if(offset>-127 && offset<127) {
            t_modrm.mod = 1;
            t_modrm.reg = reg - EX_XMM8;

            p_code_cache[index++] = *(char *)(&t_modrm);
            if(base == BT_R_ESP)
                p_code_cache[index++] = 0x24;
            p_code_cache[index++] = (INT8)offset;
        }
        else {
            t_modrm.mod = 2;
            t_modrm.reg = reg - EX_XMM8;

            p_code_cache[index++] = *(char *)(&t_modrm);
            if(base == BT_R_ESP)
                p_code_cache[index++] = 0x24;
            *(INT32 *)(p_code_cache+index) = offset;
            index += 4;
        }
      #ifdef _USE_XMM_HIGH
        if(aRem[irem]._xmm_order)
            p_code_cache[index++] = aRem[irem]._xmm_order;
      #endif
    }
    else if(reg<EX_XMM0) {
        if(oper_size==32) {
            p_code_cache[index++] = 0x0f;
            p_code_cache[index++] = 0x6e;
        }
        else {
            p_code_cache[index++] = 0x0f;
            p_code_cache[index++] = 0x6f;
        }
        if(offset>-127 && offset<127) {
            t_modrm.mod = 1;
            t_modrm.reg = reg - EX_MM0;

            p_code_cache[index++] = *(char *)(&t_modrm);
            if(base == BT_R_ESP)
                p_code_cache[index++] = 0x24;
            p_code_cache[index++] = (INT8)offset;
        }
        else {
            t_modrm.mod = 2;
            t_modrm.reg = reg - EX_MM0;

            p_code_cache[index++] = *(char *)(&t_modrm);
            if(base == BT_R_ESP)
                p_code_cache[index++] = 0x24;
            *(INT32 *)(p_code_cache+index) = offset;
            index += 4;
        }
    }
    else if(reg<EX_ALIAS_MEM) {
        p_code_cache[index++] = 0x66;
        p_code_cache[index++] = 0x0f;
        p_code_cache[index++] = 0x6e;
        if(offset>-127 && offset<127) {
            t_modrm.mod = 1;
            t_modrm.reg = reg - EX_XMM0;

            p_code_cache[index++] = *(char *)(&t_modrm);
            if(base == BT_R_ESP)
                p_code_cache[index++] = 0x24;
            p_code_cache[index++] = (INT8)offset;
        }
        else {
            t_modrm.mod = 2;
            t_modrm.reg = reg - EX_XMM0;

            p_code_cache[index++] = *(char *)(&t_modrm);
            if(base == BT_R_ESP)
                p_code_cache[index++] = 0x24;
            *(INT32 *)(p_code_cache+index) = offset;
            index += 4;
        }
    }
    
    curr_code_ptr += index;
}

void SynchronizeSTRem(REMINDEX irem) {
    AVAIL_REGS reg = aRem[irem]._allotted_reg;
    INT32 oper_size = aRem[irem]._rem_size;
    INT32 offset = aRem[irem]._offset;
    REGISTER_TYPE base = aFun[ifun]._rem_base;
    char *p_code_cache = (char *)curr_code_ptr;
    struct modrm t_modrm;

    INT32 index = 0;

    if(reg==EX_NONE || reg==EX_ALIAS_MEM)
        return;

    if(base==BT_R_ESP)
        t_modrm.rm = 4;
  #ifdef _PROMOTE_NON_STACK
    else if(base == BT_R_EDX)
        t_modrm.rm = 2;
  #endif
    else 
        t_modrm.rm = 5;
        
    if(reg<EX_XMM8) {
        if(oper_size == 32)
            p_code_cache[index++] = 0x44;
        else
            p_code_cache[index++] = 0x4c;
        
        p_code_cache[index++] = 0x89;
        
        if(offset>-127 && offset<127) {
            t_modrm.mod = 1;
            t_modrm.reg = reg - EX_R8;

            p_code_cache[index++] = *(char *)(&t_modrm);
            if(base == BT_R_ESP)
                p_code_cache[index++] = 0x24;
            p_code_cache[index++] = (INT8)offset;
        }
        else {
            t_modrm.mod = 2;
            t_modrm.reg = reg - EX_R8;

            p_code_cache[index++] = *(char *)(&t_modrm);
            if(base == BT_R_ESP)
                p_code_cache[index++] = 0x24;
            *(INT32 *)(p_code_cache+index) = offset;
            index += 4;
        }
    }
    else if(reg<EX_MM0) {
      #ifdef _USE_XMM_HIGH
        if(aRem[irem]._xmm_order) {
            p_code_cache[index++] = 0x66;
            p_code_cache[index++] = 0x44;
            p_code_cache[index++] = 0x0f;
            p_code_cache[index++] = 0x3a;
            p_code_cache[index++] = 0x16;
        }
        else
      #endif
        if(oper_size==32) {
            p_code_cache[index++] = 0x66;
            p_code_cache[index++] = 0x44;
            p_code_cache[index++] = 0x0f;
            p_code_cache[index++] = 0x7e;
        }
        else if(oper_size==64) {
            p_code_cache[index++] = 0xf2;
            p_code_cache[index++] = 0x44;
            p_code_cache[index++] = 0x0f;
            p_code_cache[index++] = 0x11;
        }
        else {
            p_code_cache[index++] = 0x44;
            p_code_cache[index++] = 0x0f;
            p_code_cache[index++] = 0x29;
        }
        
        if(offset>-127 && offset<127) {
            t_modrm.mod = 1;
            t_modrm.reg = reg - EX_XMM8;

            p_code_cache[index++] = *(char *)(&t_modrm);
            if(base == BT_R_ESP)
                p_code_cache[index++] = 0x24;
            p_code_cache[index++] = (INT8)offset;
        }
        else {
            t_modrm.mod = 2;
            t_modrm.reg = reg - EX_XMM8;

            p_code_cache[index++] = *(char *)(&t_modrm);
            if(base == BT_R_ESP)
                p_code_cache[index++] = 0x24;
            *(INT32 *)(p_code_cache+index) = offset;

            index += 4;
        }
      #ifdef _USE_XMM_HIGH
        if(aRem[irem]._xmm_order)
            p_code_cache[index++] = aRem[irem]._xmm_order;
      #endif
    }
    else if(reg<EX_XMM0) {
        if(oper_size==32) {
            p_code_cache[index++] = 0x0f;
            p_code_cache[index++] = 0x7e;
        }
        else {
            p_code_cache[index++] = 0x0f;
            p_code_cache[index++] = 0x7f;
        }
        if(offset>-127 && offset<127) {
            t_modrm.mod = 1;
            t_modrm.reg = reg - EX_MM0;

            p_code_cache[index++] = *(char *)(&t_modrm);
            if(base == BT_R_ESP)
                p_code_cache[index++] = 0x24;
            p_code_cache[index++] = (INT8)offset;
        }
        else {
            t_modrm.mod = 2;
            t_modrm.reg = reg - EX_MM0;

            p_code_cache[index++] = *(char *)(&t_modrm);
            if(base == BT_R_ESP)
                p_code_cache[index++] = 0x24;
            *(INT32 *)(p_code_cache+index) = offset;

            index += 4;
        }
    }
    else if(reg<EX_ALIAS_MEM) {
        p_code_cache[index++] = 0x66;
        p_code_cache[index++] = 0x0f;
        p_code_cache[index++] = 0x7e;
        if(offset>-127 && offset<127) {
            t_modrm.mod = 1;
            t_modrm.reg = reg - EX_XMM0;

            p_code_cache[index++] = *(char *)(&t_modrm);
            if(base == BT_R_ESP)
                p_code_cache[index++] = 0x24;
            p_code_cache[index++] = (INT8)offset;
        }
        else {
            t_modrm.mod = 2;
            t_modrm.reg = reg - EX_XMM0;

            p_code_cache[index++] = *(char *)(&t_modrm);
            if(base == BT_R_ESP)
                p_code_cache[index++] = 0x24;
            *(INT32 *)(p_code_cache+index) = offset;

            index += 4;
        }
    }
    
    curr_code_ptr += index;
}

void GenOptimizeStackIns(INSINDEX iins, REMINDEX irem) {
    char instr_buffer[16] = {0};
    char *instr_code = aIns[iins]._binary;
    REGISTER_TYPE base = aFun[ifun]._rem_base;
    AVAIL_REGS allocate_reg = aRem[irem]._allotted_reg;
    struct modrm *p_modrm;

    int i=0, j=0;

    if(allocate_reg==EX_NONE || allocate_reg==EX_ALIAS_MEM)
        return;
    
    if(aIns[iins]._op==BT_Imov) {
        if(allocate_reg < EX_XMM8) {
            if(instr_code[i] == 0x66) {
                instr_buffer[j++] = 0x66;
                i++;
            }
            
            instr_buffer[j++] = 0x41;
            instr_buffer[j++] = instr_code[i++]; //opcode
            instr_buffer[j++] = instr_code[i++]; //modrm
            p_modrm = (struct modrm *)(instr_buffer+j-1);
            p_modrm->mod = 0x3;
            p_modrm->rm = allocate_reg - EX_R8;

            p_modrm = (struct modrm *)(instr_code+i-1);
            if(base == BT_R_ESP)
                i += 1;

            if(p_modrm->mod==0x1)
                i += 1;
            else if(p_modrm->mod==0x2)
                i += 4;
                
            while(i<aIns[iins]._size)
                instr_buffer[j++] = instr_code[i++];
        }
        else if(allocate_reg<EX_MM0) {
          #ifdef _USE_XMM_HIGH
            if(aRem[irem]._xmm_order==0 && instr_code[0]!=(char)0x89) {
                aIns[iins]._op = BT_Imovd;
                instr_buffer[j++] = 0x66;
                instr_buffer[j++] = 0x44;
                instr_buffer[j++] = 0x0f;
                instr_buffer[j++] = 0x7e;

                p_modrm = (struct modrm *)(instr_buffer+j);
                p_modrm->mod = 0x3;
                p_modrm->reg = allocate_reg - EX_XMM8;
                p_modrm->rm = (instr_code[1] >> 3)&0x7;

                j += 1;
            }
            else {
                aIns[iins]._op = BT_Ipextrd;  //should be pextrd, but the disassembler does not support sse4
                if(instr_code[0] == (char)0x89) {  //reg to mem --> reg to xmmreg
                    instr_buffer[0] = 0x66;
                    instr_buffer[1] = 0x44;
                    instr_buffer[2] = 0x0f;
                    instr_buffer[3] = 0x3a;
                    instr_buffer[4] = 0x22;
                    p_modrm = (struct modrm *)(instr_buffer+5);
                    p_modrm->mod = 0x3;
                    p_modrm->reg = allocate_reg - EX_XMM8;
                    p_modrm->rm = (instr_code[1] >> 3)&0x7;
                }
                else {
                    instr_buffer[0] = 0x66;
                    instr_buffer[1] = 0x44;
                    instr_buffer[2] = 0x0f;
                    instr_buffer[3] = 0x3a;
                    instr_buffer[4] = 0x16;
                    p_modrm = (struct modrm *)(instr_buffer+5);
                    p_modrm->mod = 0x3;
                    p_modrm->reg = allocate_reg - EX_XMM8;
                    p_modrm->rm = (instr_code[1] >> 3)&0x7;
                }

                instr_buffer[6] = aRem[irem]._xmm_order;
                j = 7;
            }
          #else
            if(aRem[irem]._xmm_order==0) {
                aIns[iins]._op = BT_Imovd;
                instr_buffer[j++] = 0x66;
                instr_buffer[j++] = 0x44;
                instr_buffer[j++] = 0x0f;
                if(instr_code[0] == (char)0x89) //reg to mem
                    instr_buffer[j++] = 0x6e;
                else //mem to reg
                    instr_buffer[j++] = 0x7e;

                p_modrm = (struct modrm *)(instr_buffer+j);
                p_modrm->mod = 0x3;
                p_modrm->reg = allocate_reg - EX_XMM8;
                p_modrm->rm = (instr_code[1] >> 3)&0x7;

                j += 1;
            }
          #endif
        }
        else if(allocate_reg < EX_XMM0) {
            aIns[iins]._op = BT_Imovd;
            
            instr_buffer[j++] = 0x0f;
            if(instr_code[0] == (char)0x89) //reg to mem
                instr_buffer[j++] = 0x6e;
            else //mem to reg
                instr_buffer[j++] = 0x7e;

            p_modrm = (struct modrm *)(instr_buffer+j);
            p_modrm->mod = 0x3;
            p_modrm->reg = allocate_reg - EX_MM0;
            p_modrm->rm = (instr_code[1] >> 3)&0x7;

            j++;
        }
        else if(allocate_reg<EX_ALIAS_MEM) {
            aIns[iins]._op = BT_Imovd;
            
            instr_buffer[j++] = 0x66;
            instr_buffer[j++] = 0x0f;
            if(instr_code[0] == (char)0x89) //reg to mem
                instr_buffer[j++] = 0x6e;
            else //mem to reg
                instr_buffer[j++] = 0x7e;

            p_modrm = (struct modrm *)(instr_buffer+j);
            p_modrm->mod = 0x3;
            p_modrm->reg = allocate_reg - EX_XMM0;
            p_modrm->rm = (instr_code[1] >> 3)&0x7;

            j += 1;
        }
        /**else {
            if(instr_code[i] == 0x66)
                instr_buffer[j++] = instr_code[i++];
            instr_buffer[j++] = instr_code[i++];
            instr_buffer[j++] = instr_code[i++];
            p_modrm = (struct modrm *)(instr_buffer+j-1);
            
            if(p_modrm->mod == 0) {
                p_modrm->mod = 2;
                *(int *)(instr_buffer+j) = alias_mem_offset;
                j += 4;
            }
            else if(p_modrm->mod == 1) {
                p_modrm->mod = 2;
                *(int *)(instr_buffer+j) = (signed char)instr_code[i] + alias_mem_offset;
                j += 4;
                i += 1;
            }
            else {
                *(int *)(instr_buffer+j) = *(int *)(instr_code+i) + alias_mem_offset;
                j += 4;
                i += 4;
            }
            
            while(i<aIns[iins]._size)
                instr_buffer[j++] = instr_code[i++];
        }*/
    }
    else if((aIns[iins]._op>BT_Ibswap && aIns[iins]._op<BT_Icbw) || aIns[iins]._op==BT_Icvtsi2ss || aIns[iins]._op==BT_Icvtsi2sd) {
        if(allocate_reg < EX_XMM8) {
            if(instr_code[i] == 0x66 || instr_code[i] == (char)0xf2 || instr_code[i] == (char)0xf3)
                instr_buffer[j++] = instr_code[i++];
            
            instr_buffer[j++] = 0x41;
            if(instr_code[i] == 0x0f)
                instr_buffer[j++] = instr_code[i++]; //opcode
            instr_buffer[j++] = instr_code[i++]; //opcode
            instr_buffer[j++] = instr_code[i++]; //modrm
            p_modrm = (struct modrm *)(instr_buffer+j-1);
            p_modrm->mod = 0x3;
            p_modrm->rm = allocate_reg - EX_R8;

            p_modrm = (struct modrm *)(instr_code+i-1);
            if(base == BT_R_ESP)
                i += 1;

            if(p_modrm->mod==0x1)
                i += 1;
            else if(p_modrm->mod == 0x2)
                i += 4;
                
            while(i<aIns[iins]._size)
                instr_buffer[j++] = instr_code[i++];
        }
        /**else {
            ASSERT(allocate_reg==EX_ALIAS_MEM, ("Error with allocated reg.\n"));
            if(instr_code[i] == 0x66 || instr_code[i] == (char)0xf2 || instr_code[i] == (char)0xf3)
                instr_buffer[j++] = instr_code[i++];
            
            if(instr_code[i] == 0x0f)
                instr_buffer[j++] = instr_code[i++]; //opcode
            instr_buffer[j++] = instr_code[i++];
            instr_buffer[j++] = instr_code[i++];
            
            p_modrm = (struct modrm *)(instr_buffer+j-1);
            if(p_modrm->mod == 0) {
                p_modrm->mod = 2;
                *(int *)(instr_buffer+j) = alias_mem_offset;
                j += 4;
            }
            else if(p_modrm->mod == 1) {
                p_modrm->mod = 2;
                *(int *)(instr_buffer+j) = (signed char)instr_code[i] + alias_mem_offset;
                j += 4;
                i += 1;
            }
            else {
                *(int *)(instr_buffer+j) = *(int *)(instr_code+i) + alias_mem_offset;
                j += 4;
                i += 4;
            }
            
            while(i<aIns[iins]._size)
                instr_buffer[j++] = instr_code[i++];
        }*/
    }
    else if(aIns[iins]._op>=BT_Iaddpd && aIns[iins]._op<=BT_Icvttss2si) {
        if(allocate_reg<EX_XMM8) {
            ASSERT(((aIns[iins]._op>=BT_Imovq&&aIns[iins]._op<=BT_Imovsd_sse) || aIns[iins]._op==BT_Imovd || aIns[iins]._op==BT_Imovss), ("The allocated reg for simd instruction is a GPR.\n"));

            instr_buffer[0] = 0x66;
            if(aIns[iins]._op==BT_Imovd || aIns[iins]._op==BT_Imovss)
                instr_buffer[1] = 0x41;
            else
                instr_buffer[1] = 0x49;
            instr_buffer[2] = 0x0f;
            if(aIns[iins]._operand[0].type == BT_OP_MEM)
                instr_buffer[3] = 0x7e;
            else
                instr_buffer[3] = 0x6e;

            p_modrm = (struct modrm *)(instr_buffer+4);
            p_modrm->mod = 3;
            if(aIns[iins]._op!=BT_Imovlps)
                p_modrm->reg = ((instr_code[3])>>3)&0x7;
            else
                p_modrm->reg = ((instr_code[2])>>3)&0x7;
            p_modrm->rm = allocate_reg - EX_R8;

            j = 5;
        }
        else if(allocate_reg<EX_MM0) {
            if(aIns[iins]._op == BT_Imovd) {
                instr_code[0] = 0xf3;
                if(instr_code[2]==0x6e)
                    instr_code[2] = 0x10;
                else
                    instr_code[2] = 0x11;
            }

            if(aIns[iins]._op==BT_Imovss) {
                aIns[iins]._op = BT_Imovaps;

                instr_buffer[0] = 0x41;
                instr_buffer[1] = 0x0f;
                if(instr_code[2]==0x10)
                    instr_buffer[2] = 0x28;
                else
                    instr_buffer[2] = 0x29;
                instr_buffer[3] = instr_code[3];
                p_modrm = (struct modrm *)(instr_buffer+3);
                p_modrm->mod = 0x3;
                p_modrm->rm = allocate_reg - EX_XMM8;

                j = 4;
            }
            else if(aIns[iins]._op==BT_Imovsd_sse) {
                aIns[iins]._op = BT_Imovapd;

                instr_buffer[0] = 0x66;
                instr_buffer[1] = 0x41;
                instr_buffer[2] = 0x0f;
                if(instr_code[2]==0x10)
                    instr_buffer[3] = 0x28;
                else
                    instr_buffer[3] = 0x29;
                instr_buffer[4] = instr_code[3];
                p_modrm = (struct modrm *)(instr_buffer+4);
                p_modrm->mod = 0x3;
                p_modrm->rm = allocate_reg - EX_XMM8;

                j = 5;
            }
            else {
                if(instr_code[i] == 0x66 || instr_code[i] == (char)0xf2 || instr_code[i] == (char)0xf3)
                    instr_buffer[j++] = instr_code[i++];
                instr_buffer[j++] = 0x41;
                if(instr_code[i] == 0x0f)
                    instr_buffer[j++] = instr_code[i++];
            
                instr_buffer[j++] = instr_code[i++];
                instr_buffer[j++] = instr_code[i++];

                p_modrm = (struct modrm *)(instr_buffer+j-1);
                if(base == BT_R_ESP)
                    i += 1;
                if(p_modrm->mod==1)
                    i+=1;
                else if(p_modrm->mod==2)
                    i+=4;
                p_modrm->mod = 0x3;
                p_modrm->rm = allocate_reg - EX_XMM8;

                while(i<aIns[iins]._size)
                    instr_buffer[j++] = instr_code[i++];
            }
        }
        /**else {
            ASSERT(allocate_reg==EX_ALIAS_MEM, ("Error with allocated reg.\n"));
            if(instr_code[i] == 0x66 || instr_code[i] == (char)0xf2 || instr_code[i] == (char)0xf3)
                instr_buffer[j++] = instr_code[i++];
            if(instr_code[i] == 0x0f)
                instr_buffer[j++] = instr_code[i++];
            instr_buffer[j++] = instr_code[i++];
            
            instr_buffer[j++] = instr_code[i++];
            p_modrm = (struct modrm *)(instr_buffer+j-1);
            
            if(p_modrm->mod == 0) {
                p_modrm->mod = 2;
                *(int *)(instr_buffer+j) = alias_mem_offset;
                j += 4;
            }
            else if(p_modrm->mod == 1) {
                p_modrm->mod = 2;
                *(int *)(instr_buffer+j) = (signed char)instr_code[i] + alias_mem_offset;
                j += 4;
                i += 1;
            }
            else {
                *(int *)(instr_buffer+j) = *(int *)(instr_code+i) + alias_mem_offset;
                j += 4;
                i += 4;
            }
            
            while(i<aIns[iins]._size)
                instr_buffer[j++] = instr_code[i++];
        }*/
    }
    else if(aIns[iins]._op>BT_Ifabs && aIns[iins]._op<BT_Iftst) {
        ASSERT(allocate_reg==EX_ALIAS_MEM, ("Error with allocated reg.\n"));
        /**
        instr_buffer[j++] = instr_code[i++];
        instr_buffer[j++] = instr_code[i++];
        
        p_modrm = (struct modrm *)(instr_buffer+j-1);

        if(p_modrm->mod == 0) {
            p_modrm->mod = 2;
            *(int *)(instr_buffer+j) = alias_mem_offset;
            j += 4;
        }
        else if(p_modrm->mod == 1) {
            p_modrm->mod = 2;
            *(int *)(instr_buffer+j) = (signed char)instr_code[i] + alias_mem_offset;
            j += 4;
            i += 1;
        }
        else {
            *(int *)(instr_buffer+j) = *(int *)(instr_code+i) + alias_mem_offset;
            j += 4;
            i += 4;
        }
        
        while(i<aIns[iins]._size)
            instr_buffer[j++] = instr_code[i++];*/
    }
    else
        ERROR(("Instruction 0x%x is not handled currently.\n", aIns[iins]._addr));
        
    for(i=0; i<j; i++)
        instr_code[i] = instr_buffer[i];

    aIns[iins]._size = j;
}


void DisposeFuncArg(INSINDEX iins, int offset) {
    char instr_buffer[16] = {0};
    char *instr_code = aIns[iins]._binary;
    REGISTER_TYPE base = aFun[ifun]._rem_base;
    struct modrm *p_modrm;

    int i=0, j=0;

    ASSERT(aIns[iins]._op!=BT_Ipush, ("Instruction push ##(esp) is not handled.\n"))

    if(instr_code[i] == 0x66 || instr_code[i] == (char)0xf2 || instr_code[i] == (char)0xf3)
        instr_buffer[j++] = instr_code[i++];
    
    instr_buffer[j++] = 0x41;
    
    if(instr_code[i] == 0x0f)
        instr_buffer[j++] = instr_code[i++];
    
    instr_buffer[j++] = instr_code[i++]; //opcode
    instr_buffer[j++] = instr_code[i++]; //modrm
    p_modrm = (struct modrm *)(instr_buffer+j-1);
    p_modrm->rm = 7;

    if(base == BT_R_ESP)
        i += 1;

    if(p_modrm->mod==0x1) 
        i += 1;
    else if(p_modrm->mod==0x2)
        i += 4;

    if(offset<=127) {
        instr_buffer[j++] = offset;
        p_modrm->mod = 1;
    }
    else {
        *(int *)(instr_buffer+j) = offset;
        j += 4;
        p_modrm->mod = 1;
    }
            
    while(i<aIns[iins]._size)
        instr_buffer[j++] = instr_code[i++];
            
    for(i=0; i<j; i++)
        instr_code[i] = instr_buffer[i];

    aIns[iins]._size = j;
} 

void GenX64Code(INSINDEX iins) {
    char *p_instr_code, *p_code_cache;
    int i, opr_index, prefix_index, instr_size;
    int index_new, index_old;
    struct modrm *p_modrm;
    BOOL adjust_esp = FALSE, adjust_ebp = FALSE;

    if(aIns[iins]._size==0)
        return;
    
    aIns[iins]._opt_addr = (ADDR32)curr_code_ptr;
    p_instr_code = aIns[iins]._binary;

  #ifndef _NO_STACK_SWITCH
    if((aIns[iins]._use&(BT_R_ESP-BT_R_EAX)) && (aIns[iins]._def&(BT_R_ESP-BT_R_EAX))==0) { 
        for(opr_index=0; opr_index<aIns[iins]._opndnum; opr_index++) {
            if(aIns[iins]._operand[opr_index].type==BT_OP_REG && aIns[iins]._operand[opr_index].base==BT_R_ESP) {
                OUTPUT(("WARNING: Instruction OPCODE esp, REG exists.\n"));
                *(UINT16 *)curr_code_ptr = 0xa48d;
                curr_code_ptr += 2;
                *(UINT8 *)curr_code_ptr = 0x24;
                curr_code_ptr += 1;
                *(INT32 *)curr_code_ptr = -alias_mem_offset;
                curr_code_ptr += 4;
                adjust_esp = TRUE;
                break;
            }
        }
    }

    if(aFun[ifun]._rem_base==BT_R_EBP && (aIns[iins]._use&(BT_R_EBP-BT_R_EAX)) && (aIns[iins]._def&(BT_R_EBP-BT_R_EAX))==0) {
        for(i=aIns[iins]._dest_opnd_num; i<aIns[iins]._opndnum; i++) {
            if(aIns[iins]._operand[i].type==BT_OP_REG && aIns[iins]._operand[i].base==BT_R_EBP) {
                OUTPUT(("WARNING: Instruction OPCODE ebp, REG exists. 0x%lx\n", aIns[iins]._addr));
                *(UINT16 *)curr_code_ptr = 0xad8d;
                curr_code_ptr += 2;
                *(INT32 *)curr_code_ptr = -alias_mem_offset;
                curr_code_ptr += 4;
                adjust_ebp = TRUE;
                break;
            }
        }
    }
  #endif

    for(opr_index=0; opr_index<aIns[iins]._opndnum; opr_index++)
        if(aIns[iins]._operand[opr_index].type == BT_OP_MEM)
            break;

    if(opr_index!=aIns[iins]._opndnum) {
      #ifdef _NO_OPT_SIB
        if(aIns[iins]._op!=BT_Ilea && aIns[iins]._operand[opr_index].index && (aIns[iins]._operand[opr_index].scale || aIns[iins]._operand[opr_index].base)) {
            if(p_instr_code[0]==(char)0xf2 || p_instr_code[0]==(char)0xf3) {
                *(char *)curr_code_ptr = p_instr_code[0];
                curr_code_ptr += 1;
                *(char *)curr_code_ptr = 0x67;
                curr_code_ptr += 1;

                p_instr_code += 1;
                instr_size = aIns[iins]._size-1;
                aIns[iins]._size = instr_size;
            }
            else {
                *(char *)curr_code_ptr = 0x67;
                curr_code_ptr += 1;
            }
        }
      #endif

      if(((strstr(aFile._file_name, "h264ref")) && aIns[iins]._op==BT_Iadd && aBb[aIns[iins]._ibb]._entry_addr==0x80a2e92) && \
            aIns[iins]._operand[opr_index].index && aIns[iins]._operand[opr_index].scale) {
            *(char *)curr_code_ptr = 0x67;
            curr_code_ptr += 1;
        }

     /**ebp based sib (ebp, exx, 4)
     #ifndef _NO_STACK_SWITCH
        if(aIns[iins]._operand[opr_index].base==aFun[ifun]._rem_base && aFun[ifun]._rem_base!=BT_R_ESP && aIns[iins]._operand[opr_index].index) { 
            prefix_index = 0;
            if(p_instr_code[prefix_index] == 0x66 || p_instr_code[prefix_index] == (char)0xf2 || p_instr_code[prefix_index] == (char)0xf3)
                prefix_index++;
            
            if(p_instr_code[prefix_index] == 0x0f)
                prefix_index++;

            prefix_index += 1;
            p_modrm = (struct modrm *)(p_instr_code+prefix_index);
            prefix_index += 2;
            if(p_modrm->mod == 0) {
                p_modrm->mod = 2;
                for(i=aIns[iins]._size-1; i>=prefix_index; i--)
                    p_instr_code[i+4] = p_instr_code[i];
                *(int *)(p_instr_code+prefix_index) = alias_mem_offset;
                instr_size = aIns[iins]._size+4;
                aIns[iins]._size = instr_size;
            }
            else if(p_modrm->mod == 1) {
                p_modrm->mod = 2;
                for(i=aIns[iins]._size-1; i>=prefix_index+1; i--)
                    p_instr_code[i+4] = p_instr_code[i];
                *(int *)(p_instr_code+prefix_index) = (signed char)p_instr_code[prefix_index] + alias_mem_offset;
                instr_size = aIns[iins]._size+3;
                aIns[iins]._size = instr_size;
            }
            else {
                *(int *)(p_instr_code+prefix_index) += alias_mem_offset;
            }
        }
      #endif*/
    }

    prefix_index = 0;
    if(p_instr_code[prefix_index]==(char)0xf2 || p_instr_code[prefix_index]==(char)0xf3) {
        *(char *)curr_code_ptr = p_instr_code[prefix_index];
        curr_code_ptr += 1;

        prefix_index++;
    }
    
    if(p_instr_code[prefix_index]==0x66) {
        *(char *)curr_code_ptr = p_instr_code[prefix_index];
        curr_code_ptr += 1;

        prefix_index++;
    }

    if(p_instr_code[prefix_index] == 0x0f) {
        *(char *)curr_code_ptr = 0x0f;
        curr_code_ptr += 1;

        prefix_index ++;
    }

    if(prefix_index) {
        p_instr_code += prefix_index;
        instr_size = aIns[iins]._size-prefix_index;
        aIns[iins]._size = instr_size;
    }
    
    p_code_cache = (char *)curr_code_ptr;

    index_new = 0;
    index_old = 0;

    switch(aIns[iins]._op)
    {
        case BT_Imov:
        {
            if((p_instr_code[0]&0xf0)==0xa0) {
                if(p_instr_code[0] == (char)0xa1)
                    p_code_cache[0] = 0x8b;
                else if(p_instr_code[0] == (char)0xa3)
                    p_code_cache[0] = 0x89;
                else if(p_instr_code[0] == (char)0xa0)
                    p_code_cache[0] = 0x8a;
                else if(p_instr_code[0] == (char)0xa2)
                    p_code_cache[0] = 0x88;

                p_code_cache[1] = 0x04;
                p_code_cache[2] = 0x25;

                *(int *)(p_code_cache+3) = *(int *)(p_instr_code+1);

                curr_code_ptr += 7;
            }
            else if((p_instr_code[0]&0xfc)==0x88 && (p_instr_code[1]&0x0c0)==0 && (p_instr_code[1]&0x07)==0x5) //mov mem reg or reg mem
            {
                p_code_cache[0] = p_instr_code[0];
                p_code_cache[1] = (p_instr_code[1]&0xf8)|0x4;
                p_code_cache[2] = 0x25;
                                    
                *(int *)(p_code_cache+3) = *(int *)(p_instr_code+2);
        
                curr_code_ptr += 7;
            }
            else if((p_instr_code[0]&0xfe)==0xc6 && (p_instr_code[1]&0x0c0)==0 && (p_instr_code[1]&0x07)==0x5) //mov imm mem 
            {
                p_code_cache[0] = p_instr_code[0];
                p_code_cache[1] = (p_instr_code[1]&0xf8)|0x4;
                p_code_cache[2] = 0x25;

                *(int *)(p_code_cache+3) = *(int *)(p_instr_code+2);

                for(i=6; i<aIns[iins]._size; i++)
                    p_code_cache[i+1] = p_instr_code[i];

                curr_code_ptr = curr_code_ptr + i+1;
            }
            else {
                for(i=0; i<aIns[iins]._size; i++)
                    p_code_cache[i] = p_instr_code[i];
                                    
                curr_code_ptr = curr_code_ptr + aIns[iins]._size;
            }
        }
        break;
        
        case BT_Idec:
        case BT_Iinc:
        {
            if((opr_index != aIns[iins]._opndnum) && (p_instr_code[1]&0x0c0)==0 && (p_instr_code[1]&0x07)==0x5) {
                p_code_cache[0] = p_instr_code[0];
                p_code_cache[1] = (p_instr_code[1]&0xf8)|0x4;
                p_code_cache[2] = 0x25;
                                    
                *(int *)(p_code_cache+3) = *(int *)(p_instr_code+2);
        
                curr_code_ptr += 7;
            }
            else if((p_instr_code[0]&0xf0)==(char)0x40 && aIns[iins]._size==1) {
                p_code_cache[0] = 0xff;
                p_code_cache[1] = 0xc0 | (p_instr_code[0]&0x0f);

                curr_code_ptr += 2;
            }
            else {
                for(i=0; i<aIns[iins]._size; i++)
                    p_code_cache[i] = p_instr_code[i];
                                    
                curr_code_ptr = curr_code_ptr + aIns[iins]._size;
            }
        }
        break;

        case BT_Ipush:
        {
            p_code_cache[0] = 0x8d;
            p_code_cache[1] = 0x64;
            p_code_cache[2] = 0x24;
            p_code_cache[3] = 0xfc;
            
            if(p_instr_code[0]==0x6a) {
                p_code_cache[4] = 0xc7;
                p_code_cache[5] = 0x4;
                p_code_cache[6] = 0x24;
                *(int *)(p_code_cache+7) = (signed char)p_instr_code[1];

                curr_code_ptr += 11;
            }
            else if(p_instr_code[0]==0x68) {
                p_code_cache[4] = 0xc7;
                p_code_cache[5] = 0x4;
                p_code_cache[6] = 0x24;
                *(int *)(p_code_cache+7) = *(int *)(p_instr_code+1);

                curr_code_ptr += 11;
            }
            else if((p_instr_code[0]&0x0f8)==0x50) {
                p_code_cache[4] = 0x89;
                p_code_cache[5] = 0x4;
                p_code_cache[5] = p_code_cache[5] | (p_instr_code[0]<<3);
                p_code_cache[6] = 0x24;

                curr_code_ptr += 7;
            }
            else if((p_instr_code[1]&0x0f8)==(char)0xf0) {
                p_code_cache[4] = 0x89;
                p_code_cache[5] = 0x4;
                p_code_cache[5] = p_code_cache[5] | (p_instr_code[1]<<3);
                p_code_cache[6] = 0x24;

                curr_code_ptr += 7;
            }
            else {
                ERROR(("Instruction push ##(%esp) exists!\n"));
            }
        }
        break;

        case BT_Ipop:
        {
            if((p_instr_code[0]&0x0f8)==0x58) {
                p_code_cache[0] = 0x8b;
                p_code_cache[1] = 0x04;
                p_code_cache[1] = p_code_cache[1] | ((p_instr_code[0]&0x3)<<3);
                p_code_cache[2] = 0x24;

                p_code_cache[3] = 0x8d;
                p_code_cache[4] = 0x64;
                p_code_cache[5] = 0x24;
                p_code_cache[6] = 0x4;

                curr_code_ptr += 7;
            }
            else if((p_instr_code[1]&0x0f8)==(char)0xc0) {
                p_code_cache[0] = 0x8b;
                p_code_cache[1] = 0x04;
                p_code_cache[1] = p_code_cache[1] | ((p_instr_code[1]&0x3)<<3);
                p_code_cache[2] = 0x24;

                p_code_cache[3] = 0x8d;
                p_code_cache[4] = 0x64;
                p_code_cache[5] = 0x24;
                p_code_cache[6] = 0x4;

                curr_code_ptr += 7;
            }
            else {
                ERROR(("Instruction pop ##(%esp) exists!\n"));
            }
        }
        break;

        default:
        {
            if((opr_index != aIns[iins]._opndnum) && (p_instr_code[1]&0x0c0)==0 && (p_instr_code[1]&0x07)==0x5) {
                p_code_cache[index_new++] = p_instr_code[index_old++];
                if(aIns[iins]._op>=BT_Ipshufb && aIns[iins]._op<BT_Iinvalid)
                    p_code_cache[index_new++] = p_instr_code[index_old++];
                p_code_cache[index_new++] = (p_instr_code[index_old++]&0x0f8)|0x4;
                p_code_cache[index_new++] = 0x25;
                                    
                *(int *)(p_code_cache+index_new) = *(int *)(p_instr_code+index_old);
                index_new += 4;
                index_old += 4;

                while(index_old<aIns[iins]._size)
                    p_code_cache[index_new++] = p_instr_code[index_old++];
        
                curr_code_ptr += index_new;
            }
            else {
                for(i=0; i<aIns[iins]._size; i++)
                    p_code_cache[i] = p_instr_code[i];
                                    
                curr_code_ptr += aIns[iins]._size;
            }
        }
    }

  #ifndef _NO_STACK_SWITCH
    if(adjust_esp) {
        *(UINT16 *)curr_code_ptr = 0xa48d;
        curr_code_ptr += 2;
        *(UINT8 *)curr_code_ptr = 0x24;
        curr_code_ptr += 1;
        *(INT32 *)curr_code_ptr = alias_mem_offset;
        curr_code_ptr += 4;
    }

    if(adjust_ebp) {
        *(UINT16 *)curr_code_ptr = 0xad8d;
        curr_code_ptr += 2;
        *(INT32 *)curr_code_ptr = alias_mem_offset;
        curr_code_ptr += 4;

        adjust_ebp = FALSE;
    }
  #endif

    aIns[iins]._size += prefix_index;
}

void DupIA32Code(INSINDEX iins) {
    char *p_code_cache;
    int i;
    BOOL adjust_esp = FALSE, adjust_ebp = FALSE;
    
    aIns[iins]._opt_addr = (ADDR32)curr_code_ptr;

    if((aIns[iins]._use&(BT_R_ESP-BT_R_EAX)) && (aIns[iins]._def&(BT_R_ESP-BT_R_EAX))==0) { 
        for(i=aIns[iins]._dest_opnd_num; i<aIns[iins]._opndnum; i++) {
            if(aIns[iins]._operand[i].type==BT_OP_REG && aIns[iins]._operand[i].base==BT_R_ESP) {
                if(aFun[ifun]._rem_base==BT_R_EBP && (*(UINT16 *)(ADDR)aIns[iins]._addr==0x0e589))
                    break;

                OUTPUT(("WARNING: Instruction OPCODE esp, REG exists. 0x%lx\n", aIns[iins]._addr));
                *(UINT16 *)curr_code_ptr = 0xa48d;
                curr_code_ptr += 2;
                *(UINT8 *)curr_code_ptr = 0x24;
                curr_code_ptr += 1;
                *(INT32 *)curr_code_ptr = -alias_mem_offset;
                curr_code_ptr += 4;
                adjust_esp = TRUE;
                break;
            }
        }
    }

    if(aFun[ifun]._rem_base==BT_R_EBP && (aIns[iins]._use&(BT_R_EBP-BT_R_EAX)) && (aIns[iins]._def&(BT_R_EBP-BT_R_EAX))==0) {
        for(i=aIns[iins]._dest_opnd_num; i<aIns[iins]._opndnum; i++) {
            if(aIns[iins]._operand[i].type==BT_OP_REG && aIns[iins]._operand[i].base==BT_R_EBP) {
                OUTPUT(("WARNING: Instruction OPCODE ebp, REG exists. 0x%lx\n", aIns[iins]._addr));
                *(UINT16 *)curr_code_ptr = 0xad8d;
                curr_code_ptr += 2;
                *(INT32 *)curr_code_ptr = -alias_mem_offset;
                curr_code_ptr += 4;
                adjust_ebp = TRUE;
                break;
            }
        }
    }

    p_code_cache = (char *)curr_code_ptr;
    for(i=0; i<aIns[iins]._size; i++)
        p_code_cache[i] = aIns[iins]._binary[i];
    curr_code_ptr = curr_code_ptr + aIns[iins]._size;

    if(adjust_esp) {
        *(UINT16 *)curr_code_ptr = 0xa48d;
        curr_code_ptr += 2;
        *(UINT8 *)curr_code_ptr = 0x24;
        curr_code_ptr += 1;
        *(INT32 *)curr_code_ptr = alias_mem_offset;
        curr_code_ptr += 4;

        adjust_esp = FALSE;
    }

    if(adjust_ebp) {
        *(UINT16 *)curr_code_ptr = 0xad8d;
        curr_code_ptr += 2;
        *(INT32 *)curr_code_ptr = alias_mem_offset;
        curr_code_ptr += 4;

        adjust_ebp = FALSE;
    }
}

