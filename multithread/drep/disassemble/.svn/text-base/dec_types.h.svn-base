/* ----------------------------------------------------------------------------- 
Copyright  (c) 2006, Vivek Mohan <vivek@sig9.com> All rights reserved. See LICENSE
   ----------------------------------------------------------------------------- */
#ifndef _DEC_TYPES_H
#define _DEC_TYPES_H

#include <stddef.h>

#include "opcmap.h"
#include "common_types.h"

/* ----------------------------------------------------------------------------- 
   All possible "types" of objects in udis86. Order is Important!
   ----------------------------------------------------------------------------- */
typedef enum
{
  BT_NONE,

  /* 8 bit GPRs */
  BT_R_AL, BT_R_CL, BT_R_DL, BT_R_BL,
  BT_R_AH, BT_R_CH, BT_R_DH, BT_R_BH,
  BT_R_SPL, BT_R_BPL, BT_R_SIL, BT_R_DIL,
  BT_R_R8B, BT_R_R9B, BT_R_R10B, BT_R_R11B,
  BT_R_R12B, BT_R_R13B, BT_R_R14B, BT_R_R15B,

  /* 16 bit GPRs */
  BT_R_AX, BT_R_CX, BT_R_DX, BT_R_BX,
  BT_R_SP, BT_R_BP, BT_R_SI, BT_R_DI,
  BT_R_R8W, BT_R_R9W, BT_R_R10W, BT_R_R11W,
  BT_R_R12W, BT_R_R13W, BT_R_R14W, BT_R_R15W,

  /* 32 bit GPRs */
  BT_R_EAX, BT_R_ECX, BT_R_EDX, BT_R_EBX,
  BT_R_ESP, BT_R_EBP, BT_R_ESI, BT_R_EDI,
  BT_R_R8D, BT_R_R9D, BT_R_R10D, BT_R_R11D,
  BT_R_R12D, BT_R_R13D, BT_R_R14D, BT_R_R15D,

  /* 64 bit GPRs */
  BT_R_RAX, BT_R_RCX, BT_R_RDX, BT_R_RBX,
  BT_R_RSP, BT_R_RBP, BT_R_RSI, BT_R_RDI,
  BT_R_R8, BT_R_R9, BT_R_R10, BT_R_R11,
  BT_R_R12, BT_R_R13, BT_R_R14, BT_R_R15,
  
  /* segment registers */
  BT_R_ES, BT_R_CS, BT_R_SS, BT_R_DS,
  BT_R_FS, BT_R_GS,

  /* control registers */
  BT_R_CR0, BT_R_CR1, BT_R_CR2, BT_R_CR3,
  BT_R_CR4, BT_R_CR5, BT_R_CR6, BT_R_CR7,
  BT_R_CR8, BT_R_CR9, BT_R_CR10, BT_R_CR11,
  BT_R_CR12, BT_R_CR13, BT_R_CR14, BT_R_CR15,

  /* debug registers */
  BT_R_DR0, BT_R_DR1, BT_R_DR2, BT_R_DR3,
  BT_R_DR4, BT_R_DR5, BT_R_DR6, BT_R_DR7,
  BT_R_DR8, BT_R_DR9, BT_R_DR10, BT_R_DR11,
  BT_R_DR12, BT_R_DR13, BT_R_DR14, BT_R_DR15,

  /* mmx registers */
  BT_R_MM0, BT_R_MM1, BT_R_MM2, BT_R_MM3,
  BT_R_MM4, BT_R_MM5, BT_R_MM6, BT_R_MM7,

  /* x87 registers */
  BT_R_ST0, BT_R_ST1, BT_R_ST2, BT_R_ST3,
  BT_R_ST4, BT_R_ST5, BT_R_ST6, BT_R_ST7,

  /* extended multimedia registers */
  BT_R_XMM0, BT_R_XMM1, BT_R_XMM2, BT_R_XMM3,
  BT_R_XMM4, BT_R_XMM5, BT_R_XMM6, BT_R_XMM7,
  BT_R_XMM8, BT_R_XMM9, BT_R_XMM10, BT_R_XMM11,
  BT_R_XMM12, BT_R_XMM13, BT_R_XMM14, BT_R_XMM15,

  BT_R_RIP
}REGISTER_TYPE;

typedef enum
{
  /* Operand Types */
  BT_OP_ES_MEM, BT_OP_CS_MEM, BT_OP_SS_MEM, BT_OP_DS_MEM,
  BT_OP_FS_MEM, BT_OP_GS_MEM,
  BT_OP_REG, BT_OP_MEM, BT_OP_PTR, BT_OP_IMM,
  BT_OP_JIMM, BT_OP_SIMM, BT_OP_FREG, BT_OP_MMXREG, BT_OP_XMMREG,
  BT_OP_SEG,
  BT_OP_NONE
}OP_TYPE;

/* ----------------------------------------------------------------------------- OPERAND
   - Disassembled instruction Operand.
   ----------------------------------------------------------------------------- */
typedef struct {
  OP_TYPE type;
  UINT8 size;
  union {
    INT8 sbyte;
    UINT8 ubyte;
    INT16 sword;
    UINT16 uword;
    INT32 sdword;
    UINT32 udword;
    INT64 sqword;
    UINT64 uqword;

    struct {
      UINT16 seg;
      UINT32 off;
    } ptr;
  } lval;

  REGISTER_TYPE base;
  REGISTER_TYPE index;
  UINT8 scale;
} OPERAND;

typedef struct {
  ADDR pc;
  MAP_ENTRY *mapen;
  OPCODE mnemonic;
  OPERAND operand[3];
  UINT8 operand_number;
  UINT8 dest_opnd_number;
  UINT8 src_opnd_number;
  UINT8 src_opnd_start;

  UINT8 dis_mode;
  UINT8 vendor;
  UINT8 error;
  UINT8 pfx_rex;
  UINT8 pfx_seg;
  UINT8 pfx_opr;
  UINT8 pfx_adr;
  UINT8 pfx_lock;
  UINT8 pfx_rep;
  // UINT8 pfx_repe;
  UINT8 pfx_repne;
  UINT8 pfx_insn;
  UINT8 default64;
  UINT8 opr_mode;
  UINT8 adr_mode;
  UINT8 br_far;
  UINT8 br_near;
}UD;

typedef struct {
    ADDR32 _addr;
    ADDR32 _next_instr_addr;
    OPCODE _op;
    INT8 _operandnumber;
  	INT8 _src_opnd_number;
  	INT8 _dest_opnd_number;
  	INT8 _src_opnd_start;
    OPERAND _operand[3];
	PREFIX _prefix;
}INSTR_CUT;

/* ----------------------------------------------------------------------------- Type-definitions
   ----------------------------------------------------------------------------- */

extern INSTR_CUT *p_instr_c;
extern ADDR decode (INSTR_CUT *p_instr_c, int disas_mode);

#define BT_EOI			-1
#define BT_INP_CACHE_SZ		32
#define BT_VENDOR_AMD		0
#define BT_VENDOR_INTEL		1
#define ALLFR 0xff
#define INVAL 0xfe
#define ALLINTR 0xfd
#endif
