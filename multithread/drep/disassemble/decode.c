/* ----------------------------------------------------------------------------- 
   decode.c
   Copyright (c) 2005, 2006, Vivek Mohan <vivek@sig9.com> All rights reserved. See LICENSE
   ----------------------------------------------------------------------------- */

#include <string.h>
#include <stdio.h>
#include "dec_types.h"
#include "input.h"
#include "opcmap.h"
#include "mnemonics.h"
#include "utility.h"

/* The max number of prefixes to an instruction */
#define MAX_PREFIXES	15

/* register types */
#define T_NONE	0
#define T_GPR	1
#define T_MMX	2
#define T_CRG	3
#define T_DBG	4
#define T_SEG	5
#define T_XMM	6
#define FSTI	8
MAP_ENTRY *bt_me_db ();
MAP_ENTRY *bt_me_invalid ();

/* ----------------------------------------------------------------------------- resolve_oprsize()- 
   Resolves the size of operand depending on the current disassembly mode, effective operand sizes, 
   etc. ----------------------------------------------------------------------------- */
static unsigned int resolve_oprsize (register UD *u, unsigned int s)
{
  switch (s)
  {
    case SZ_V:
      return (u->opr_mode);
    case SZ_Z:
      return (u->opr_mode == 16) ? 16 : 32;
    case SZ_P:
      return (u->opr_mode == 16) ? SZ_WP : SZ_DP;
    case SZ_MDQ:
      return (u->opr_mode == 16) ? 32 : u->opr_mode;
    case SZ_RDQ:
      return (u->dis_mode == 64) ? 64 : 32;
    default:
      return s;
  }
}

/* -----------------------------------------------------------------------------
   resolve_mnemonic()- Resolves the correct mnemonic that depends on the current effective operand 
   or address mode. ----------------------------------------------------------------------------- */
static OPCODE resolve_mnemonic (register UD *u)
{

  if (u->opr_mode == 32)
  {
    switch (u->mnemonic)
    {
      case BT_Icbw:
        return BT_Icwde;
      case BT_Icwd:
        return BT_Icdq;
      case BT_Ilodsw:
        return BT_Ilodsd;
      case BT_Imovsw:
        return BT_Imovsd;
      case BT_Icmpsw:
        return BT_Icmpsd;
      case BT_Iinsw:
        return BT_Iinsd;
      case BT_Ioutsw:
        return BT_Ioutsd;
      case BT_Ipushfw:
        return BT_Ipushfd;
      case BT_Ipopfw:
        return BT_Ipopfd;
      case BT_Istosw:
        return BT_Istosd;
      case BT_Iscasw:
        return BT_Iscasd;
      case BT_Iiretw:
        return BT_Iiretd;
      case BT_Ipusha:
        return BT_Ipushad;
      case BT_Ipopa:
        return BT_Ipopad;
      default:
        break;
    }
  }

  if (u->opr_mode == 64)
  {
    switch (u->mnemonic)
    {
      case BT_Icbw:
        return BT_Icdqe;
      case BT_Icwd:
        return BT_Icqo;
      case BT_Ilodsw:
        return BT_Ilodsq;
      case BT_Imovsw:
        return BT_Imovsq;
      case BT_Icmpsw:
        return BT_Icmpsq;
      case BT_Iinsw:
        return BT_Iinsd;
      case BT_Ioutsw:
        return BT_Ioutsd;
      case BT_Icmpxchg8b:
        return BT_Icmpxchg16b;
      case BT_Istosw:
        return BT_Istosq;
      case BT_Iscasw:
        return BT_Iscasq;
      case BT_Iiretw:
        return BT_Iiretq;
      case BT_Ipushfw:
        return BT_Ipushfq;
      case BT_Ipopfw:
        return BT_Ipopfq;
      default:
        break;
    }
  }

  if (u->mnemonic == BT_Iswapgs && u->dis_mode != 64)
  {
    u->error = 1;
  }

  if (u->adr_mode == 32)
  {
    switch (u->mnemonic)
    {
      case BT_Ijcxz:
        return BT_Ijecxz;
      default:
        break;
    }
  }

  if (u->adr_mode == 64)
  {
    switch (u->mnemonic)
    {
      case BT_Ijcxz:
        return BT_Ijrcxz;
      default:
        break;
    }
  }

  return u->mnemonic;
}

/* ----------------------------------------------------------------------------- decode_a()-
   Decodes operands of the type seg:offset
   ----------------------------------------------------------------------------- */
static void decode_a (UD *u, OPERAND *op)
{
  if (u->opr_mode == 16)
  {
    /* seg16:off16 */
    op->type = BT_OP_PTR;
    op->size = 32;
    op->lval.ptr.off = inp_uint16 (u);
    op->lval.ptr.seg = inp_uint16 (u);
  }
  else
  {
    /* seg16:off32 */
    op->type = BT_OP_PTR;
    op->size = 48;
    op->lval.ptr.off = inp_uint32 (u);
    op->lval.ptr.seg = inp_uint16 (u);
  }
}

/* ----------------------------------------------------------------------------- decode_gpr() -
   Returns decoded General Purpose Register
   ----------------------------------------------------------------------------- */
static REGISTER_TYPE decode_gpr (register UD *u, unsigned int s, unsigned char rm)
{
  s = resolve_oprsize (u, s);

  switch (s)
  {
    case 64:
      return (REGISTER_TYPE) (BT_R_RAX + rm);
    case SZ_DP:
    case 32:
      return (REGISTER_TYPE) (BT_R_EAX + rm);
    case SZ_WP:
    case 16:
      return (REGISTER_TYPE) (BT_R_AX + rm);
    case 8:
      if (u->dis_mode == 64 && u->pfx_rex)
      {
        if (rm >= 4)
          return (REGISTER_TYPE) (BT_R_SPL + (rm - 4));
        return (REGISTER_TYPE) (BT_R_AL + rm);
      }
      else
        return (REGISTER_TYPE) (BT_R_AL + rm);
    default:
      return (REGISTER_TYPE) 0;
  }
}

/* ----------------------------------------------------------------------------- resolve_gpr64() -
   64bit General Purpose Register-Selection.
   ----------------------------------------------------------------------------- */
static void resolve_gpr64 (UD *u, OPERAND *iop, MAP_OPERAND_TYPE gpr_op)
{
  if (gpr_op >= OP_rAXr8 && gpr_op <= OP_rDIr15)
    gpr_op = (MAP_OPERAND_TYPE) ((gpr_op - OP_rAXr8) | (P_REX_B (u->pfx_rex) << 3));
  else
    gpr_op = (MAP_OPERAND_TYPE) (gpr_op - OP_rAX);

  if (u->opr_mode == 16)
  {
    iop->base = (REGISTER_TYPE) (gpr_op + BT_R_AX);
    iop->size = 16;
    return;
  }
  if (u->dis_mode == 32 || (u->opr_mode == 32 && !(P_REX_W (u->pfx_rex) || u->default64)))
  {
    iop->base = (REGISTER_TYPE) (gpr_op + BT_R_EAX);
    iop->size = 32;
    return;
  }

  iop->base = (REGISTER_TYPE) (gpr_op + BT_R_RAX);
  iop->size = 64;
}

/* ----------------------------------------------------------------------------- resolve_gpr32 () - 
   32bit General Purpose Register-Selection.
   ----------------------------------------------------------------------------- */
static void resolve_gpr32 (UD *u, OPERAND *iop, MAP_OPERAND_TYPE gpr_op)
{
  gpr_op = (MAP_OPERAND_TYPE) (gpr_op - OP_eAX);

  if (u->opr_mode == 16)
  {
    iop->base = (REGISTER_TYPE) (gpr_op + BT_R_AX);
    iop->size = 16;
  }
  else
  {
    iop->base = (REGISTER_TYPE) (gpr_op + BT_R_EAX);
    iop->size = 32;
  }
}

/* ----------------------------------------------------------------------------- resolve_reg() -
   Resolves the register type
   ----------------------------------------------------------------------------- */
static void resolve_reg (UD *u, OPERAND *iop, unsigned int type, unsigned char i)
{
  switch (type)
  {
    case T_MMX:
      iop->type = BT_OP_MMXREG;
      iop->size = 64;
      iop->base = (REGISTER_TYPE) (BT_R_MM0 + (i & 7));
      break;
    case T_XMM:
      iop->type = BT_OP_XMMREG;
      iop->size = 128;
      iop->base = (REGISTER_TYPE) (BT_R_XMM0 + i);
      break;
    case T_CRG:
      iop->size = 0;
      iop->base = (REGISTER_TYPE) (BT_R_CR0 + i);
      break;
    case T_DBG:
      iop->size = 0;
      iop->base = (REGISTER_TYPE) (BT_R_DR0 + i);
      break;
    case T_SEG:
      iop->size = 0;
      iop->base = (REGISTER_TYPE) (BT_R_ES + (i & 7));
      break;
    case T_NONE:
    default:
      WARNING(("Resolve_reg: Invalid register types."));
  }
}

/* ----------------------------------------------------------------------------- decode_imm() -
   Decodes Immediate values.
   ----------------------------------------------------------------------------- */
static void decode_imm (UD *u, unsigned int s, OPERAND *op)
{
  op->size = resolve_oprsize (u, s);
  op->type = BT_OP_IMM;

  switch (op->size)
  {
    case 8:
      op->lval.sbyte = inp_uint8 (u);
      break;
    case 16:
      op->lval.uword = inp_uint16 (u);
      break;
    case 32:
      op->lval.udword = inp_uint32 (u);
      break;
    case 64:
      op->lval.uqword = inp_uint64 (u);
      break;
    default:
      return;
  }
}

/* ----------------------------------------------------------------------------- decode_modrm() -
   Decodes ModRM Byte ----------------------------------------------------------------------------- */
static void
decode_modrm (UD *u, OPERAND *op, unsigned int s,
              unsigned char rm_type, OPERAND *opreg,
              unsigned char reg_size, unsigned char reg_type)
{
  unsigned char mod, rm, reg;
  UINT8 offset = 0;
  inp_next (u);

  /* get mod, r/m and reg fields */
  mod = MODRM_MOD (inp_curr (u));
  rm = (P_REX_B (u->pfx_rex) << 3) | MODRM_RM (inp_curr (u));
  reg = (P_REX_R (u->pfx_rex) << 3) | MODRM_REG (inp_curr (u));

  op->size = resolve_oprsize (u, s);

  /* if mod is 11b, then the BT_R_m specifies a gpr/mmx/sse/control/debug */
  if (mod == 3)
  {
    op->type = BT_OP_REG;
    if (rm_type == T_GPR)
      op->base = decode_gpr (u, op->size, rm);
    else{
	if (rm_type==T_XMM)
	      resolve_reg (u, op, rm_type, /*(P_REX_R (u->pfx_rex) << 3) |*/ (rm & 15));
	else
		resolve_reg (u, op, rm_type, /*(P_REX_R (u->pfx_rex) << 3) |*/ (rm & 7));
    }
  }
  /* else its memory addressing */
  else
  {
    op->type = BT_OP_MEM;

    /* 64bit addressing */
    if (u->adr_mode == 64)
    {

      op->base = (REGISTER_TYPE) (BT_R_RAX + rm);

      /* get offset type */
      if (mod == 1)
        offset = 8;
      else if (mod == 2)
        offset = 32;
      else if (mod == 0 && (rm & 7) == 5)
      {
        op->base = BT_R_RIP;
        offset = 32;
      }
      else
        offset = 0;

      /* Scale-Index-Base (SIB) */
      if ((rm & 7) == 4)
      {
        inp_next (u);

        // op->scale = (1 << SIB_S(inp_curr(u))) & ~1;
        op->scale = SIB_S (inp_curr (u));
        op->index =
          (REGISTER_TYPE) (BT_R_RAX + (SIB_I (inp_curr (u)) | (P_REX_X (u->pfx_rex) << 3)));
        op->base = (REGISTER_TYPE) (BT_R_RAX + (SIB_B (inp_curr (u)) | (P_REX_B (u->pfx_rex) << 3)));

        /* special conditions for base reference */
        if (op->index == BT_R_RSP)
        {
          op->index = BT_NONE;
          op->scale = BT_NONE;
        }

        if (op->base == BT_R_RBP || op->base == BT_R_R13)
        {
          if (mod == 0)
            op->base = BT_NONE;
          if (mod == 1)
            offset = 8;
          else
            offset = 32;
        }
      }
    }

    /* 32-Bit addressing mode */
    else if (u->adr_mode == 32)
    {

      /* get base */
      op->base = (REGISTER_TYPE) (BT_R_EAX + rm);

      /* get offset type */
      if (mod == 1)
        offset = 8;
      else if (mod == 2)
        offset = 32;
      else if (mod == 0 && rm == 5)
      {
        op->base = BT_NONE;
        offset = 32;
      }
      else
        offset = 0;

      /* Scale-Index-Base (SIB) */
      if ((rm & 7) == 4)
      {
        inp_next (u);

        // op->scale = (1 << SIB_S(inp_curr(u))) & ~1;
        op->scale = SIB_S (inp_curr (u));
        op->index =
          (REGISTER_TYPE) (BT_R_EAX + (SIB_I (inp_curr (u)) | (P_REX_X (u->pfx_rex) << 3)));
        op->base = (REGISTER_TYPE) (BT_R_EAX + (SIB_B (inp_curr (u)) | (P_REX_B (u->pfx_rex) << 3)));

        if (op->index == BT_R_ESP)
        {
          op->index = BT_NONE;
          op->scale = BT_NONE;
        }

        /* special condition for base reference */
        if (op->base == BT_R_EBP)
        {
          if (mod == 0)
            op->base = BT_NONE;
          if (mod == 1)
            offset = 8;
          else
            offset = 32;
        }
      }
    }

    /* 16bit addressing mode */
    else
    {
      switch (rm)
      {
        case 0:
          op->base = BT_R_BX;
          op->index = BT_R_SI;
          break;
        case 1:
          op->base = BT_R_BX;
          op->index = BT_R_DI;
          break;
        case 2:
          op->base = BT_R_BP;
          op->index = BT_R_SI;
          break;
        case 3:
          op->base = BT_R_BP;
          op->index = BT_R_DI;
          break;
        case 4:
          op->base = BT_R_SI;
          break;
        case 5:
          op->base = BT_R_DI;
          break;
        case 6:
          op->base = BT_R_BP;
          break;
        case 7:
          op->base = BT_R_BX;
          break;
      }

      if (mod == 0 && rm == 6)
      {
        offset = 16;
        op->base = BT_NONE;
      }
      else if (mod == 1)
        offset = 8;
      else if (mod == 2)
        offset = 16;
    }
  }

  /* extract offset, if any */
  switch (offset)
  {
    case 8:
      op->lval.sqword = (INT64) inp_int8 (u);
      break;
    case 16:
      op->lval.sqword = (INT64) inp_int16 (u);
      break;
    case 32:
      op->lval.sqword = (INT64) inp_int32 (u);
      break;
    case 64:
      op->lval.sqword = (INT64) inp_int64 (u);
      break;
    default:
      break;
  }

  /* resolve register encoded in reg field */
  if (opreg)
  {
    opreg->type = BT_OP_REG;
    opreg->size = resolve_oprsize (u, reg_size);
    if (reg_type == T_GPR)
      opreg->base = decode_gpr (u, opreg->size, reg);
    else
      resolve_reg (u, opreg, reg_type, reg);
  }
}

/* ----------------------------------------------------------------------------- decode_o() -
   Decodes offset ----------------------------------------------------------------------------- */
static void decode_o (UD *u, unsigned int s, OPERAND *op)
{
  switch (u->adr_mode)
  {
    case 64:
      op->lval.uqword = inp_uint64 (u);
      break;
    case 32:
      op->lval.udword = inp_uint32 (u);
      break;
    case 16:
      op->lval.uword = inp_uint16 (u);
      break;
    default:
      return;
  }
  op->type = BT_OP_MEM;
  op->size = resolve_oprsize (u, s);
}

/* ----------------------------------------------------------------------------- disasm_operands()
   - Disassembles Operands.
   ----------------------------------------------------------------------------- */
static void disasm_operands (register UD *u)
{

  /* mopXt = map entry, operand X, type; */
  MAP_OPERAND_TYPE mop1t = (MAP_OPERAND_TYPE) u->mapen->operand1.type;
  MAP_OPERAND_TYPE mop2t = (MAP_OPERAND_TYPE) u->mapen->operand2.type;
  MAP_OPERAND_TYPE mop3t = (MAP_OPERAND_TYPE) u->mapen->operand3.type;


  /* mopXs = map entry, operand X, size */
  unsigned int mop1s = u->mapen->operand1.size;
  unsigned int mop2s = u->mapen->operand2.size;
  unsigned int mop3s = u->mapen->operand3.size;
  register OPERAND *iop = u->operand;

  u->operand_number = mop1t ? (mop2t ? (mop3t ? 3 : 2) : 1) : 0;
  /* iop = instruction operand */

  switch (mop1t)
  {

    case OP_A:
      decode_a (u, &(iop[0]));
      break;

      /* M[b] ... */
    case OP_M:
      if (MODRM_MOD (inp_peek (u)) == 3)
        u->error = 1;
      /* E, G/P/V/I/CL/1/S */
    case OP_E:
      if (mop2t == OP_G)
      {
        decode_modrm (u, &(iop[0]), mop1s, T_GPR, &(iop[1]), mop2s, T_GPR);
        if (mop3t == OP_I)
          decode_imm (u, mop3s, &(iop[2]));
        else if (mop3t == OP_CL)
        {
          iop[2].type = BT_OP_REG;
          iop[2].base = BT_R_CL;
          iop[2].size = 8;
        }
      }
      else if (mop2t == OP_P)
        decode_modrm (u, &(iop[0]), mop1s, T_GPR, &(iop[1]), mop2s, T_MMX);
      else if (mop2t == OP_V) {
        decode_modrm (u, &(iop[0]), mop1s, T_GPR, &(iop[1]), mop2s, T_XMM);
        if (mop3t == OP_I)
          decode_imm (u, mop3s, &(iop[2]));
      }
      else if (mop2t == OP_S)
        decode_modrm (u, &(iop[0]), mop1s, T_GPR, &(iop[1]), mop2s, T_SEG);
      else
      {
        decode_modrm (u, &(iop[0]), mop1s, T_GPR, NULL, 0, T_NONE);
        if (mop2t == OP_CL)
        {
          iop[1].type = BT_OP_REG;
          iop[1].base = BT_R_CL;
          iop[1].size = 8;
        }
        else if (mop2t == OP_I1)
        {
          iop[1].type = BT_OP_IMM;
          u->operand[1].lval.udword = 1;
        }
        else if (mop2t == OP_I)
          decode_imm (u, mop2s, &(iop[1]));
	 else if (mop2t == OP_eDX){
	 	 iop[1].type = BT_OP_REG;
      		resolve_gpr32 (u, &iop[1], mop2t);
		if (mop3t == OP_eAX){
			iop[2].type = BT_OP_REG;
      			resolve_gpr32 (u, &iop[2], mop3t);
		}
	 }
	 else if (mop2t == OP_DX){
          iop[1].type = BT_OP_REG;
          iop[1].base = BT_R_DX;
          iop[1].size = 16;
	 }
      }
      break;

      /* G, E/PR[,I]/VR */
    case OP_G:

      if (mop2t == OP_M)
      {
        if (MODRM_MOD (inp_peek (u)) == 3)
          u->error = 1;
        decode_modrm (u, &(iop[1]), mop2s, T_GPR, &(iop[0]), mop1s, T_GPR);
      }
      else if (mop2t == OP_E)
      {
        decode_modrm (u, &(iop[1]), mop2s, T_GPR, &(iop[0]), mop1s, T_GPR);
        if (mop3t == OP_I)
          decode_imm (u, mop3s, &(iop[2]));
      }
      else if (mop2t == OP_PR)
      {
        decode_modrm (u, &(iop[1]), mop2s, T_MMX, &(iop[0]), mop1s, T_GPR);
        if (mop3t == OP_I)
          decode_imm (u, mop3s, &(iop[2]));
      }
      else if (mop2t == OP_VR)
      {
        if (MODRM_MOD (inp_peek (u)) != 3)
          u->error = 1;
        decode_modrm (u, &(iop[1]), mop2s, T_XMM, &(iop[0]), mop1s, T_GPR);
        if (mop3t == OP_I)
          decode_imm (u, mop3s, &(iop[2]));		
      }
      else if (mop2t == OP_W)
        decode_modrm (u, &(iop[1]), mop2s, T_XMM, &(iop[0]), mop1s, T_GPR);
      break;

      /* AL..BH, I/O/DX */
    case OP_AL:
    case OP_CL:
    case OP_DL:
    case OP_BL:
    case OP_AH:
    case OP_CH:
    case OP_DH:
    case OP_BH:

      iop[0].type = BT_OP_REG;
      iop[0].base = (REGISTER_TYPE) (BT_R_AL + (mop1t - OP_AL));
      iop[0].size = 8;

      if (mop2t == OP_I)
        decode_imm (u, mop2s, &(iop[1]));
      else if (mop2t == OP_DX)
      {
        iop[1].type = BT_OP_REG;
        iop[1].base = BT_R_DX;
        iop[1].size = 16;
      }
      else if (mop2t == OP_O)
        decode_o (u, mop2s, &(iop[1]));
      else if (mop2t == OP_AH)
      {
        iop[1].type = BT_OP_REG;
        iop[1].base = BT_R_AH;
        iop[1].size = 8;
      }
      break;

      /* rAX[r8]..rDI[r15], I/rAX..rDI/O */
    case OP_rAXr8:
    case OP_rCXr9:
    case OP_rDXr10:
    case OP_rBXr11:
    case OP_rSPr12:
    case OP_rBPr13:
    case OP_rSIr14:
    case OP_rDIr15:
    case OP_rAX:
    case OP_rCX:
    case OP_rDX:
    case OP_rBX:
    case OP_rSP:
    case OP_rBP:
    case OP_rSI:
    case OP_rDI:

      iop[0].type = BT_OP_REG;
      resolve_gpr64 (u, &iop[0], mop1t);
      // iop[0].size = 64;
      if (mop2t == OP_I)
        decode_imm (u, mop2s, &(iop[1]));
      else if (mop2t >= OP_rAX && mop2t <= OP_rDI)
      {
        iop[1].type = BT_OP_REG;
        resolve_gpr64 (u, &iop[1], mop2t);
		if (mop3t == OP_E)
			decode_modrm (u, &(iop[2]), mop3s, T_GPR, NULL, 0, T_NONE);

      }
      else if (mop2t == OP_O)
      {
        decode_o (u, mop2s, &(iop[1]));
        iop[0].size = resolve_oprsize (u, mop2s);
      }
      else if (mop2t == OP_J)
      {
           decode_imm (u, mop2s, &(iop[1]));
           iop[1].type = BT_OP_JIMM;
      }

      break;
      /* AL[r8b]..BH[r15b], I */
    case OP_ALr8b:
    case OP_CLr9b:
    case OP_DLr10b:
    case OP_BLr11b:
    case OP_AHr12b:
    case OP_CHr13b:
    case OP_DHr14b:
    case OP_BHr15b:
    {
      REGISTER_TYPE gpr = (REGISTER_TYPE) ((mop1t - OP_ALr8b) + BT_R_AL + (P_REX_B (u->pfx_rex) << 3));
      if (BT_R_AH <= gpr && u->pfx_rex)
        gpr = (REGISTER_TYPE) (gpr + 4);
      iop[0].type = BT_OP_REG;
      iop[0].base = gpr;
      iop[0].size = 8;
      if (mop2t == OP_I)
        decode_imm (u, mop2s, &(iop[1]));
      break;
    }

      /* eAX..eDX, DX/I */
    case OP_eAX:
    case OP_eCX:
    case OP_eDX:
    case OP_eBX:
    case OP_eSP:
    case OP_eBP:
    case OP_eSI:
    case OP_eDI:

      iop[0].type = BT_OP_REG;
      resolve_gpr32 (u, &iop[0], mop1t);
      if (mop2t == OP_DX)
      {
        iop[1].type = BT_OP_REG;
        iop[1].base = BT_R_DX;
        iop[1].size = 16;
      }
      else if (mop2t == OP_I)
        decode_imm (u, mop2s, &(iop[1]));
      else if (mop2t == OP_eAX || mop2t == OP_eDI || mop2t == OP_eSI ){
      		iop[1].type = BT_OP_REG;
      		resolve_gpr32 (u, &iop[1], mop2t);
      }
      else if (mop2t == OP_AX)
      	{
        iop[1].type = BT_OP_REG;
        iop[1].base = BT_R_AX;
        iop[1].size = 16;
      	}
	break;

      /* ES..GS */
    case OP_ES:
    case OP_CS:
    case OP_DS:
    case OP_SS:
    case OP_FS:
    case OP_GS:

      /* in 64bits mode, only fs and gs are allowed */
      if (u->dis_mode == 64)
        if (mop1t != OP_FS && mop1t != OP_GS)
          u->error = 1;
      iop[0].type = BT_OP_REG;
      iop[0].base = (REGISTER_TYPE) ((mop1t - OP_ES) + BT_R_ES);
      iop[0].size = 16;
      if (mop2t == OP_G){
	  	if (mop3t == OP_M){
			if (MODRM_MOD (inp_peek (u)) == 3)
         	 u->error = 1;
        	decode_modrm (u, &(iop[2]), mop3s, T_GPR, &(iop[1]), mop2s, T_GPR);
     	 	}
	}
      break;

      /* J */
    case OP_J:
      decode_imm (u, mop1s, &(iop[0]));
      iop[0].type = BT_OP_JIMM;
      break;

      /* PR, I */
    case OP_PR:
      if (MODRM_MOD (inp_peek (u)) != 3)
        u->error = 1;
      decode_modrm (u, &(iop[0]), mop1s, T_MMX, NULL, 0, T_NONE);
      if (mop2t == OP_I)
        decode_imm (u, mop2s, &(iop[1]));
      break;

      /* VR, I */
    case OP_VR:
      if (MODRM_MOD (inp_peek (u)) != 3)
        u->error = 1;
      decode_modrm (u, &(iop[0]), mop1s, T_XMM, NULL, 0, T_NONE);
      if (mop2t == OP_I)
        decode_imm (u, mop2s, &(iop[1]));
      break;

      /* P, Q[,I]/W/E[,I] */
    case OP_P:
      if (mop2t == OP_Q)
      {
        decode_modrm (u, &(iop[1]), mop2s, T_MMX, &(iop[0]), mop1s, T_MMX);
        if (mop3t == OP_I)
          decode_imm (u, mop3s, &(iop[2]));
      }
      else if (mop2t == OP_W)
        decode_modrm (u, &(iop[1]), mop2s, T_XMM, &(iop[0]), mop1s, T_MMX);
      else if (mop2t == OP_E)
      {
        decode_modrm (u, &(iop[1]), mop2s, T_GPR, &(iop[0]), mop1s, T_MMX);
        if (mop3t == OP_I)
          decode_imm (u, mop3s, &(iop[2]));
      }else if (mop2t == OP_VR) // movdq2q
      	 decode_modrm (u, &(iop[1]), mop2s, T_XMM, &(iop[0]), mop1s, T_MMX);
      break;

      /* R, C/D */
    case OP_R:
      if (mop2t == OP_C)
        decode_modrm (u, &(iop[0]), mop1s, T_GPR, &(iop[1]), mop2s, T_CRG);
      else if (mop2t == OP_D)
        decode_modrm (u, &(iop[0]), mop1s, T_GPR, &(iop[1]), mop2s, T_DBG);
      break;

      /* C, R */
    case OP_C:
      decode_modrm (u, &(iop[1]), mop2s, T_GPR, &(iop[0]), mop1s, T_CRG);
      break;

      /* D, R */
    case OP_D:
      decode_modrm (u, &(iop[1]), mop2s, T_GPR, &(iop[0]), mop1s, T_DBG);
      break;

      /* Q, P */
    case OP_Q:
      decode_modrm (u, &(iop[0]), mop1s, T_MMX, &(iop[1]), mop2s, T_MMX);
      break;

      /* S, E */
    case OP_S:
      decode_modrm (u, &(iop[1]), mop2s, T_GPR, &(iop[0]), mop1s, T_SEG);
      break;

      /* W, V */
    case OP_W:
      decode_modrm (u, &(iop[0]), mop1s, T_XMM, &(iop[1]), mop2s, T_XMM);
      break;

      /* V, W[,I]/Q/M/E */
    case OP_V:
      if (mop2t == OP_W)
      {
        /* special cases for movlps and movhps */
        if (MODRM_MOD (inp_peek (u)) == 3)
        {
          if (u->mnemonic == BT_Imovlps)
            u->mnemonic = BT_Imovhlps;
          else if (u->mnemonic == BT_Imovhps)
            u->mnemonic = BT_Imovlhps;
        }
        decode_modrm (u, &(iop[1]), mop2s, T_XMM, &(iop[0]), mop1s, T_XMM);
        if (mop3t == OP_I)
          decode_imm (u, mop3s, &(iop[2]));
      }
      else if (mop2t == OP_Q)
        decode_modrm (u, &(iop[1]), mop2s, T_MMX, &(iop[0]), mop1s, T_XMM);
      else if (mop2t == OP_M)
      {
        if (MODRM_MOD (inp_peek (u)) == 3)
          u->error = 1;
        decode_modrm (u, &(iop[1]), mop2s, T_GPR, &(iop[0]), mop1s, T_XMM);
      }
      else if (mop2t == OP_E)
      {
        decode_modrm (u, &(iop[1]), mop2s, T_GPR, &(iop[0]), mop1s, T_XMM);
        if (mop3t == OP_I)
           decode_imm (u, mop3s, &(iop[2]));
      }else if (mop2t == OP_PR)
      	 decode_modrm(u, &(iop[1]), mop2s, T_MMX, &(iop[0]), mop1s, T_XMM);
      break;

      /* DX, eAX/AL */
    case OP_DX:
      iop[0].type = BT_OP_REG;
      iop[0].base = BT_R_DX;
      iop[0].size = 16;

      if (mop2t == OP_eAX)
      {
        iop[1].type = BT_OP_REG;
        resolve_gpr32 (u, &iop[1], mop2t);
      }
      else if (mop2t == OP_AL)
      {
        iop[1].type = BT_OP_REG;
        iop[1].base = BT_R_AL;
        iop[1].size = 8;
      }
	else if (mop2t == OP_E)
	{
        decode_modrm (u, &(iop[1]), mop2s, T_GPR, NULL, 0, T_NONE);
	}

      break;

      /* I, I/AL/eAX */
    case OP_I:
      decode_imm (u, mop1s, &(iop[0]));
      if (mop2t == OP_I)
        decode_imm (u, mop2s, &(iop[1]));
      else if (mop2t == OP_AL)
      {
        iop[1].type = BT_OP_REG;
        iop[1].base = BT_R_AL;
        iop[1].size = 16;
      }
      else if (mop2t == OP_eAX)
      {
        iop[1].type = BT_OP_REG;
        resolve_gpr32 (u, &iop[1], mop2t);
      }
      break;

      /* O, AL/eAX */
    case OP_O:
      decode_o (u, mop1s, &(iop[0]));
      iop[1].type = BT_OP_REG;
      iop[1].size = resolve_oprsize (u, mop1s);
      if (mop2t == OP_AL)
        iop[1].base = BT_R_AL;
      else if (mop2t == OP_eAX)
        resolve_gpr32 (u, &iop[1], mop2t);
      else if (mop2t == OP_rAX)
        resolve_gpr64 (u, &iop[1], mop2t);
      break;

      /* 3 */
    case OP_I3:
      iop[0].type = BT_OP_IMM;
      iop[0].lval.sbyte = 3;
      break;

      /* ST(n), ST(n) */
    case OP_ST0:
    case OP_ST1:
    case OP_ST2:
    case OP_ST3:
    case OP_ST4:
    case OP_ST5:
    case OP_ST6:
    case OP_ST7:

      iop[0].type = BT_OP_FREG;
      iop[0].base = (REGISTER_TYPE) ((mop1t - OP_ST0) + BT_R_ST0);
      iop[0].size = FSTI;

      if (mop2t >= OP_ST0 && mop2t <= OP_ST7)
      {
        iop[1].type = BT_OP_FREG;
        iop[1].base = (REGISTER_TYPE) ((mop2t - OP_ST0) + BT_R_ST0);
        iop[1].size = FSTI;
      }
      else if (mop2t == OP_M )
         decode_modrm (u, &(iop[1]), mop2s, T_GPR, NULL, 0, T_NONE);

      break;

      /* AX */
    case OP_AX:
      iop[0].type = BT_OP_REG;
      iop[0].base = BT_R_AX;
      iop[0].size = 16;
      if (mop2t == OP_AL)
      {
      iop[1].type = BT_OP_REG;
      iop[1].base = BT_R_AL;
      iop[1].size = 8;
	  if (mop3t == OP_E)
	  	  decode_modrm (u, &(iop[2]), mop3s, T_GPR, NULL, 0, T_NONE);
      }
      else if (mop2t ==OP_E)
      {
      		 decode_modrm (u, &(iop[1]), mop2s, T_GPR, NULL, 0, T_NONE);
      }
      break;

      /* none */
    default:
      iop[0].type = iop[1].type = iop[2].type = BT_OP_NONE;
  }
}

/* ----------------------------------------------------------------------------- clear_insn() -
   clear instruction pointer
   ----------------------------------------------------------------------------- */
void clear_insn (register UD *u)
{
  u->error = 0;
  u->pfx_seg = 0;
  u->pfx_opr = 0;
  u->pfx_adr = 0;
  u->pfx_lock = 0;
  u->pfx_repne = 0;
  u->pfx_rep = 0;
  u->pfx_seg = 0;
  u->pfx_rex = 0;
  u->pfx_insn = 0;
  u->operand_number = 0;
  u->mnemonic = BT_Inone;
  u->mapen = NULL;

  memset (&u->operand[0], 0, sizeof (OPERAND));
  memset (&u->operand[1], 0, sizeof (OPERAND));
  memset (&u->operand[2], 0, sizeof (OPERAND));
}

/* ==============================================================
   Instruction decoder. Returns the number of bytes decoded.
   =============================================================== */
void imm_extend (register UD *u)
{
  if (u->operand[0].type == BT_OP_JIMM)
  {
    switch (u->operand[0].size)
    {
      case 8:
        u->operand[0].lval.sqword = (INT64) (u->operand[0].lval.sbyte);
        break;
      case 16:
        u->operand[0].lval.sqword = (INT64) (u->operand[0].lval.sword);
        break;
      case 32:
        u->operand[0].lval.sqword = (INT64) (u->operand[0].lval.sdword);
        break;
      default:
        fprintf(Error_File, "+++++++jimm size err in imm_extend\n");
    }
    return;
  }
  else   if (u->operand[1].type == BT_OP_JIMM)
  {
    switch (u->operand[1].size)
    {
      case 8:
        u->operand[1].lval.sqword = (INT64) (u->operand[1].lval.sbyte);
        break;
      case 16:
        u->operand[1].lval.sqword = (INT64) (u->operand[1].lval.sword);
        break;
      case 32:
        u->operand[1].lval.sqword = (INT64) (u->operand[1].lval.sdword);
        break;
      default:
        fprintf(Error_File, "+++++++jimm size err in imm_extend\n");
    }
    return;
  }
  switch (u->mnemonic)
  {
    case BT_Iadc:
    case BT_Iadd:
    case BT_Icmp:
   // case BT_Imov:
    case BT_Ior:
    case BT_Isbb:
    case BT_Isub:
    case BT_Itest:
    case BT_Ixor:
    case BT_Iand:
      if (u->operand[1].type == BT_OP_IMM)
      {
        switch (u->operand[1].size)
        {
          case 8:
            u->operand[1].lval.sqword = (INT64) (u->operand[1].lval.sbyte);
            break;
          case 16:
            u->operand[1].lval.sqword = (INT64) (u->operand[1].lval.sword);
            break;
          case 32:
            u->operand[1].lval.sqword = (INT64) (u->operand[1].lval.sdword);
            break;
          case 64:
            break;
          default:
            fprintf(Error_File, "+++++++size err in imm_extend\n");
	    break;
        }
        u->operand[1].type = BT_OP_SIMM;
      }
      break;
    case BT_Ipush:
      if (u->operand[0].type == BT_OP_IMM)
      {
        switch (u->operand[0].size)
        {
          case 8:
            u->operand[0].lval.sqword = (INT64) (u->operand[0].lval.sbyte);
            break;
          case 16:
            u->operand[0].lval.sqword = (INT64) (u->operand[0].lval.sword);
            break;
          case 32:
            u->operand[0].lval.sqword = (INT64) (u->operand[0].lval.sdword);
            break;
          case 64:
            break;
          default:
            fprintf(Error_File, "+++++++size err in imm_extend\n");
	    break;
        }
        u->operand[0].type = BT_OP_SIMM;
      }
      break;
    case BT_Iimul:
	if (u->operand[1].type == BT_OP_IMM)
      {
        switch (u->operand[1].size)
        {
          case 8:
            u->operand[1].lval.sqword = (INT64) (u->operand[1].lval.sbyte);
            break;
          case 16:
            u->operand[1].lval.sqword = (INT64) (u->operand[1].lval.sword);
            break;
          case 32:
            u->operand[1].lval.sqword = (INT64) (u->operand[1].lval.sdword);
            break;
          case 64:
            break;
          default:
            fprintf(Error_File, "+++++++size err in imm_extend\n");
        }
        u->operand[1].type = BT_OP_SIMM;
      }
	
	if (u->operand[2].type == BT_OP_IMM)
      {
        switch (u->operand[2].size)
        {
          case 8:
            u->operand[2].lval.sqword = (INT64) (u->operand[2].lval.sbyte);
            break;
          case 16:
            u->operand[2].lval.sqword = (INT64) (u->operand[2].lval.sword);
            break;
          case 32:
            u->operand[2].lval.sqword = (INT64) (u->operand[2].lval.sdword);
            break;
          case 64:
            break;
          default:
            fprintf(Error_File, "+++++++size err in imm_extend\n");
        }
        u->operand[2].type = BT_OP_SIMM;
      }

      break;
    default:
      break;

  }

}


/******************************************************************************
*    FUNCTION NAME: 
        static void Dis_Result_To_Ir1(bt_t* p_bt_obj,DBT_IR1_INSTRUCTION* p_ir1)
*    INPUT:
        bt_t* p_bt_obj : the object returned from bt_decode 
        DBT_IR1_INSTRUCTION* p_ir1 : the ir1 we use in interpret or translation
*    OUTPUT: 
*    DESCRIPTION:
        change disassemble result to ir1
******************************************************************************/
static void Dis_Result_To_Ir1(UD * p_bt_obj, INSTR_CUT *p_instr_c)
{
    int i=0;
    p_instr_c->_op = p_bt_obj->mnemonic;
    p_instr_c->_operandnumber = p_bt_obj->operand_number;
    p_instr_c->_dest_opnd_number= p_bt_obj->dest_opnd_number;
    p_instr_c->_src_opnd_number= p_bt_obj->src_opnd_number;
    p_instr_c->_src_opnd_start= p_bt_obj->src_opnd_start;
	
    if (p_bt_obj->pfx_rep)
      p_instr_c->_prefix = cREP;
    else if (p_bt_obj->pfx_repne)
      p_instr_c->_prefix = cREPNE;
    else if (p_bt_obj->pfx_lock)
      p_instr_c->_prefix = cLOCK;
    else
      p_instr_c->_prefix = cINV;  

    while (i<3){
        p_instr_c->_operand[i] = p_bt_obj->operand[i];

		if (p_bt_obj->pfx_seg && p_bt_obj->operand[i].type == BT_OP_MEM){ /*??*/
			p_instr_c->_operand[i].type = p_bt_obj->pfx_seg - BT_R_ES;
		}
		else if (p_bt_obj->operand[i].base >=BT_R_ES && p_bt_obj->operand[i].base <= BT_R_GS)
			p_instr_c->_operand[i].type = BT_OP_SEG;
		
		i++;
    }

}

ADDR decode (INSTR_CUT *p_instr_c, int disas_mode)  //disas_mode =32 or 64
{
  unsigned int p;               /* (bool) denotes end of prefixes */
  unsigned int i;               /* prefix counter */
  char *src_hex;
  unsigned char *src_ptr;

  UD bt_obj;  //will be modified, using malloc
  register UD *u = &bt_obj;
  
  u->pc = p_instr_c->_addr;
  u->dis_mode = disas_mode;
  u->vendor = BT_VENDOR_INTEL;

  /* [1] Clear the decode/output fields */
  clear_insn (u);

  /* [2] Extract Prefixes */

  // inp_next(u);

  for (i = 0, p = 0; p == 0; ++i)
  {
    if ((inp_curr (u) & 0xF0) == 0x40)
    {                           /* REX */
      if (u->dis_mode == 64)
      {
        u->pfx_rex = inp_curr (u);
        inp_next (u);
      }
      else
        p = 1;                  /* Bail out, its an inc/dec */
    }
    else
      switch (inp_curr (u))
      {
        case 0x2E:
          u->pfx_seg = BT_R_CS;
          inp_next (u);
          break;
        case 0x36:
          u->pfx_seg = BT_R_SS;
          inp_next (u);
          break;
        case 0x3E:
          u->pfx_seg = BT_R_DS;
          inp_next (u);
          break;
        case 0x26:
          u->pfx_seg = BT_R_ES;
          inp_next (u);
          break;
        case 0x64:
          u->pfx_seg = BT_R_FS;
          inp_next (u);
          break;
        case 0x65:
          u->pfx_seg = BT_R_GS;
          inp_next (u);
          break;
        case 0x66:
          u->pfx_insn = u->pfx_opr = 0x66;
          inp_next (u);
          break;
        case 0x67:
          u->pfx_adr = 0x67;
          inp_next (u);
          break;
        case 0xF0:
          u->pfx_lock = 0xF0;
          inp_next (u);
          break;
        case 0xF2:
          u->pfx_insn = u->pfx_repne = 0xF2;
          inp_next (u);
          break;
        case 0xF3:
          u->pfx_insn = u->pfx_rep = 0xF3;
          inp_next (u);
          break;
        default:
          p = 1;
      }

    /* if >= MAX_PREFIXES, disintegrate */
    if (i >= MAX_PREFIXES)
    {
      u->error = 1;
      break;
    }
  }

  /* [3] Search opcode map */

  search_map (u);

  /* [4] Set mode flags */

  if (u->dis_mode == 64)
  {                             /* set 64bit-mode flags */
    u->pfx_rex = u->pfx_rex & P_REX_MASK (u->mapen->prefix);
    u->default64 = P_DEF64 (u->mapen->prefix);
    u->error = P_INV64 (u->mapen->prefix);

    if (P_REX (u->mapen->prefix) && P_REX_W (u->pfx_rex))
      u->opr_mode = 64;
    else if (u->pfx_opr)
      u->opr_mode = 16;
    else
      u->opr_mode = (u->default64) ? 64 : 32;

    //u->adr_mode = (u->pfx_adr) ? 32 : 64;
    u->adr_mode = 32;
  }
  else if (u->dis_mode == 32)
  {                             /* set 32bit-mode flags */
    u->opr_mode = (u->pfx_opr) ? 16 : 32;
    u->adr_mode = (u->pfx_adr) ? 16 : 32;
  }
  else if (u->dis_mode == 16)
  {                             /* set 16bit-mode flags */
    u->opr_mode = (u->pfx_opr) ? 32 : 16;
    u->adr_mode = (u->pfx_adr) ? 32 : 16;
  }

  /* [5] Disassembled operands */

  disasm_operands (u);

  /* [6] Resolve mode related and other mnemonic issues */

  if (P_DEPM (u->mapen->prefix))
    u->mnemonic = resolve_mnemonic (u);

  u->br_far = 0;
  u->br_near = 0;

  if (u->mnemonic == BT_Icall || u->mnemonic == BT_Ijmp)
  {
    if (u->operand[0].size == SZ_WP)
    {
      u->operand[0].size = 16;
      u->br_far = 1;
      u->br_near = 0;
    }
    else if (u->operand[0].size == SZ_DP)
    {
      u->operand[0].size = 32;
      u->br_far = 1;
      u->br_near = 0;
    }
    else
    {
      u->br_far = 0;
      u->br_near = 1;
    }
  }
  else if (u->mnemonic == BT_I3dnow)
    u->mnemonic = map_get_3dnow (inp_curr (u));

  /* [7] Check for errors */

  if (u->error)
  {
    clear_insn (u);
    u->mapen = bt_me_invalid ();
    u->mnemonic = u->mapen->mnemonic;
  }

  /* [8] Identify the operand type*/
  //dispose_operand(u);

  /* [9] Update program counter */
  /* [10] Return the pc of next instruction */
  inp_next (u);
  imm_extend (u);

  Dis_Result_To_Ir1(u, p_instr_c);

  MESSAGE(p_instr_c->_op==BT_Iinvalid, ("Exists instruction that the disassembler doesnot support, 0x%lx.\n", p_instr_c->_addr));
  
  return u->pc;
}
