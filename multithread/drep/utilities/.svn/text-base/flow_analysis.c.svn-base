#include <stdio.h>
#include <string.h>
#include "mem_manage.h"
#include "optimization.h"
#include "utility.h"

int dfn_pre = 0;
INNLPINDEX gInnLoop;
BBINDEX iroot_bb;
STACK *s;
ARRAY *rPostorder;

void InnerLoop(BBINDEX ibb) {
    BBINDEX ybb, zbb;
    BBLKINDEX ibblk;
    INNLPINDEX iInnLoop;

    dfn_pre += 1;
    aBb[ibb]._dfn_pre = dfn_pre;
    aBb[ibb]._cfg_llink = dfn_pre;

    StackPush(s, ibb);

    ibblk = aBb[ibb]._succ_bb;
    while(ibblk) {
        ybb = aBblk[ibblk]._ibb;

        if(ybb==iroot_bb || !ArraySExist(t_array, ybb)) {
            ibblk = aBblk[ibblk]._next;
            continue;
        }

        if(aBb[ybb]._dfn_pre == 0) {
            InnerLoop(ybb);
            if(aBb[ibb]._cfg_llink > aBb[ybb]._cfg_llink)
                aBb[ibb]._cfg_llink = aBb[ybb]._cfg_llink;
        }
        else if(aBb[ibb]._dfn_pre >= aBb[ybb]._dfn_pre) {
            if(StackExist(s, ybb) && aBb[ibb]._cfg_llink>aBb[ybb]._dfn_pre)
                aBb[ibb]._cfg_llink = aBb[ybb]._dfn_pre;
        }
        
        ibblk = aBblk[ibblk]._next;
    }

    if(aBb[ibb]._cfg_llink == aBb[ibb]._dfn_pre) {
        iInnLoop == INVALID;

        ibblk = aBb[ibb]._succ_bb;
        ibblk = aBblk[ibblk]._next;
        if(s->StackBase[s->NumOfElem-1]!=ibb || (ibblk && aBblk[ibblk]._ibb==ibb)) {
            if(gInnLoop == INVALID) {
                iInnLoop = InnLoopNew();
                aInnLoop[iInnLoop]._entry = ibb;
                gInnLoop = iInnLoop;
            }
            else {
                iInnLoop = gInnLoop;
                while(aInnLoop[iInnLoop]._next)
                    iInnLoop = aInnLoop[iInnLoop]._next;
                aInnLoop[iInnLoop]._next = InnLoopNew();
                iInnLoop = aInnLoop[iInnLoop]._next;
                aInnLoop[iInnLoop]._entry = ibb;
            }
        }

        while(s->NumOfElem) {
            zbb = s->StackBase[s->NumOfElem-1];
            if(aBb[zbb]._dfn_pre < aBb[ibb]._dfn_pre)
                return;
            zbb = StackPop(s);
            if(iInnLoop) {
                ArrayAdd(aInnLoop[iInnLoop]._member, zbb);
                aInnLoop[iInnLoop]._instr_num += aBb[zbb]._ins_num;
            }
        }
    }
}

void FindInnerLoop() {
    OUTLPINDEX iOutLoop;
    INNLPINDEX iInnLoop;
    BBINDEX ibb;
    int i;
    STACK *t_stack = StackNew();

    iOutLoop = INVALID + 1;
    while(iOutLoop < nOutLp) {
        t_array = aOutLoop[iOutLoop]._member;

        if(t_array->NumOfElem > 1) {
            ArraySort(t_array);

            for(i=0; i<t_array->NumOfElem; i++) {
                ibb = t_array->ArrayBase[i];
                aBb[ibb]._dfn_pre = 0;
                aBb[ibb]._cfg_llink = 0;
            }

            dfn_pre = 0;
            s->NumOfElem = 0;
            //ibb = t_array->ArrayBase[0];
            iroot_bb = aOutLoop[iOutLoop]._entry;
            //if(ibb == iroot_bb)
                //ibb = t_array->ArrayBase[1];

            gInnLoop = aOutLoop[iOutLoop]._inner;
            InnerLoop(iroot_bb);
            aOutLoop[iOutLoop]._inner = gInnLoop;

            if(gInnLoop)
                StackPush(t_stack, gInnLoop);
            while(t_stack->NumOfElem) {
                iInnLoop = StackPop(t_stack);
                t_array = aInnLoop[iInnLoop]._member;
                ArraySort(t_array);

                for(i=0; i<t_array->NumOfElem; i++) {
                    ibb = t_array->ArrayBase[i];
                    aBb[ibb]._dfn_pre = 0;
                    aBb[ibb]._cfg_llink = 0;
                }

                dfn_pre = 0;
                s->NumOfElem = 0;
                if(t_array->NumOfElem > 1) {
                    //ibb = t_array->ArrayBase[0];
                    //if(ibb == aInnLoop[iInnLoop]._entry)
                        //ibb = t_array->ArrayBase[1];

                    iroot_bb = aInnLoop[iInnLoop]._entry;
                    gInnLoop = aInnLoop[iInnLoop]._inner;
                    InnerLoop(iroot_bb);
                    aInnLoop[iInnLoop]._inner = gInnLoop;
                }

                if(aInnLoop[iInnLoop]._next)
                    StackPush(t_stack, aInnLoop[iInnLoop]._next);

                if(aInnLoop[iInnLoop]._inner)
                    StackPush(t_stack, aInnLoop[iInnLoop]._inner);
            }
        }
        iOutLoop ++;
    }

    StackFree(t_stack);
}

void FindOuterLoop(BBINDEX ibb) {
    BBINDEX ybb, zbb;
    BBLKINDEX ibblk;
    OUTLPINDEX  iOutLoop;
    
    dfn_pre += 1;
    aBb[ibb]._dfn_pre = dfn_pre;
    aBb[ibb]._cfg_llink = dfn_pre;

    StackPush(s, ibb);

    ibblk = aBb[ibb]._succ_bb;
    while(ibblk) {
        ybb = aBblk[ibblk]._ibb;

        if(aBb[ybb]._dfn_pre == 0) {
            FindOuterLoop(ybb);
            if(aBb[ibb]._cfg_llink > aBb[ybb]._cfg_llink)
                aBb[ibb]._cfg_llink = aBb[ybb]._cfg_llink;
        }
        else if(aBb[ibb]._dfn_pre >= aBb[ybb]._dfn_pre) {
            if(StackExist(s, ybb) && aBb[ibb]._cfg_llink>aBb[ybb]._dfn_pre)
                aBb[ibb]._cfg_llink = aBb[ybb]._dfn_pre;
        }
        
        ibblk = aBblk[ibblk]._next;
    }

    ArrayAdd(rPostorder, ibb);
    
    if(aBb[ibb]._cfg_llink == aBb[ibb]._dfn_pre) {
        iOutLoop == INVALID;

        ibblk = aBb[ibb]._succ_bb;
        ibblk = aBblk[ibblk]._next;
        if(s->StackBase[s->NumOfElem-1]!=ibb || (ibblk && aBblk[ibblk]._ibb==ibb)) {
            iOutLoop = OutLoopNew();
            aOutLoop[iOutLoop]._entry = ibb;
        }
        
        while(s->NumOfElem) {
            zbb = s->StackBase[s->NumOfElem-1];
            if(aBb[zbb]._dfn_pre < aBb[ibb]._dfn_pre)
                return;
            zbb = StackPop(s);
            if(iOutLoop) {
                ArrayAdd(aOutLoop[iOutLoop]._member, zbb);
                aOutLoop[iOutLoop]._instr_num += aBb[zbb]._ins_num;
            }
        }
    }
}

void FindIdomBb() {
    OUTLPINDEX iOutLoop;
    BBINDEX ibb, pbb, new_idom, finger1, finger2;
    BBLKINDEX ibblk;
    BOOL changed;
    int i;

    changed = TRUE;
    ASSERT(aFun[ifun]._ibb_entry==rPostorder->ArrayBase[rPostorder->NumOfElem-1], ("The reverse postorder array is incorrect!\n"))
    aBb[aFun[ifun]._ibb_entry]._idom_bb = aFun[ifun]._ibb_entry;
    while(changed) {
        changed = FALSE;
        for(i=rPostorder->NumOfElem-2; i>=0; i--) {
            ibb = rPostorder->ArrayBase[i];
            ibblk = aBb[ibb]._pred_bb;

            while(ibblk) {
                new_idom = aBblk[ibblk]._ibb;
                ibblk = aBblk[ibblk]._next;
                if(aBb[new_idom]._idom_bb!=INVALID)
                    break;
            }

            while(ibblk) {
                pbb = aBblk[ibblk]._ibb;
                if(aBb[pbb]._idom_bb != INVALID) {
                    finger1 = pbb;
                    finger2 = new_idom;

                    while(finger1 != finger2) {
                        while(ArrayElemIndex(rPostorder, finger1) < ArrayElemIndex(rPostorder, finger2))
                            finger1 = aBb[finger1]._idom_bb;
                        while(ArrayElemIndex(rPostorder, finger2) < ArrayElemIndex(rPostorder, finger1))
                            finger2 = aBb[finger2]._idom_bb;
                    }

                    new_idom = finger1;
                }
                ibblk = aBblk[ibblk]._next;
            }

            if(aBb[ibb]._idom_bb != new_idom) {
                aBb[ibb]._idom_bb = new_idom;
                changed = TRUE;
            }
        }
    }
}

void ControlFlowAnalysis() {
    BBINDEX ibb, jbb;
    BBLKINDEX ibblk;
    OUTLPINDEX tOutLoop, tInnLoop;
    int i;

    ASSERT(aFun[ifun]._ibb_head==aFun[ifun]._ibb_entry,("The head of bbs is not the same as function entry!\n"));

    s = StackNew();
    rPostorder = ArrayNew();
    ibb = aFun[ifun]._ibb_head;
    while(ibb) {
        if(aBb[ibb]._dfn_pre == 0)
            FindOuterLoop(ibb);
        
        ibb = aBb[ibb]._next;
    }

    //FindIdomBb();
    FindInnerLoop();

    //code to check reducible and identify the exit
    tOutLoop = INVALID + 1;
    while(tOutLoop < nOutLp) {
        t_array = aOutLoop[tOutLoop]._member;

        for(i=0; i<t_array->NumOfElem; i++) {
            ibb = t_array->ArrayBase[i];
            if(aBb[ibb]._last_instr_type>T_ENTRY && aBb[ibb]._last_instr_type<T_BRANCH)
                aOutLoop[tOutLoop]._call_num ++;

            ibblk = aBb[ibb]._pred_bb;
            while(ibblk) {
                jbb = aBblk[ibblk]._ibb;
                if(!ArraySExist(t_array, jbb) && aOutLoop[tOutLoop]._entry != ibb && aBb[jbb]._pred_bb_num!=0) {
                    //ArrayAdd(aOutLoop[tOutLoop]._entry, ibb);
                    if((aOutLoop[tOutLoop]._flag & LOOP_UNREDUCIBLE) == 0) {
                        aOutLoop[tOutLoop]._flag |= LOOP_UNREDUCIBLE;
                        WARNING(("Loop %d is not reducible. Edge 0x%lx --> 0x%lx\n", tOutLoop, aBb[jbb]._entry_addr, aBb[ibb]._entry_addr))
                    }
                }
                
                ibblk = aBblk[ibblk]._next;
            }

            if(aBb[ibb]._last_instr_type==T_JUMPIN) {
                aOutLoop[tOutLoop]._flag |= LOOP_CONTAIN_JUMPIN;
                break;
            }
            
            ibblk = aBb[ibb]._succ_bb;
            while(ibblk) {
                jbb = aBblk[ibblk]._ibb;
                if(!ArraySExist(t_array, jbb))
                    ArrayAdd(aOutLoop[tOutLoop]._exit, ibb);

                ibblk= aBblk[ibblk]._next;
            }
        }
        
        tOutLoop ++;
    }

    tInnLoop = INVALID + 1;
    while(tInnLoop < nInnLp) {
        t_array = aInnLoop[tInnLoop]._member;

        for(i=0; i<t_array->NumOfElem; i++) {
            ibb = t_array->ArrayBase[i];
            if(aBb[ibb]._last_instr_type>T_ENTRY && aBb[ibb]._last_instr_type<T_BRANCH)
                aInnLoop[tInnLoop]._call_num ++;

            ibblk = aBb[ibb]._pred_bb;
            while(ibblk) {
                jbb = aBblk[ibblk]._ibb;
                if(!ArraySExist(t_array, jbb) && aInnLoop[tInnLoop]._entry != ibb && aBb[jbb]._pred_bb_num!=0) {
                    //ArrayAdd(aInnLoop[tInnLoop]._entry, ibb);
                    if((aInnLoop[tInnLoop]._flag & LOOP_UNREDUCIBLE) == 0) {
                        aInnLoop[tInnLoop]._flag |= LOOP_UNREDUCIBLE;
                        WARNING(("Loop %d is not reducible. Edge 0x%lx --> 0x%lx\n", tInnLoop, aBb[jbb]._entry_addr, aBb[ibb]._entry_addr))
                    }
                }

                ibblk = aBblk[ibblk]._next;
            }

            if(aBb[ibb]._last_instr_type==T_JUMPIN) {
                aInnLoop[tInnLoop]._flag |= LOOP_CONTAIN_JUMPIN;
                break;
            }

            ibblk = aBb[ibb]._succ_bb;
            while(ibblk) {
                jbb = aBblk[ibblk]._ibb;
                if(!ArraySExist(t_array, jbb))
                    ArrayAdd(aInnLoop[tInnLoop]._exit, ibb);

                ibblk= aBblk[ibblk]._next;
            }
        }

        tInnLoop ++;
    }

    StackFree(s);
    ArrayFree(rPostorder);
}

void RemInBb(BBINDEX ibb, OUTLPINDEX iOutLoop, int weight) {
    INSINDEX iins, tins;
    REMINDEX irem, trem;
    RMINSINDEX irem_ins;
    REGIONINDEX iregion;
    OPERAND *p_operand, *t_operand;
    OPCODE t_op;
    int i, j, t_ins_count;
    REGISTER_TYPE d_reg;

    iins = aBb[ibb]._ins_first;
    while(iins <= aBb[ibb]._ins_last) {
        for(i=0; i<aIns[iins]._opndnum; i++) {
            p_operand = &(aIns[iins]._operand[i]);
            t_op = aIns[iins]._op;
            if(p_operand->type == BT_OP_MEM && t_op!=BT_Ilea) {
                if(p_operand->index==BT_NONE && p_operand->base==aFun[ifun]._rem_base) {
                    irem_ins = RemInsNew();
                    aRemIns[irem_ins]._weight = weight;
    
                    if(t_op==BT_Imov) {
                        if(i==0) {
                            if(aIns[iins]._binary[0] == (char)0xc7)
                                aRemIns[irem_ins]._rem_type = LOAR_DEST;
                            else
                                aRemIns[irem_ins]._rem_type = TRAN_DEST;
                        }
                        else
                            aRemIns[irem_ins]._rem_type = TRAN_SRC;
                    }
                    else if(t_op>=BT_Iaddpd && t_op<BT_Iemms) {
                        ASSERT(i<2, ("The operand no is greater than 1.\n"));
                        t_operand = &(aIns[iins]._operand[1-i]);

                        if((t_op>=BT_Imovq&&t_op<=BT_Imovsd_sse) || (t_op==BT_Imovd) || (t_op==BT_Imovss)) {
                            if(i==0)
                                aRemIns[irem_ins]._rem_type = TRAN_XMM_DEST;
                            else
                                aRemIns[irem_ins]._rem_type = TRAN_XMM_SRC;
                        }
                        else if(t_operand->type==BT_OP_XMMREG) {
                            if(aIns[iins]._dest_opnd_num > i)
                                aRemIns[irem_ins]._rem_type = XMM_DEST;
                            else
                                aRemIns[irem_ins]._rem_type = XMM_SRC;
                        }
                        else
                            aRemIns[irem_ins]._rem_type = MMX_OPER;
                        
                        if(t_op<=BT_Ixorps)
                            p_operand->size = 128;
                        else if(t_op<=BT_Imovsd_sse)
                            p_operand->size = 64;
                        else if(t_op<=BT_Icvttss2si)
                            p_operand->size = 32;
                        else
                            p_operand->size = 0;
                    }
                    else if(t_op>BT_If2xm1 && t_op<BT_Ifyl2xp1)
                        aRemIns[irem_ins]._rem_type = FR_OPER;
                    else {
                        if(aIns[iins]._dest_opnd_num > i)
                            aRemIns[irem_ins]._rem_type = LOAR_DEST;
                        else
                            aRemIns[irem_ins]._rem_type = LOAR_SRC;

                        if(t_op==BT_Icvtsi2ss && t_op==BT_Icvtsi2sd)
                            p_operand->size = 32;
                    }

                    //assign weight to rem
                    if((aRemIns[irem_ins]._rem_type==TRAN_SRC || aRemIns[irem_ins]._rem_type==TRAN_XMM_SRC || \
                        aRemIns[irem_ins]._rem_type==LOAR_SRC || aRemIns[irem_ins]._rem_type==XMM_SRC) &&\
                        (i<=1 && aIns[iins]._opndnum>=2)) {
                        t_operand = &(aIns[iins]._operand[1-i]);
                        ASSERT(t_operand->type==BT_OP_REG||t_operand->type==BT_OP_XMMREG||t_operand->type==BT_OP_SIMM, ("The dest operand is not reg.\n"));
                        if(t_operand->type!=BT_OP_SIMM)
                            d_reg = t_operand->base;
                        else
                            d_reg = BT_R_RIP;

                        t_ins_count = 0;
                        tins = iins + 1;
                        while(tins<=aBb[ibb]._ins_last && t_ins_count<4) {
                            if(aRemIns[irem_ins]._rem_type==TRAN_SRC || aRemIns[irem_ins]._rem_type==TRAN_XMM_SRC) {
                                for(j=aIns[tins]._opndnum-1; j>=aIns[tins]._src_opnd_start; j--) {
                                    t_operand = aIns[tins]._operand+j;
                                    if(t_operand->base==d_reg || t_operand->index==d_reg) {
                                        aRemIns[irem_ins]._rem_type = (REM_TYPE)(aRemIns[irem_ins]._rem_type+t_ins_count+4);

                                        if((aIns[tins]._op!=BT_Ilea && t_operand->type==BT_OP_MEM) || IS_LONGLATENCY_INS(aIns[tins]._op))
                                            aRemIns[irem_ins]._rem_type = (REM_TYPE)(aRemIns[irem_ins]._rem_type - 1);
                                        else if(IS_TRANSFER_INS(aIns[tins]._op))
                                            aRemIns[irem_ins]._rem_type = (REM_TYPE)(aRemIns[irem_ins]._rem_type + 1);

                                        break;
                                    }
                                }

                                if(j>=aIns[tins]._src_opnd_start) {
                                    t_operand = aIns[tins]._operand;
                                    if(t_operand->type==BT_OP_REG || t_operand->type==BT_OP_XMMREG) {
                                        d_reg = t_operand->base;
                                        tins ++;
                                        if(tins<=aBb[ibb]._ins_last) {
                                            for(j=aIns[tins]._src_opnd_start; j<aIns[tins]._opndnum; j++) {
                                                t_operand = aIns[tins]._operand+j;
                                                if((t_operand->base==d_reg || t_operand->index==d_reg) && aIns[tins]._op!=BT_Imov) {
                                                    aRemIns[irem_ins]._rem_type = (REM_TYPE)(aRemIns[irem_ins]._rem_type - 2);
                                                    break;
                                                }
                                            }

                                            if(j==aIns[tins]._opndnum) {
                                                tins ++;
                                                if(tins<=aBb[ibb]._ins_last) {
                                                    for(j=aIns[tins]._src_opnd_start; j<aIns[tins]._opndnum; j++) {
                                                        t_operand = aIns[tins]._operand+j;
                                                        if((t_operand->base==d_reg || t_operand->index==d_reg) && aIns[tins]._op!=BT_Imov) {
                                                            aRemIns[irem_ins]._rem_type = (REM_TYPE)(aRemIns[irem_ins]._rem_type - 1);
                                                            break;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    
                                    break;
                                }
                            }
                            else if(aRemIns[irem_ins]._rem_type == LOAR_SRC) {
                                if(t_op==BT_Icmp) {
                                    if((aIns[tins]._op>=BT_Ija && aIns[tins]._op<=BT_Ijnle) ||\
                                        (aIns[tins]._op>=BT_Icmovae && aIns[tins]._op<=BT_Icmovnle)) {
                                        aRemIns[irem_ins]._rem_type = (REM_TYPE)(LOAR_SRC+t_ins_count+2);
                                        break;
                                    }
                                    else if(t_ins_count==3)
                                        aRemIns[irem_ins]._rem_type = LOAR_DEST;
                                }
                                else {
                                    for(j=aIns[tins]._opndnum-1; j>=aIns[tins]._src_opnd_start; j--) {
                                        t_operand = aIns[tins]._operand+j;
                                        if(t_operand->base==d_reg || t_operand->index==d_reg) {
                                            aRemIns[irem_ins]._rem_type = (REM_TYPE)(LOAR_SRC+t_ins_count+2);

                                            if((aIns[tins]._op!=BT_Ilea && t_operand->type==BT_OP_MEM) || IS_LONGLATENCY_INS(aIns[tins]._op))
                                                aRemIns[irem_ins]._rem_type = (REM_TYPE)(aRemIns[irem_ins]._rem_type - 1);
                                            else if(aIns[tins]._op==BT_Imov)
                                                aRemIns[irem_ins]._rem_type = (REM_TYPE)(aRemIns[irem_ins]._rem_type + 1);

                                            break;
                                        }
                                    }

                                    if(j<aIns[tins]._opndnum)
                                        break;
                                }
                            }
                            else {
                                for(j=aIns[tins]._opndnum-1; j>=aIns[tins]._src_opnd_start; j--) {
                                    t_operand = aIns[tins]._operand+j;
                                    if(t_operand->base==d_reg || t_operand->index==d_reg) {
                                        aRemIns[irem_ins]._rem_type = (REM_TYPE)(XMM_SRC+t_ins_count+2);

                                        if((aIns[tins]._op!=BT_Ilea && t_operand->type==BT_OP_MEM) || IS_LONGLATENCY_INS(aIns[tins]._op))
                                            aRemIns[irem_ins]._rem_type = (REM_TYPE)(aRemIns[irem_ins]._rem_type - 1);
                                        else if(IS_TRANSFER_INS(aIns[tins]._op))
                                            aRemIns[irem_ins]._rem_type = (REM_TYPE)(aRemIns[irem_ins]._rem_type + 1);

                                        break;
                                    }
                                }

                                if(j<aIns[tins]._opndnum)
                                    break;
                            }

                            tins ++ ;
                            t_ins_count ++;
                        }
                    }

                    aRemIns[irem_ins]._iins = iins;
                    aRemIns[irem_ins]._operand_no = i;

                    if((aOutLoop[iOutLoop]._flag&LOOP_OPT_REGION)==0)
                        irem = RemSearch(aOutLoop[iOutLoop]._rem_list, p_operand->lval.sdword+aFun[ifun]._push_num);
                    else {
                        iregion = aOutLoop[iOutLoop]._region;
                        while(iregion) {
                            if(ibb == aRegion[iregion]._ibb)
                                break;
                            iregion = aRegion[iregion]._next;
                        }
                        ASSERT(iregion!=INVALID, ("Cannot find region index.\n"));
                        irem = RemSearch(aRegion[iregion]._rem_list, p_operand->lval.sdword+aFun[ifun]._push_num);
                    }

                    if(irem) {
                        if(p_operand->size!=aRem[irem]._rem_size && aRem[irem]._rem_size!=0) {
                            int t_size;
                            if(p_operand->size > aRem[irem]._rem_size)
                                t_size = p_operand->size;
                            else
                                t_size = aRem[irem]._rem_size;

                            if((aOutLoop[iOutLoop]._flag&LOOP_OPT_REGION)==0)
                                trem = aOutLoop[iOutLoop]._rem_list;
                            else
                                trem = aRegion[iregion]._rem_list;
                            while(trem) {
                                if(aRem[trem]._offset>aRem[irem]._offset && aRem[trem]._offset<aRem[irem]._offset+t_size/8)
                                    aRem[trem]._rem_size = 0;
                                trem = aRem[trem]._next;
                            }

                            aRem[irem]._rem_size = 0;
                            WARNING(("Non-Identical rem size, offset: 0x%x  instr addr: 0x%lx.\n", aRem[irem]._offset,aIns[iins]._addr))
                        }
                        ArrayAdd(aRem[irem]._rem_instr, irem_ins);
                    }
                    else {
                        irem = RemNew();
                        aRem[irem]._offset = p_operand->lval.sdword+aFun[ifun]._push_num;
                        aRem[irem]._rem_size = p_operand->size;
                        ArrayAdd(aRem[irem]._rem_instr, irem_ins);

                        if((aOutLoop[iOutLoop]._flag&LOOP_OPT_REGION)==0) {
                            if(aOutLoop[iOutLoop]._rem_num == 0)
                                aOutLoop[iOutLoop]._rem_list = irem;
                            else {
                                aRem[irem]._next = aOutLoop[iOutLoop]._rem_list;
                                aOutLoop[iOutLoop]._rem_list = irem;
                            }

                            aOutLoop[iOutLoop]._rem_num ++;
                        }
                        else {
                            if(aRegion[iregion]._rem_num == 0)
                                aRegion[iregion]._rem_list = irem;
                            else {
                                aRem[irem]._next = aRegion[iregion]._rem_list;
                                aRegion[iregion]._rem_list = irem;
                            }

                            aRegion[iregion]._rem_num ++;
                        }
                    }
                }
            }
        }   

        if(aIns[iins]._op==BT_Ipush) {
            if(ibb!=aFun[ifun]._ibb_entry)
                aFun[ifun]._push_num -= 4;
            else if(aBb[ibb]._last_instr_type>T_ENTRY && aBb[ibb]._last_instr_type<T_BRANCH) {
                tins = iins + 1;
                while(tins+1 <= aBb[ibb]._ins_last) {
                    if(aIns[tins]._op!=BT_Ipush)
                        break;
                    tins += 1;
                }
                if(tins==aBb[ibb]._ins_last)
                    aFun[ifun]._push_num -= 4;
            }
        }
        else if(aBb[ibb]._last_instr_type!=T_RET) {
            if(IS_ADD_IMM_ESP(aIns[iins]._binary))
                aFun[ifun]._push_num += (int)(*(signed char *)(aIns[iins]._binary+2));
            else if(aIns[iins]._op==BT_Ipop)
                aFun[ifun]._push_num += 4;
        }
        else if(aIns[iins]._op==BT_Iret)
            aFun[ifun]._push_num = 0;

        ASSERT(aFun[ifun]._push_num<=0, ("The push offset is error.\n"))

        iins ++;
    }
}

void DataFlowAnalysis() {
        BBINDEX ibb;
        OUTLPINDEX iOutLoop;
        INNLPINDEX iInnLoop;
        REGIONINDEX iregion;
        int weight, ins_percent;
    
        ibb = aFun[ifun]._ibb_entry;
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
    
            if(iOutLoop < nOutLp) {
                if(aFun[ifun]._opt_target==FUNC)
                    iOutLoop = 1;
    
                if((aOutLoop[iOutLoop]._flag&LOOP_OPT_REGION)==0) {
                    weight = 1;
                    iInnLoop = aOutLoop[iOutLoop]._inner;
                    while(iInnLoop) {
                        if(ArrayExist(aInnLoop[iInnLoop]._member, ibb)) {
                            weight ++;
                            ins_percent = (aOutLoop[iOutLoop]._instr_num*2+aInnLoop[iInnLoop]._instr_num)/(aInnLoop[iInnLoop]._instr_num*2);
                            if(ins_percent < weight)
                                weight = ins_percent;
    
                            iInnLoop = aInnLoop[iInnLoop]._inner;
                        }
                        else
                            iInnLoop = aInnLoop[iInnLoop]._next;
                    }
                    weight = weight*(aBb[ibb]._samples*1000/(aFun[ifun]._samples+1));
    
                    if(aBb[ibb]._last_instr_type==T_CALL_RELATIVE)
                        GetCalleeArgNum(aIns[aBb[ibb]._ins_last]._operand[0].lval.sdword + aIns[aBb[ibb]._ins_last]._addr_next);
    
                    RemInBb(ibb, iOutLoop, weight);
                }
                else {
                    iregion = aOutLoop[iOutLoop]._region;
                    while(iregion) {
                        if(ibb == aRegion[iregion]._ibb)
                            break;
                        iregion = aRegion[iregion]._next;
                    }
                    if(iregion)
                        RemInBb(ibb, iOutLoop, 1);
                }
            }
            else if(aFun[ifun]._opt_target==FUNC) {
                iOutLoop = 1;
                if(aBb[ibb]._last_instr_type==T_CALL_RELATIVE)
                    GetCalleeArgNum(aIns[aBb[ibb]._ins_last]._operand[0].lval.sdword + aIns[aBb[ibb]._ins_last]._addr_next);
    
                RemInBb(ibb, iOutLoop, 0);
            }
            
            ibb = aBb[ibb]._next;
        }
    
        iOutLoop = 1;
        if(aFun[ifun]._opt_target==FUNC)
            RemListSort(iOutLoop);
        else {
            while(iOutLoop < nOutLp) {
                if((aOutLoop[iOutLoop]._flag&LOOP_OPT_REGION)==0)
                    RemListSort(iOutLoop);
                else
                    RemListSortRegion(iOutLoop);
                iOutLoop ++;
            }
        }
    }

