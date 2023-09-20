#if (defined _DEBUG || defined _DUMP_INSTR)
#include <stdio.h>
#include <stdarg.h>
#include "dec_types.h"
#include "utility.h"

#define INSTR_CODE_LEN 128
char insn_buffer[INSTR_CODE_LEN] = {0};
unsigned int insn_fill = 0;

const char* bt_reg_tab[] = 
{
  "none",
  
  "al",     "cl",       "dl",       "bl",
  "ah",     "ch",       "dh",       "bh",
  "spl",    "bpl",      "sil",      "dil",
  "r8b",    "r9b",      "r10b",     "r11b",
  "r12b",   "r13b",     "r14b",     "r15b",

  "ax",     "cx",       "dx",       "bx",
  "sp",     "bp",       "si",       "di",
  "r8w",    "r9w",      "r10w",     "r11w",
  "r12w",   "r13W"  ,   "r14w",     "r15w",
    
  "eax",    "ecx",      "edx",      "ebx",
  "esp",    "ebp",      "esi",      "edi",
  "r8d",    "r9d",      "r10d",     "r11d",
  "r12d",   "r13d",     "r14d",     "r15d",

  "rax",    "rcx",      "rdx",      "rbx",
  "rsp",    "rbp",      "rsi",      "rdi",
  "r8",     "r9",       "r10",      "r11",
  "r12",    "r13",      "r14",      "r15",
  
  "es",     "cs",       "ss",       "ds",
  "fs",     "gs",   

  "cr0",    "cr1",      "cr2",      "cr3",
  "cr4",    "cr5",      "cr6",      "cr7",
  "cr8",    "cr9",      "cr10",     "cr11",
  "cr12",   "cr13",     "cr14",     "cr15",
    
  "dr0",    "dr1",      "dr2",      "dr3",
  "dr4",    "dr5",      "dr6",      "dr7",
  "dr8",    "dr9",      "dr10",     "dr11",
  "dr12",   "dr13",     "dr14",     "dr15",

  "mm0",    "mm1",      "mm2",      "mm3",
  "mm4",    "mm5",      "mm6",      "mm7",

  "st0",    "st1",      "st2",      "st3",
  "st4",    "st5",      "st6",      "st7", 

  "xmm0",   "xmm1",     "xmm2",     "xmm3",
  "xmm4",   "xmm5",     "xmm6",     "xmm7",
  "xmm8",   "xmm9",     "xmm10",    "xmm11",
  "xmm12",  "xmm13",    "xmm14",    "xmm15",

  "rip"
};

static void mkasm(const char* fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  insn_fill += vsprintf((char*)insn_buffer + insn_fill, fmt, ap);
  va_end(ap);
  ASSERT(insn_fill<INSTR_CODE_LEN, ("The dumped instr code is overflow.\n"))
}

const char * bt_lookup_mnemonic(OPCODE op)
{
    if ( op < BT_Inone)
        return mnemonics[op];
    return NULL;
}

/* -----------------------------------------------------------------------------
 * opr_cast() - Prints an operand cast.
 * -----------------------------------------------------------------------------
 */
static void opr_cast(OPERAND* op)
{
  switch(op->size) {
    case 16 : 
    case 32 :
        mkasm("*");   break;
    default: break;
  }
}

/* -----------------------------------------------------------------------------
 * gen_operand() - Generates assembly output for each operand.
 * -----------------------------------------------------------------------------
 */
static void 
gen_operand(INSTR_CUT* p_instr_c, OPERAND* op)
{
  switch(op->type) {
    case BT_OP_REG:
    case BT_OP_FREG:
    case BT_OP_MMXREG:
    case BT_OP_XMMREG:
        mkasm("%%%s", bt_reg_tab[op->base]);
        break;

    case BT_OP_MEM:
        mkasm("0x%lx", op->lval.sdword);
    
        if (op->base)
            mkasm("(%%%s", bt_reg_tab[op->base]);
        if (op->index) {
            if (op->base)
                mkasm(",");
            else 
                mkasm("(");
            mkasm("%%%s", bt_reg_tab[op->index]);
        }
        if (op->scale)
            mkasm(",%d", op->scale);
        if (op->base || op->index)
            mkasm(")");
        break;

    case BT_OP_IMM:
        switch (op->size) {
            case  8: mkasm("$0x%x", op->lval.ubyte);    break;
            case 16: mkasm("$0x%x", op->lval.uword);    break;
            case 32: mkasm("$0x%lx", op->lval.udword);  break;
            case 64: mkasm("$0x%llx", op->lval.uqword); break;
            default: break;
        }
        break;

    case BT_OP_JIMM:
        switch (op->size) {
            case  8:
                mkasm("0x%lx", p_instr_c->_next_instr_addr + op->lval.sbyte); 
                break;
            case 16:
                mkasm("0x%lx", p_instr_c->_next_instr_addr + op->lval.sword);
                break;
            case 32:
                mkasm("0x%lx", p_instr_c->_next_instr_addr + op->lval.sdword);
                break;
            default:break;
        }
        break;

    case BT_OP_SIMM:
        mkasm("$0x%lx", op->lval.sdword); 
        break;

    case BT_OP_PTR:
        switch (op->size) {
            case 32:
                mkasm("$0x%x, $0x%x", op->lval.ptr.seg, 
                    op->lval.ptr.off & 0xFFFF);
                break;
            case 48:
                mkasm("$0x%x, $0x%lx", op->lval.ptr.seg, 
                    op->lval.ptr.off);
                break;
        }
        break;
            
    default: return;
  }
}

/* =============================================================================
 * translates to AT&T syntax 
 * =============================================================================
 */
void Instr_Dump_ATT()
{
  int i;
  int size = 0;
  char *p_instr_code;

  insn_fill = 0;

  mkasm("0x%lx: ", p_instr_c->_addr);
  p_instr_code = (char *)(ADDR)(p_instr_c->_addr);
  for(i=0; i<p_instr_c->_next_instr_addr-p_instr_c->_addr; i++) {
    if((unsigned char)p_instr_code[i] > 0x0f)
        mkasm("%x", (unsigned char)p_instr_code[i]);
    else if((unsigned char)p_instr_code[i] != 0)
        mkasm("0%x", (unsigned char)p_instr_code[i]);
    else
        mkasm("00");
  }
  for(; i<12; i++)
    mkasm("  ");

  if (p_instr_c->_prefix == cLOCK)
    mkasm("lock ");
  if (p_instr_c->_prefix == cREP)
    mkasm("rep ");
  if (p_instr_c->_prefix == cREPE)
        mkasm("repne ");

  /* special instructions */
  switch (p_instr_c->_op) {
    case BT_Iretf: 
        mkasm("lret "); 
        break;
    case BT_Idb:
        mkasm(".byte 0x%x", p_instr_c->_operand[0].lval.ubyte);
        return;

    default:
        mkasm("%s", bt_lookup_mnemonic(p_instr_c->_op));
  }

  size = p_instr_c->_operand[0].size;
  if (p_instr_c->_operand[1].size > size)
    size = p_instr_c->_operand[1].size;
  if (p_instr_c->_operand[2].size > size)
    size = p_instr_c->_operand[2].size;

  mkasm(" ");

  if(p_instr_c->_operandnumber > 2) {
    gen_operand(p_instr_c, &p_instr_c->_operand[2]);
    mkasm(", ");
  }

  if(p_instr_c->_operandnumber > 1) {
    gen_operand(p_instr_c, &p_instr_c->_operand[1]);
    mkasm(", ");
  }

  gen_operand(p_instr_c, &p_instr_c->_operand[0]);

  OUTPUT(("%-75s", insn_buffer));
}

#endif

