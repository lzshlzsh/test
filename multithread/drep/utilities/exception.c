#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define __USE_GNU
#include <sys/ucontext.h>
#include <signal.h>
#include <sys/mman.h>
#include "ir.h"
#include "mem_manage.h"
#include "assemble.h"

#define MAX_NEGINS_NUM  20
ADDR32 NegIndexInstr[MAX_NEGINS_NUM];
int iNegIndexIns = 0;

void Segv_Handler(int signum, siginfo_t *sip, void *uap) {
    struct ucontext *uc;
    OPERAND *p_operand;
    char *p_instr_code;
    struct modrm *p_modrm;
    ADDR pc, t_pc;
    int reg_map[16] = {REG_RAX, REG_RCX, REG_RDX, REG_RBX, REG_RSP, REG_RBP, REG_RSI, REG_RDI, \
        REG_R8, REG_R9, REG_R10, REG_R11, REG_R12, REG_R13, REG_R14, REG_R15};
    BBINDEX ibb, jbb;
    INSINDEX iins;
    BBLKINDEX ibblk;
    int greg, i, j;
    int t_size;
    BOOL change;

    uc = (struct ucontext *)uap;

    pc = uc->uc_mcontext.gregs[REG_RIP];
    p_instr_c->_addr = pc;
    t_pc = decode (p_instr_c, 64);
    p_instr_c->_next_instr_addr = t_pc;

    for(i=0; i<p_instr_c->_operandnumber; i++) {
        p_operand = p_instr_c->_operand+i;
        if(p_operand->type == BT_OP_MEM)
            break;
    }

    //fprintf(stderr, "sib incurred segmentation fault! 0x%lx\n", pc);
    if(p_operand->type==BT_OP_MEM && (uc->uc_mcontext.gregs[REG_CSGSFS]&0x0ff)==0x33) {
        greg = p_operand->index-BT_R_EAX;
        if(p_operand->index && greg>=0 && (INT32)(uc->uc_mcontext.gregs[reg_map[greg]])<0) {
            for(i=0; i<iNegIndexIns; i++) {
                if(NegIndexInstr[i]==(ADDR32)pc)
                    break;
            }
            if(i==iNegIndexIns) {
                NegIndexInstr[iNegIndexIns++] = (ADDR32)pc;
                ASSERT(iNegIndexIns<=MAX_NEGINS_NUM, ("The negative instr array is overflow.\n"));
                greg = reg_map[greg];
                uc->uc_mcontext.gregs[greg] = (INT64)(INT32)(uc->uc_mcontext.gregs[greg]);
            }
            else {
                change = TRUE;
            	for(i=iNegIndexIns-1; i>0&&change; --i)	{
            		change = FALSE;
            		for(j=0; j<i; ++j) {
            			if(NegIndexInstr[j] > NegIndexInstr[j+1])	{
            				t_pc = NegIndexInstr[j];
            				NegIndexInstr[j] = NegIndexInstr[j+1];
            				NegIndexInstr[j+1] = t_pc;
            				change = TRUE;
            			}
            		}
            	}
                curr_code_ptr = mm_pool._code_cache_info.p_cache_free;
                i = 0;
                while(i<iNegIndexIns) {
                    for(j=1; j<nFun; j++) {
                        if(NegIndexInstr[i]<aFun[j]._opt_code_addr)
                            break;
                    }
                    ibb = aFun[j-1]._ibb_head;
                    while(ibb) {
                        if(NegIndexInstr[i]>=aBb[ibb]._opt_code_addr && NegIndexInstr[i]<=aIns[aBb[ibb]._ins_last]._opt_addr)
                            break;
                        ibb = aBb[ibb]._next;
                    }
                    ASSERT(ibb!=INVALID, ("can not find the BB index of segv addr.\n"));
                    t_pc = aBb[ibb]._opt_code_addr;
                    iins = aBb[ibb]._ins_first;
                    while(iins && iins!=aBb[ibb]._ins_last) {
                        //t_pc = aIns[iins]._opt_addr;
                        aIns[iins]._opt_addr = (ADDR32)curr_code_ptr;
                        if(NegIndexInstr[i]==t_pc) {
                            if(pc==t_pc)
                                uc->uc_mcontext.gregs[REG_RIP] = curr_code_ptr;

                            if(*(UINT8 *)t_pc==(char)0xf2 || *(UINT8 *)t_pc==(char)0xf3) {
                                *(UINT8 *)curr_code_ptr = *(UINT8 *)t_pc;
                                curr_code_ptr ++;
                                t_pc ++;
                            }
                            *(UINT8 *)curr_code_ptr = 0x67;
                            curr_code_ptr ++;

                            while(t_pc < aIns[aIns[iins]._succ]._opt_addr)
                                *(UINT8 *)(curr_code_ptr++) = *(UINT8 *)(t_pc++);
                            i ++;
                        }
                        else {
                            while(t_pc < aIns[aIns[iins]._succ]._opt_addr)
                                *(UINT8 *)(curr_code_ptr++) = *(UINT8 *)(t_pc++);
                        }
                        
                        iins = aIns[iins]._succ;
                    }
                    ASSERT(iins!=INVALID, ("unexpected case.\n"));

                    aIns[iins]._opt_addr = curr_code_ptr;
                    if(aIns[iins]._op>BT_Iljmp && aIns[iins]._op<BT_Iloop) {
                        *(UINT16 *)curr_code_ptr = *(UINT16 *)t_pc;
                        *(INT32 *)(curr_code_ptr+2) = *(INT32 *)(t_pc+2) + (INT32)t_pc - (INT32)curr_code_ptr;
                        curr_code_ptr += 6;

                        *(UINT8 *)curr_code_ptr = 0xe9;
                        curr_code_ptr += 1;
                        *(UINT32 *)curr_code_ptr = t_pc + 6 - curr_code_ptr - 4;
                        curr_code_ptr += 4;
                    }
                    else if(aIns[iins]._op==BT_Icall || aIns[iins]._op==BT_Ijmp) {
                        *(UINT8 *)(curr_code_ptr) = *(UINT8 *)t_pc;
                        *(INT32 *)(curr_code_ptr+1) = *(INT32 *)(t_pc+1) + (INT32)t_pc - (INT32)curr_code_ptr;
                        curr_code_ptr += 5;

                        *(UINT8 *)curr_code_ptr = 0xe9;
                        curr_code_ptr += 1;
                        *(UINT32 *)curr_code_ptr = t_pc + 5 - curr_code_ptr - 4;
                        curr_code_ptr += 4;
                    }
                    else {
                        ADDR pc_end = t_pc+aIns[iins]._size;
                        while(t_pc < pc_end)
                            *(UINT8 *)(curr_code_ptr++) = *(UINT8 *)(t_pc++);

                        *(UINT8 *)curr_code_ptr = 0xe9;
                        curr_code_ptr += 1;
                        *(UINT32 *)curr_code_ptr = t_pc - curr_code_ptr - 4;
                        curr_code_ptr += 4;
                    }

                    *(UINT8 *)((ADDR)aBb[ibb]._opt_code_addr) = 0xe9;
                    *(UINT32 *)((ADDR)aBb[ibb]._opt_code_addr+1) = (ADDR32)mm_pool._code_cache_info.p_cache_free - aBb[ibb]._opt_code_addr - 5;

                    ibblk = aBb[ibb]._pred_bb;
                    while(ibblk) {
                        jbb = aBblk[ibblk]._ibb;
                        iins = aBb[jbb]._ins_last;
                        if((aIns[iins]._op>BT_Iljmp&&aIns[iins]._op<BT_Iloop) && *(INT32 *)((ADDR)aIns[iins]._opt_addr+2)+aIns[iins]._opt_addr+6==aBb[ibb]._opt_code_addr)
                            *(INT32 *)((ADDR)aIns[iins]._opt_addr+2) = (ADDR32)mm_pool._code_cache_info.p_cache_free - aIns[iins]._opt_addr - 6;
                        else if((aIns[iins]._op==BT_Icall||aIns[iins]._op==BT_Ijmp) && *(INT32 *)((ADDR)aIns[iins]._opt_addr+1)+aIns[iins]._opt_addr+5==aBb[ibb]._opt_code_addr)
                            *(INT32 *)((ADDR)aIns[iins]._opt_addr+1) = (ADDR32)mm_pool._code_cache_info.p_cache_free - aIns[iins]._opt_addr - 5;

                        ibblk = aBblk[ibblk]._next;
                    }
                }
                aBb[ibb]._opt_code_addr = mm_pool._code_cache_info.p_cache_free;
                CodeCacheAlloc(curr_code_ptr-mm_pool._code_cache_info.p_cache_free);

                iNegIndexIns = 0;
            }
        }
        else {
            fprintf(stderr, "detect potential alias ... 0x%x\n", pc);
            while(t_pc-pc<5) {
                p_instr_c->_addr = t_pc;
                t_pc = (ADDR)decode(p_instr_c, 64);
                p_instr_c->_next_instr_addr = t_pc;
            }
            curr_code_ptr = mm_pool._code_cache_info.p_cache_free;
            p_instr_code = (char *)pc;

            i = 0;
            if(p_instr_code[i]==(char)0xf2 || p_instr_code[i]==(char)0xf3 || p_instr_code[i]==0x66) {
                *(char *)curr_code_ptr = p_instr_code[i];
                curr_code_ptr += 1;
                i++;
            }
            
            if(p_instr_code[i]==0x41) {
                *(char *)curr_code_ptr = p_instr_code[i];
                curr_code_ptr += 1;
                i++;
            }

            if(p_instr_code[i] == 0x0f) {
                *(char *)curr_code_ptr = 0x0f;
                curr_code_ptr += 1;
                i ++;
            }

            *(char *)curr_code_ptr = p_instr_code[i];
            i ++;
            *(char *)(curr_code_ptr+1) = p_instr_code[i];
            i ++;
            j = 2;
            
            p_modrm = (struct modrm *)(curr_code_ptr+1);
            if(p_modrm->rm==4) {
                *(char *)(curr_code_ptr+j) = p_instr_code[i];
                i ++;
                j ++;
            }

            if(p_modrm->mod == 0) {
                p_modrm->mod = 2;
                *(int *)(curr_code_ptr+j) = alias_mem_offset;
                j += 4;
            }
            else if(p_modrm->mod == 1) {
                p_modrm->mod = 2;
                *(int *)(curr_code_ptr+j) = (signed char)p_instr_code[i] + alias_mem_offset;
                j += 4;
                i ++;
            }
            else {
                *(int *)(curr_code_ptr+j) = *(int *)(p_instr_code+i) + alias_mem_offset;
                j += 4;
                i += 4;
            }

            while(i < t_pc-pc) {
                *(char *)(curr_code_ptr+j) = p_instr_code[i];
                j ++;
                i ++;
            }

            curr_code_ptr += j;
            *(char *)curr_code_ptr = 0xe9;
            *(int *)(curr_code_ptr+1) = t_pc - curr_code_ptr - 5;
            curr_code_ptr += 5;

            *(char *)pc = 0xe9;
            *(int *)(pc+1) = mm_pool._code_cache_info.p_cache_free - pc - 5;
            
            CodeCacheAlloc(curr_code_ptr-mm_pool._code_cache_info.p_cache_free);
        }
    }
    else {
        fprintf(stderr, "segmentation fault\n");
        exit(-1);
    } 
}

void SignalInit() {
    struct sigaction sa_segv;
    
    sa_segv.sa_sigaction = Segv_Handler;
    sigemptyset (&sa_segv.sa_mask);
    sa_segv.sa_flags = SA_SIGINFO;
    
    if (sigaction (SIGSEGV, &sa_segv, NULL))
        ERROR(("The SIGSEGV signal error while sigaction!\n"));
}

