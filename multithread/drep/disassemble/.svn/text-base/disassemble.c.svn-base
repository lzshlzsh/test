#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ir.h"
#include "mem_manage.h"

INSTR_CUT *p_instr_c;

BBINDEX FormBlock (ADDR32 block_entry) {
    BBINDEX jbb = HashSearch(block_entry);
    if (jbb)
        return jbb;

    jbb = BbNew();
    aBb[jbb]._entry_addr = block_entry;

    HashInsert(jbb);

    return jbb;
}

void Disassemble_A_Block (BT_INFO *p_info) {
    INSINDEX jins;
    BBINDEX jbb = p_info->_current_bb;
    ADDR32 pc = aBb[jbb]._entry_addr;

    ASSERT(pc!=0, ("pc is NULL!\n"));

    //Disassemble a single instruction
    p_instr_c->_addr = pc;
    pc = (ADDR32)decode(p_instr_c, 32);
    p_instr_c->_next_instr_addr = pc;
    jins = InstrNew();
    BbAddInstr(jbb, jins);

  #ifdef _DUMP_INSTR
    //Instr_Dump_ATT(p_instr_c);
  #endif
    
    while(!(aIns[jins]._op>=BT_Ihlt&&aIns[jins]._op<=BT_Iretf) && (aIns[jins]._addr_next<aFun[ifun]._entry_addr+aFun[ifun]._func_size)) {
        p_instr_c->_addr = pc;
        pc = (ADDR32)decode(p_instr_c, 32);
        p_instr_c->_next_instr_addr = pc;
        jins = InstrNew();
        BbAddInstr(jbb, jins);
      #ifdef _DUMP_INSTR
        //Instr_Dump_ATT(p_instr_c);
      #endif
    }
    
    //Set _end_vaddr of p_block. This addr is the fallthrough addr of p_block.
    aBb[jbb]._end_addr = pc;
    /*fill the p_info */
    p_info->_next_ins_addr = pc;

    if (aIns[jins]._op >= BT_Ija && aIns[jins]._op <= BT_Iloopz) {
        p_info->_type = T_BRANCH;
        p_info->_target_addr = pc + aIns[jins]._operand[0].lval.sdword;
    }
    else {
        switch (aIns[jins]._op) {
            case BT_Icall:
                p_info->_type = T_CALL_RELATIVE;
                p_info->_target_addr = pc + aIns[jins]._operand[0].lval.sdword;
                break;
            case BT_Icallin:
                p_info->_type = T_CALLIN;
                break;
            case BT_Ilcall:
                p_info->_type = T_CALL_FAR;
                break;
            case BT_Ijmp:
                p_info->_type = T_JUMP_RELATIVE;
                p_info->_target_addr = pc + aIns[jins]._operand[0].lval.sdword;
                break;
            case BT_Ijmpin:
                p_info->_type = T_JUMPIN;
                break;
            case BT_Iljmp:
                p_info->_type = T_JUMP_FAR;
                break;
            case BT_Iret:
            case BT_Iiretw:
            case BT_Iiretd:
            case BT_Iiretq:
                p_info->_type = T_RET;
                break;
            case BT_Ihlt:
                p_info->_type = T_HALT;
                break;
            default:
                p_info->_type = T_COMMON;
                break;

        }
    }

    aBb[jbb]._last_instr_type = p_info->_type;
}

void Insert_Predecessor (BBINDEX icurrent, BBINDEX ipred) {
    BBLKINDEX ip, iq;
    BOOL has_this_pred;

    has_this_pred = FALSE;
    ip = INVALID;
    iq = aBb[icurrent]._pred_bb;

    while (iq != INVALID) {
        ip = iq;
        if(aBblk[ip]._ibb == ipred) {
            has_this_pred = TRUE;
            break;
        }
        else
            iq = aBblk[ip]._next;
    }

    if (!has_this_pred) {
        iq = BblkNew();
        aBblk[iq]._next = INVALID;
        aBblk[iq]._ibb = ipred;

        if (ip)
            aBblk[ip]._next = iq;
        else
            aBb[icurrent]._pred_bb = iq;
        aBb[icurrent]._pred_bb_num ++;
    }
}


void Remove_Predecessor (BBINDEX icurrent, BBINDEX ipred) {
    BBLKINDEX ip, iq;
    
    ip = aBb[icurrent]._pred_bb;
    while (ip) {
        if (aBblk[ip]._ibb == ipred)
            break;
        iq = ip;
        ip = aBblk[ip]._next;
    }

    if (!ip)
        return;

    if (ip == aBb[icurrent]._pred_bb)
        aBb[icurrent]._pred_bb = aBblk[ip]._next;
    else
        aBblk[iq]._next = aBblk[ip]._next;

    aBb[icurrent]._pred_bb_num --;
}

void Insert_Successor (BBINDEX icurrent, BBINDEX isucc) {
    BBLKINDEX ip, iq;
    BOOL has_this_succ;

    has_this_succ = FALSE;
    ip = INVALID;
    iq = aBb[icurrent]._succ_bb;
    
    while (iq != INVALID) {
        ip = iq;
        if (aBblk[ip]._ibb == isucc) {
            has_this_succ = TRUE;
            break;
        }
        else
            iq = aBblk[ip]._next;
    }

    if (!has_this_succ) {
        iq = BblkNew();
        aBblk[iq]._ibb = isucc;
        aBblk[iq]._next = INVALID;

        if (ip)
            aBblk[ip]._next = iq;
        else
            aBb[icurrent]._succ_bb = iq;
        
        aBb[icurrent]._succ_bb_num ++;
    }
}

void CreatePredSucc (BT_INFO *p_info, QUEUE *target_queue, QUEUE *bb_queue) {
    BBINDEX jbb_target, jbb_fallth;
    BBINDEX jbb = p_info->_current_bb;

    switch (aBb[jbb]._last_instr_type) {
        case T_JUMP_RELATIVE:
        {
            //Form the target block node
            jbb_target = FormBlock(p_info->_target_addr);
            aBb[jbb_target]._ifun = ifun;

            QueuePush(target_queue, p_info->_target_addr);
            QueuePush(bb_queue, jbb_target);

            Insert_Predecessor (jbb_target, jbb);
            Insert_Successor (jbb, jbb_target);

            //Form the fallthrough block node
            if (p_info->_next_ins_addr+20 < aFun[ifun]._entry_addr+aFun[ifun]._func_size) {
                jbb_fallth = FormBlock(p_info->_next_ins_addr);
                aBb[jbb_fallth]._ifun = ifun;
                QueuePush(bb_queue, jbb_fallth);
            }
         }
            break;
            
        case T_BRANCH:
        {
            //Form the fallthrough block node
            jbb_fallth = FormBlock(p_info->_next_ins_addr);
            aBb[jbb_fallth]._ifun = ifun;

            QueuePush(bb_queue, jbb_fallth);

            Insert_Predecessor (jbb_fallth, jbb);
            Insert_Successor (jbb, jbb_fallth);
            
            //Form the target block node
            jbb_target = FormBlock(p_info->_target_addr);
            aBb[jbb_target]._ifun = ifun;

            QueuePush(target_queue, p_info->_target_addr);
            QueuePush(bb_queue, jbb_target);

            Insert_Predecessor (jbb_target, jbb);
            Insert_Successor (jbb, jbb_target);
        }
            break;
            
        case T_CALL_RELATIVE:
        case T_CALLIN: 
        case T_CALL_FAR:
        case T_COMMON:
        {
            if(p_info->_next_ins_addr < aFun[ifun]._entry_addr+aFun[ifun]._func_size) {
                jbb_fallth = FormBlock(p_info->_next_ins_addr);
                aBb[jbb_fallth]._ifun = ifun;

                QueuePush(bb_queue, jbb_fallth);

                Insert_Predecessor (jbb_fallth, jbb);
                Insert_Successor (jbb, jbb_fallth);
            }
            else {
                Insert_Predecessor (jbb_fallth, jbb);
            }
        }
            break;

        case T_JUMPIN:
        {
            if (p_info->_next_ins_addr+20 < aFun[ifun]._entry_addr+aFun[ifun]._func_size) {
                jbb_fallth = FormBlock(p_info->_next_ins_addr);
                aBb[jbb_fallth]._ifun = ifun;
                QueuePush(bb_queue, jbb_fallth);
            }
        }
            break;
            
        default:
            break;
    }
}

void DisplayBlock (QUEUE *target_queue, ARRAY *bbs_in_fun) {
    int i, j;
    BOOL change;
	ELEM_TYPE t_elem;
    BBINDEX jbb, jbb_target;
    INSINDEX jins;
    ADDR32 target_addr;
    
    /* For each "target", if it falls in middle of a block, then this block need to be splitted. */
    /** A special target: tu's entry addr. There must be a block starts at tu's entry addr, so if
        any other blocks across this block, they should be splitted. */
    QueuePush(target_queue, aFun[ifun]._entry_addr);

    //Sort _target_queue by address
    QueueSort(target_queue);
    
    //Sort blocks by address
	change = TRUE;
	for(i=bbs_in_fun->NumOfElem-1; i>0&&change; --i)	{
		change = FALSE;
		for(j=0; j<i; ++j) {
			if(aBb[bbs_in_fun->ArrayBase[j]]._entry_addr > aBb[bbs_in_fun->ArrayBase[j+1]]._entry_addr)	{
				t_elem = bbs_in_fun->ArrayBase[j];
				bbs_in_fun->ArrayBase[j] = bbs_in_fun->ArrayBase[j+1];
				bbs_in_fun->ArrayBase[j+1] = t_elem;
				change = TRUE;
			}
		}
	}
    
    for (i = 0; i < bbs_in_fun->NumOfElem-1; i++)
        aBb[bbs_in_fun->ArrayBase[i]]._next = bbs_in_fun->ArrayBase[i+1];
    aBb[bbs_in_fun->ArrayBase[i]]._next = INVALID;
    aFun[ifun]._ibb_head = bbs_in_fun->ArrayBase[0];

    while (target_queue->NumOfElem) {
        target_addr = QueuePopFast(target_queue);
        /* Check each block to see whether the target is in middle of it */
        for(jbb=aFun[ifun]._ibb_head; aBb[jbb]._entry_addr<target_addr; jbb=aBb[jbb]._next) {
            if (target_addr>aBb[jbb]._entry_addr && target_addr<aBb[jbb]._end_addr) {
                jbb_target = HashSearch(target_addr);

                //Split p_block
                aBb[jbb]._ins_num = aBb[jbb]._ins_num - aBb[jbb_target]._ins_num;
                jins = aBb[jbb]._ins_first;
                aBb[jbb]._ins_last = jins + aBb[jbb]._ins_num - 1;
                aIns[aBb[jbb]._ins_last]._succ = INVALID;

                aBb[jbb]._end_addr = aBb[jbb_target]._entry_addr;

                //Adjust pred and succ
                BBLKINDEX isucc, jsucc;
                isucc = aBb[jbb]._succ_bb;
                while (isucc) {
                    //Set target_block to be p_block's succ's pred
                    Insert_Successor (jbb_target, aBblk[isucc]._ibb);
                    //Remove p_block from p_succ's pred list
                    Remove_Predecessor (aBblk[isucc]._ibb, jbb);
                    
                    jsucc = isucc;
                    isucc = aBblk[isucc]._next;
                }
                aBb[jbb]._succ_bb = INVALID;
                aBb[jbb]._succ_bb_num = 0;
                aBb[jbb]._last_instr_type = T_COMMON;

                Insert_Predecessor (jbb_target, jbb);
                Insert_Successor (jbb, jbb_target);
            }        
        }
    }
}

void Disassemble () {
    BBINDEX jbb;
    QUEUE *target_queue, *bb_queue;
    BT_INFO info;

    target_queue = QueueNew();
    bb_queue = QueueNew();

    if(aFun[ifun]._flag & FUN_HAS_DISASEM)
        return;
    
    jbb = FormBlock(aFun[ifun]._entry_addr);
    aBb[jbb]._ifun = ifun;
    aFun[ifun]._ibb_entry = jbb;

    QueuePush(bb_queue, jbb);
    aBb[jbb]._flag |= BB_ENTRY_FLAG;

    /** during the following iteration, all of the blocks in this tu will be disassembled and recorded in
       bb_queue, all of the branch/jmp target addresses will be recorded in target_queue. **/
    while (bb_queue->NumOfElem) {
        jbb = QueuePop(bb_queue);
        info._current_bb = jbb;

        Disassemble_A_Block(&info);
        CreatePredSucc(&info, target_queue, bb_queue);
    }
    
    /* Make all the disassembled blocks to be real "basic blocks"(some blocks need to be splitted), 
       and sort them by address. */
    DisplayBlock (target_queue, bb_queue->Deleted);

    aFun[ifun]._flag |= FUN_HAS_DISASEM;
}

void GetCalleeArgNum(ADDR32 entry_addr) {
    ADDR32 pc = entry_addr;
    ADDR32 end_addr = entry_addr + FileGetFunSize(entry_addr);
    REGISTER_TYPE arg_base = BT_R_ESP;
    OPERAND *p_operand;
    int i, esp_offset = 0;

    ASSERT(pc!=0, ("pc is NULL!\n"));

    if(((*(unsigned int *)(ADDR)entry_addr)&0x00ffffff)==0xec8b55)
        arg_base = BT_R_EBP;
    else if(((*(unsigned int *)(ADDR)entry_addr)&0x00ffffff)==0xdc8b53)
        arg_base = BT_R_EBX;

    p_instr_c->_op = INVALID;
    if(arg_base==BT_R_ESP) {
        while(!(p_instr_c->_op>=BT_Ihlt && p_instr_c->_op<=BT_Iretf) && pc<end_addr) {
            p_instr_c->_addr = pc;
            pc = (ADDR32)decode(p_instr_c, 32);
            p_instr_c->_next_instr_addr = pc;
            
            if(p_instr_c->_op==BT_Ipush)
                esp_offset += 4;
            else if(IS_SUB_IMM_ESP((ADDR)p_instr_c->_addr)) {
                esp_offset += (p_instr_c->_operand[1]).lval.sdword;
                break;
            }
        }
    }

    while (pc<end_addr) {
        //Disassemble a single instruction
        p_instr_c->_addr = pc;
        pc = (ADDR32)decode (p_instr_c, 32);
        p_instr_c->_next_instr_addr = pc;

        for(i=0; i<p_instr_c->_operandnumber; i++) {
            p_operand = p_instr_c->_operand + i;

            if(p_operand->type==BT_OP_MEM && p_instr_c->_op!=BT_Ilea && p_operand->base==arg_base && p_operand->index==BT_NONE)
                if(aFun[ifun]._callee_arg_off<p_operand->lval.sdword-esp_offset)
                    aFun[ifun]._callee_arg_off = p_operand->lval.sdword-esp_offset;
        }
    }
}

#ifdef _DUMP_INSTR
void DumpInstrCompare() {
    ADDR32 origin_pc, new_pc;
    BBINDEX ibb, jbb;
    INSINDEX iins;
    char origin_instr_code[16], new_instr_code[16];
    char *instr_ptr;
    int i;
    
    new_pc = aFun[ifun]._opt_code_addr;
    ibb = jbb = aFun[ifun]._ibb_entry;

    OUTPUT(("Optimized:                                                                     | Original:\n"));
    while(ibb) {
        iins = aBb[ibb]._ins_first;
        while(iins) {
            SetColor(YELLOW);
            while(aIns[iins]._opt_addr > new_pc) {
                p_instr_c->_addr = new_pc;
                if((aBb[ibb]._flag&BB_OPTIMIZED) || (aBb[jbb]._flag&BB_OPTIMIZED))
                    new_pc = (ADDR32)decode (p_instr_c, 64);
                else
                    new_pc = (ADDR32)decode (p_instr_c, 32);
                p_instr_c->_next_instr_addr = new_pc;
                Instr_Dump_ATT();
                
                OUTPUT(("\n"));
            }
            UnsetColor();

            ASSERT(aIns[iins]._opt_addr==new_pc, ("Error occured while dumping instruction\n"));
            p_instr_c->_addr = new_pc;
            if(aBb[ibb]._flag&BB_OPTIMIZED)
                new_pc = (ADDR32)decode (p_instr_c, 64);
            else
                new_pc = (ADDR32)decode (p_instr_c, 32);
            p_instr_c->_next_instr_addr = new_pc;

            if(aIns[iins]._addr) {
                instr_ptr = (char *)(ADDR)(p_instr_c->_addr);
                for(i=0; i<p_instr_c->_next_instr_addr - p_instr_c->_addr; i++)
                    new_instr_code[i] = instr_ptr[i];
                new_instr_code[i] = '\0';
                instr_ptr = (char *)(ADDR)(aIns[iins]._addr);
                for(i=0; i<aIns[iins]._addr_next - aIns[iins]._addr; i++)
                    origin_instr_code[i] = instr_ptr[i];
                origin_instr_code[i] = '\0';
                if(strcmp(origin_instr_code, new_instr_code))
                    SetColor(YELLOW);
                
                Instr_Dump_ATT();

                if(strcmp(origin_instr_code, new_instr_code))
                    OUTPUT(("+    "))
                else
                    OUTPUT(("|    "))
                
                p_instr_c->_addr = aIns[iins]._addr;
                origin_pc = (ADDR32)decode (p_instr_c, 32);
                p_instr_c->_next_instr_addr = origin_pc;
                Instr_Dump_ATT();
            }
            else {
                SetColor(YELLOW);
                Instr_Dump_ATT();
            }
            
            OUTPUT(("\n"));

            iins = aIns[iins]._succ;
        }

        OUTPUT(("\n"));
        jbb = ibb;
        ibb = aBb[ibb]._next;
    }
    
    SetColor(YELLOW);
    p_instr_c->_addr = aIns[aBb[jbb]._ins_last]._opt_addr + aIns[aBb[jbb]._ins_last]._size;
    while(*(int *)(ADDR)(p_instr_c->_addr)!=0) {
        new_pc = (ADDR32)decode (p_instr_c, 64);
        p_instr_c->_next_instr_addr = new_pc;
        Instr_Dump_ATT();
        p_instr_c->_addr = new_pc;
        
        OUTPUT(("\n"));
    }

    UnsetColor();
}
#endif

#ifdef _DEBUG
void DumpInstr(ADDR32 start, int mode, int n) {
    ADDR32 new_pc;
    int i=0;
    #undef Error_File
    #define Error_File stderr
    p_instr_c->_addr = start;
    while(i<n) {
        new_pc = (ADDR32)decode(p_instr_c, mode);
        p_instr_c->_next_instr_addr = new_pc;
        Instr_Dump_ATT();
        p_instr_c->_addr = new_pc;
        OUTPUT(("\n"));
        i ++;
    }
    #undef Error_File
    #define Error_File dreplog
}
#endif


