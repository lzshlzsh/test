/* ----------------------------------------------------------------------------- opcmap.c
   Copyright (c) 2006, Vivek Mohan <vivek@sig9.com> All rights reserved. See LICENSE
   ----------------------------------------------------------------------------- */

#include "dec_types.h"
#include "mnemonics.h"
#include "opcmap.h"
#include "input.h"

/* operand types - check out the intel/amd manuals */
#define Ap	{ OP_A, SZ_P 	}
#define E	{ OP_E, 0 	}
#define Eb	{ OP_E, SZ_B 	}
#define Ew	{ OP_E, SZ_W 	}
#define Ev	{ OP_E, SZ_V 	}
#define Ed	{ OP_E, SZ_D 	}
#define Ez	{ OP_E, SZ_Z 	}
#define Ex	{ OP_E, SZ_MDQ 	}
#define Ep	{ OP_E, SZ_P 	}
#define G	{ OP_G, 0 	}
#define Gb	{ OP_G, SZ_B 	}
#define Gw	{ OP_G, SZ_W 	}
#define Gv	{ OP_G, SZ_V 	}
#define Gvw	{ OP_G, SZ_MDQ 	}
#define Gd	{ OP_G, SZ_D 	}
#define Gx	{ OP_G, SZ_MDQ 	}
#define Gz	{ OP_G, SZ_Z 	}
#define M	{ OP_M, 0 	}
#define Mb	{ OP_M, SZ_B 	}
#define Mw	{ OP_M, SZ_W 	}
#define Ms	{ OP_M, SZ_W 	}
#define Md	{ OP_M, SZ_D 	}
#define Mq	{ OP_M, SZ_Q 	}
#define Mt	{ OP_M, SZ_T 	}
#define	I1	{ OP_I1, 0 	}
#define	I3	{ OP_I3, 0 	}
#define Ib	{ OP_I, SZ_B 	}
#define Iw	{ OP_I, SZ_W	}
#define Iv	{ OP_I, SZ_V	}
#define Iz	{ OP_I, SZ_Z	}
#define Jv	{ OP_J, SZ_V	}
#define Jz	{ OP_J, SZ_Z	}
#define Jb	{ OP_J, SZ_B	}
#define R	{ OP_R, SZ_RDQ	}
#define C	{ OP_C, 0	}
#define D	{ OP_D, 0	}
#define S	{ OP_S, 0	}
#define Ob	{ OP_O, SZ_B	}
#define Ow	{ OP_O, SZ_W	}
#define Ov	{ OP_O, SZ_V	}
#define V	{ OP_V, 0	}
#define W	{ OP_W, 0	}
#define Vq	{ OP_V, SZ_Q	}
#define Wq	{ OP_W, SZ_Q}
#define P	{ OP_P, 0	}
#define Q	{ OP_Q, 0	}
#define VR	{ OP_VR, 0	}
#define PR	{ OP_PR, 0	}
#define AL	{ OP_AL, 0	}
#define CL	{ OP_CL, 0	}
#define DL	{ OP_DL, 0	}
#define BL	{ OP_BL, 0	}
#define AH	{ OP_AH, 0	}
#define CH	{ OP_CH, 0	}
#define DH	{ OP_DH, 0	}
#define BH	{ OP_BH, 0	}
#define AX	{ OP_AX, 0	}
#define CX	{ OP_CX, 0	}
#define DX	{ OP_DX, 0	}
#define BX	{ OP_BX, 0	}
#define SI	{ OP_SI, 0	}
#define DI	{ OP_DI, 0	}
#define SP	{ OP_SP, 0	}
#define BP	{ OP_BP, 0	}
#define eAX	{ OP_eAX, 0	}
#define eCX	{ OP_eCX, 0	}
#define eDX	{ OP_eDX, 0	}
#define eBX	{ OP_eBX, 0	}
#define eSI	{ OP_eSI, 0	}
#define eDI	{ OP_eDI, 0	}
#define eSP	{ OP_eSP, 0	}
#define eBP	{ OP_eBP, 0	}
#define rAX	{ OP_rAX, 0	}
#define rCX	{ OP_rCX, 0	}
#define rBX	{ OP_rDX, 0	}
#define rDX	{ OP_rDX, 0	}
#define rSI	{ OP_rSI, 0	}
#define rDI	{ OP_rDI, 0	}
#define rSP	{ OP_rSP, 0	}
#define rBP	{ OP_rBP, 0	}
#define ES	{ OP_ES, 0	}
#define CS	{ OP_CS, 0	}
#define DS	{ OP_DS, 0	}
#define SS	{ OP_SS, 0	}
#define GS	{ OP_GS, 0	}
#define FS	{ OP_FS, 0	}
#define ST0	{ OP_ST0, 0	}
#define ST1	{ OP_ST1, 0	}
#define ST2	{ OP_ST2, 0	}
#define ST3	{ OP_ST3, 0	}
#define ST4	{ OP_ST4, 0	}
#define ST5	{ OP_ST5, 0	}
#define ST6	{ OP_ST6, 0	}
#define ST7	{ OP_ST7, 0	}
#define NOARG	{ 0, 0 		}
#define ALr8b	{ OP_ALr8b,0 	}
#define CLr9b	{ OP_CLr9b,0 	}
#define DLr10b	{ OP_DLr10b,0 	}
#define BLr11b	{ OP_BLr11b,0 	}
#define AHr12b	{ OP_AHr12b,0 	}
#define CHr13b	{ OP_CHr13b,0 	}
#define DHr14b	{ OP_DHr14b,0 	}
#define BHr15b	{ OP_BHr15b,0 	}
#define rAXr8	{ OP_rAXr8,0 	}
#define rCXr9	{ OP_rCXr9,0 	}
#define rDXr10	{ OP_rDXr10,0 	}
#define rBXr11	{ OP_rBXr11,0 	}
#define rSPr12	{ OP_rSPr12,0 	}
#define rBPr13	{ OP_rBPr13,0 	}
#define rSIr14	{ OP_rSIr14,0 	}
#define rDIr15	{ OP_rDIr15,0 	}

enum INSN_GROUPS
{
  GRP_80,
  GRP_81,
  GRP_82,
  GRP_83,
  GRP_8F,
  GRP_C0,
  GRP_C1,
  GRP_C6,
  GRP_C7,
  GRP_D0,
  GRP_D1,
  GRP_D2,
  GRP_D3,
  GRP_F6,
  GRP_F7,
  GRP_FE,
  GRP_FF,
  GRP_0F00,
  GRP_0F01,
  GRP_0F0D,
  GRP_0F18,
  GRP_0F71,
  GRP_0F72,
  GRP_0F73,
  GRP_0FAE,
  GRP_0FBA,
  GRP_0FB9,
  GRP_0FC7
};

/* 1 byte opcode */
MAP_ENTRY itab_1byte[0x100] = {
  /* Instruction, op1, op2, op3, Valid Prefixes */

  /* 00 */ {BT_Iadd, Eb, Gb, NOARG, Pa32 | REX (_X | _B | _R) ,1,2,0},
  /* 01 */ {BT_Iadd, Ev, Gv, NOARG, Pa32 | Po32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 02 */ {BT_Iadd, Gb, Eb, NOARG, Pa32 | REX (_X | _B | _R) ,1,2,0},
  /* 03 */ {BT_Iadd, Gv, Ev, NOARG, Pa32 | Po32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 04 */ {BT_Iadd, AL, Ib, NOARG, Pnone,1,2,0},
  /* 05 */ {BT_Iadd, rAX, Iz, NOARG, Po32 | REX (_W) ,1,2,0},
  /* 06 */ {BT_Ipush, ES, NOARG, NOARG, Pinv64,0,1,0},
  /* 07 */ {BT_Ipop, ES, NOARG, NOARG, Pinv64,1,0,INVAL},
  /* 08 */ {BT_Ior, Eb, Gb, NOARG, Pa32 | REX (_X | _B | _R) ,1,2,0},
  /* 09 */ {BT_Ior, Ev, Gv, NOARG, Pa32 | Po32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 0A */ {BT_Ior, Gb, Eb, NOARG, Pa32 | REX (_X | _B | _R) ,1,2,0},
  /* 0B */ {BT_Ior, Gv, Ev, NOARG, Pa32 | Po32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 0C */ {BT_Ior, AL, Ib, NOARG, Pnone,1,2,0},
  /* 0D */ {BT_Ior, rAX, Iz, NOARG, Po32 | REX (_W) ,1,2,0},
  /* 0E */ {BT_Ipush, CS, NOARG, NOARG, Pinv64,0,1,0},
  /* 0F */ {BT_Iesc, NOARG, NOARG, NOARG, Pnone,0,0,INVAL},
  /* 10 */ {BT_Iadc, Eb, Gb, NOARG, Pa32 | REX (_X | _B | _R) ,1,2,0},
  /* 11 */ {BT_Iadc, Ev, Gv, NOARG, Pa32 | Po32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 12 */ {BT_Iadc, Gb, Eb, NOARG, Pa32 | REX (_X | _B | _R) ,1,2,0},
  /* 13 */ {BT_Iadc, Gv, Ev, NOARG, Pa32 | Po32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 14 */ {BT_Iadc, AL, Ib, NOARG, Pnone,1,2,0},
  /* 15 */ {BT_Iadc, rAX, Iz, NOARG, Po32 | REX (_W) ,1,2,0},
  /* 16 */ {BT_Ipush, SS, NOARG, NOARG, Pinv64,0,1,0},
  /* 17 */ {BT_Ipop, SS, NOARG, NOARG, Pinv64,1,0,INVAL},
  /* 18 */ {BT_Isbb, Eb, Gb, NOARG, Pa32 | REX (_X | _B | _R) ,1,2,0},
  /* 19 */ {BT_Isbb, Ev, Gv, NOARG, Pa32 | Po32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 1A */ {BT_Isbb, Gb, Eb, NOARG, Pa32 | REX (_X | _B | _R) ,1,2,0},
  /* 1B */ {BT_Isbb, Gv, Ev, NOARG, Pa32 | Po32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 1C */ {BT_Isbb, AL, Ib, NOARG, Pnone,1,2,0},
  /* 1D */ {BT_Isbb, rAX, Iz, NOARG, Po32 | REX (_W) ,1,2,0},
  /* 1E */ {BT_Ipush, DS, NOARG, NOARG, Pinv64,0,1,0},
  /* 1F */ {BT_Ipop, DS, NOARG, NOARG, Pinv64,1,0,INVAL},
  /* 20 */ {BT_Iand, Eb, Gb, NOARG, Pa32 | REX (_X | _B | _R) ,1,2,0},
  /* 21 */ {BT_Iand, Ev, Gv, NOARG, Pa32 | Po32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 22 */ {BT_Iand, Gb, Eb, NOARG, Pa32 | REX (_X | _B | _R) ,1,2,0},
  /* 23 */ {BT_Iand, Gv, Ev, NOARG, Pa32 | Po32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 24 */ {BT_Iand, AL, Ib, NOARG, Pnone,1,2,0},
  /* 25 */ {BT_Iand, rAX, Iz, NOARG, Po32 | REX (_W) ,1,2,0},
  /* 26 */ {BT_Ies, ES, NOARG, NOARG, Pnone,0,1,0},
  /* 27 */ {BT_Idaa, AL, NOARG, NOARG, Pinv64,1,1,0},
  /* 28 */ {BT_Isub, Eb, Gb, NOARG, Pa32 | REX (_X | _B | _R) ,1,2,0},
  /* 29 */ {BT_Isub, Ev, Gv, NOARG, Pa32 | Po32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 2A */ {BT_Isub, Gb, Eb, NOARG, Pa32 | REX (_X | _B | _R) ,1,2,0},
  /* 2B */ {BT_Isub, Gv, Ev, NOARG, Pa32 | Po32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 2C */ {BT_Isub, AL, Ib, NOARG, Pnone,1,2,0},
  /* 2D */ {BT_Isub, rAX, Iz, NOARG, Po32 | REX (_W) ,1,2,0},
  /* 2E */ {BT_Ics, CS, NOARG, NOARG, Pnone,0,1,0},
  /* 2F */ {BT_Idas, AL, NOARG, NOARG, Pinv64,1,1,0},
  /* 30 */ {BT_Ixor, Eb, Gb, NOARG, Pa32 | REX (_X | _B | _R) ,1,2,0},
  /* 31 */ {BT_Ixor, Ev, Gv, NOARG, Pa32 | Po32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 32 */ {BT_Ixor, Gb, Eb, NOARG, Pa32 | REX (_X | _B | _R) ,1,2,0},
  /* 33 */ {BT_Ixor, Gv, Ev, NOARG, Pa32 | Po32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 34 */ {BT_Ixor, AL, Ib, NOARG, Pnone,1,2,0},
  /* 35 */ {BT_Ixor, rAX, Iz, NOARG, Po32 | REX (_W) ,1,2,0},
  /* 36 */ {BT_Iss, ES, NOARG, NOARG, Pinv64,0,1,0},
  /* 37 */ {BT_Iaaa, AL, AH, NOARG, Pinv64,2,2,0},
  /* 38 */ {BT_Icmp, Eb, Gb, NOARG, Pa32 | REX (_X | _B | _R) ,0,2,0},
  /* 39 */ {BT_Icmp, Ev, Gv, NOARG, Pa32 | Po32 | REX (_W | _R | _X | _B) ,0,2,0},
  /* 3A */ {BT_Icmp, Gb, Eb, NOARG, Pa32 | REX (_X | _B | _R) ,0,2,0},
  /* 3B */ {BT_Icmp, Gv, Ev, NOARG, Pa32 | Po32 | REX (_W | _R | _X | _B) ,0,2,0},
  /* 3C */ {BT_Icmp, AL, Ib, NOARG, Pnone,0,2,0},
  /* 3D */ {BT_Icmp, rAX, Iz, NOARG, Po32 | REX (_W) ,0,2,0},
  /* 3E */ {BT_Ids, ES, NOARG, NOARG, Pnone,0,1,0},
  /* 3F */ {BT_Iaas, AL,AH, NOARG, Pinv64,2,2,0},
  /* 40 */ {BT_Iinc, eAX, NOARG, NOARG, Po32,1,1,0},
  /* 41 */ {BT_Iinc, eCX, NOARG, NOARG, Po32,1,1,0},
  /* 42 */ {BT_Iinc, eDX, NOARG, NOARG, Po32,1,1,0},
  /* 43 */ {BT_Iinc, eBX, NOARG, NOARG, Po32,1,1,0},
  /* 44 */ {BT_Iinc, eSP, NOARG, NOARG, Po32,1,1,0},
  /* 45 */ {BT_Iinc, eBP, NOARG, NOARG, Po32,1,1,0},
  /* 46 */ {BT_Iinc, eSI, NOARG, NOARG, Po32,1,1,0},
  /* 47 */ {BT_Iinc, eDI, NOARG, NOARG, Po32,1,1,0},
  /* 48 */ {BT_Idec, eAX, NOARG, NOARG, Po32,1,1,0},
  /* 49 */ {BT_Idec, eCX, NOARG, NOARG, Po32,1,1,0},
  /* 4A */ {BT_Idec, eDX, NOARG, NOARG, Po32,1,1,0},
  /* 4B */ {BT_Idec, eBX, NOARG, NOARG, Po32,1,1,0},
  /* 4C */ {BT_Idec, eSP, NOARG, NOARG, Po32,1,1,0},
  /* 4D */ {BT_Idec, eBP, NOARG, NOARG, Po32,1,1,0},
  /* 4E */ {BT_Idec, eSI, NOARG, NOARG, Po32,1,1,0},
  /* 4F */ {BT_Idec, eDI, NOARG, NOARG, Po32,1,1,0},
  /* 50 */ {BT_Ipush, rAXr8, NOARG, NOARG, Po32 | Pdef64 | REX (_B),0,1,0},
  /* 51 */ {BT_Ipush, rCXr9, NOARG, NOARG, Po32 | Pdef64 | REX (_B) ,0,1,0},
  /* 52 */ {BT_Ipush, rDXr10, NOARG, NOARG, Po32 | Pdef64 | REX (_B) ,0,1,0},
  /* 53 */ {BT_Ipush, rBXr11, NOARG, NOARG, Po32 | Pdef64 | REX (_B) ,0,1,0},
  /* 54 */ {BT_Ipush, rSPr12, NOARG, NOARG, Po32 | Pdef64 | REX (_B) ,0,1,0},
  /* 55 */ {BT_Ipush, rBPr13, NOARG, NOARG, Po32 | Pdef64 | REX (_B) ,0,1,0},
  /* 56 */ {BT_Ipush, rSIr14, NOARG, NOARG, Po32 | Pdef64 | REX (_B) ,0,1,0},
  /* 57 */ {BT_Ipush, rDIr15, NOARG, NOARG, Po32 | Pdef64 | REX (_B) ,0,1,0},
  /* 58 */ {BT_Ipop, rAXr8, NOARG, NOARG, Po32 | Pdef64 | REX (_B),1,0,INVAL},
  /* 59 */ {BT_Ipop, rCXr9, NOARG, NOARG, Po32 | Pdef64 | REX (_B) ,1,0, INVAL },
  /* 5A */ {BT_Ipop, rDXr10, NOARG, NOARG, Po32 | Pdef64 | REX (_B) ,1,0, INVAL },
  /* 5B */ {BT_Ipop, rBXr11, NOARG, NOARG, Po32 | Pdef64 | REX (_B) ,1,0, INVAL },
  /* 5C */ {BT_Ipop, rSPr12, NOARG, NOARG, Po32 | Pdef64 | REX (_B) ,1,0, INVAL },
  /* 5D */ {BT_Ipop, rBPr13, NOARG, NOARG, Po32 | Pdef64 | REX (_B) ,1,0, INVAL },
  /* 5E */ {BT_Ipop, rSIr14, NOARG, NOARG, Po32 | Pdef64 | REX (_B) ,1,0, INVAL },
  /* 5F */ {BT_Ipop, rDIr15, NOARG, NOARG, Po32 | Pdef64 | REX (_B) ,1,0, INVAL },
  /* 60 */ {BT_Ipusha, NOARG, NOARG, NOARG, Po32 | Pinv64 | PdepM,0,ALLINTR,0},
  /* 61 */ {BT_Ipopa, NOARG, NOARG, NOARG, Po32 | Pinv64 | PdepM, ALLINTR,0, INVAL },
  /* 62 */ {BT_Ibound, Gv, M, NOARG, Po32 | Pa32 | Pinv64,0,2,0},
  /* 63 */ {BT_Iarpl, Ew, Gw, NOARG, Pa32 | Pinv64,0,2,0},
  /* 64 */ {BT_Ifs, ES, NOARG, NOARG, Pnone,0,1,0},
  /* 65 */ {BT_Igs, GS, NOARG, NOARG, Pnone,0,1,0},
  /* 66 */ {BT_Ia32, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 67 */ {BT_Io32, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 68 */ {BT_Ipush, Iz, NOARG, NOARG, Pc1 | Po32,0,1,0},
  /* 69 */ {BT_Iimul, Gv, Ev, Iz, Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,1},
  /* 6A */ {BT_Ipush, Ib, NOARG, NOARG, Pnone,0,1,0},
  /* 6B */ {BT_Iimul, Gv, Ev, Ib, Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,1},
  /* 6C */ {BT_Iinsb, NOARG, NOARG, NOARG, Pnone, 0,0,INVAL },
  /* 6D */ {BT_Iinsw, NOARG, NOARG, NOARG, Po32 | PdepM, 0,0,INVAL },
  /* 6E */ {BT_Ioutsb, NOARG, NOARG, NOARG, Pnone, 0,0,INVAL },
  /* 6F */ {BT_Ioutsw, NOARG, NOARG, NOARG, Po32 | PdepM, 0,0,INVAL },
  /* 70 */ {BT_Ijo, Jb, NOARG, NOARG, Pnone,0,1,0},
  /* 71 */ {BT_Ijno, Jb, NOARG, NOARG, Pnone,0,1,0},
  /* 72 */ {BT_Ijb, Jb, NOARG, NOARG, Pnone,0,1,0},
  /* 73 */ {BT_Ijae, Jb, NOARG, NOARG, Pnone,0,1,0},
  /* 74 */ {BT_Ijz, Jb, NOARG, NOARG, Pnone,0,1,0},
  /* 75 */ {BT_Ijnz, Jb, NOARG, NOARG, Pnone,0,1,0},
  /* 76 */ {BT_Ijbe, Jb, NOARG, NOARG, Pnone,0,1,0},
  /* 77 */ {BT_Ija, Jb, NOARG, NOARG, Pnone,0,1,0},
  /* 78 */ {BT_Ijs, Jb, NOARG, NOARG, Pnone,0,1,0},
  /* 79 */ {BT_Ijns, Jb, NOARG, NOARG, Pnone,0,1,0},
  /* 7A */ {BT_Ijp, Jb, NOARG, NOARG, Pnone,0,1,0},
  /* 7B */ {BT_Ijnp, Jb, NOARG, NOARG, Pnone,0,1,0},
  /* 7C */ {BT_Ijl, Jb, NOARG, NOARG, Pnone,0,1,0},
  /* 7D */ {BT_Ijge, Jb, NOARG, NOARG, Pnone,0,1,0},
  /* 7E */ {BT_Ijle, Jb, NOARG, NOARG, Pnone,0,1,0},
  /* 7F */ {BT_Ijg, Jb, NOARG, NOARG, Pnone,0,1,0},
  /* 80 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_80,INVAL, INVAL, INVAL },
  /* 81 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_81,INVAL, INVAL, INVAL },
  /* 82 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_82,INVAL, INVAL, INVAL },
  /* 83 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_83,INVAL, INVAL, INVAL },
  /* 84 */ {BT_Itest, Eb, Gb, NOARG, Pa32 | REX (_R | _X | _B) ,0,2,0},
  /* 85 */ {BT_Itest, Ev, Gv, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,0,2,0},
  /* 86 */ {BT_Ixchg, Eb, Gb, NOARG, Pa32 | REX (_R | _X | _B) ,2,2,0},
  /* 87 */ {BT_Ixchg, Ev, Gv, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,2,2,0},
  /* 88 */ {BT_Imov, Eb, Gb, NOARG, Pa32 | REX (_R | _X | _B) ,1,1,1},
  /* 89 */ {BT_Imov, Ev, Gv, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,1,1},
  /* 8A */ {BT_Imov, Gb, Eb, NOARG, Pa32 | REX (_R | _X | _B) ,1,1,1},
  /* 8B */ {BT_Imov, Gv, Ev, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,1,1},
  /* 8C */ {BT_Imov, Ev, S, NOARG, Po32 | Pa32 | REX (_R | _X | _B) ,1,1,1},
  /* 8D */ {BT_Ilea, Gv, M, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,1,1},
  /* 8E */ {BT_Imov, S, Ev, NOARG, Po32 | Pa32 | REX (_R | _X | _B) ,1,1,1},
  /* 8F */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_8F,INVAL, INVAL, INVAL },
  /* 90 */ {BT_Ixchg, rAXr8, rAX, NOARG, Po32 | REX (_W | _B) ,2,2,0},
  /* 91 */ {BT_Ixchg, rCXr9, rAX, NOARG, Po32 | REX (_W | _B) ,2,2,0},
  /* 92 */ {BT_Ixchg, rDXr10, rAX, NOARG, Po32 | REX (_W | _B) ,2,2,0},
  /* 93 */ {BT_Ixchg, rBXr11, rAX, NOARG, Po32 | REX (_W | _B) ,2,2,0},
  /* 94 */ {BT_Ixchg, rSPr12, rAX, NOARG, Po32 | REX (_W | _B) ,2,2,0},
  /* 95 */ {BT_Ixchg, rBPr13, rAX, NOARG, Po32 | REX (_W | _B) ,2,2,0},
  /* 96 */ {BT_Ixchg, rSIr14, rAX, NOARG, Po32 | REX (_W | _B) ,2,2,0},
  /* 97 */ {BT_Ixchg, rDIr15, rAX, NOARG, Po32 | REX (_W | _B) ,2,2,0},
  /* 98 */ {BT_Icbw, AX, AL, NOARG, Po32 | PdepM | REX (_W),1,1,1},
  /* 99 */ {BT_Icwd, eAX, AX, NOARG, Po32 | PdepM | REX (_W),1,1,1},
  /* 9A */ {BT_Ilcall, Ap, NOARG, NOARG, Pc1 | Po32 | Pinv64,0,1,0},
  /* 9B */ {BT_Iwait, NOARG, NOARG, NOARG, Pnone,0,0,INVAL},
  /* 9C */ {BT_Ipushfw, NOARG, NOARG, NOARG, Po32 | PdepM | Pdef64,0,0,INVAL},
  /* 9D */ {BT_Ipopfw, NOARG, NOARG, NOARG, Po32 | PdepM | Pdef64,0,0,INVAL},
  /* 9E */ {BT_Isahf, AH, NOARG, NOARG, Pnone,0,1,0},
  /* 9F */ {BT_Ilahf, AH, NOARG, NOARG, Pnone,1,0,INVAL},
  /* A0 */ {BT_Imov, AL, Ob, NOARG, Pnone,1,1,1},
  /* A1 */ {BT_Imov, rAX, Ov, NOARG, Po32 | Pa32 | REX (_W) ,1,1,1},
  /* A2 */ {BT_Imov, Ob, AL, NOARG, Pnone,1,1,1},
  /* A3 */ {BT_Imov, Ov, rAX, NOARG, Po32 | Pa32 | REX (_W) ,1,1,1},
  /* A4 */ {BT_Imovsb, NOARG, NOARG, NOARG, Pnone, 0,0,INVAL },
  /* A5 */ {BT_Imovsw, NOARG, NOARG, NOARG, Po32 | PdepM | REX (_W) ,0,0,INVAL},
  /* A6 */ {BT_Icmpsb, NOARG, NOARG, NOARG, Pnone,0,0,INVAL},
  /* A7 */ {BT_Icmpsw, NOARG, NOARG, NOARG, Po32 | PdepM | REX (_W) ,0,0,INVAL},
  /* A8 */ {BT_Itest, AL, Ib, NOARG, Pnone,0,2,0},
  /* A9 */ {BT_Itest, rAX, Iz, NOARG, Po32 | REX (_W) ,0,2,0},
  /* AA */ {BT_Istosb, AL, NOARG, NOARG, Pnone,0,1,0},
  /* AB */ {BT_Istosw, eAX, NOARG, NOARG,Po32 | PdepM | REX (_W),0,1,0},
  /* AC */ {BT_Ilodsb, AL, NOARG, NOARG, Pnone,0,1,0},
  /* AD */ {BT_Ilodsw, eAX, NOARG, NOARG, Po32 | PdepM | REX (_W),0,1,0},
  /* AE */ {BT_Iscasb, AL, NOARG, NOARG, Pnone,0,1,0},
  /* AF */ {BT_Iscasw, eAX, NOARG, NOARG, Po32 | PdepM | REX (_W),0,1,0},
  /* B0 */ {BT_Imov, ALr8b, Ib, NOARG, REX (_B) ,1,1,1},
  /* B1 */ {BT_Imov, CLr9b, Ib, NOARG, REX (_B) ,1,1,1},
  /* B2 */ {BT_Imov, DLr10b, Ib, NOARG, REX (_B) ,1,1,1},
  /* B3 */ {BT_Imov, BLr11b, Ib, NOARG, REX (_B) ,1,1,1},
  /* B4 */ {BT_Imov, AHr12b, Ib, NOARG, REX (_B) ,1,1,1},
  /* B5 */ {BT_Imov, CHr13b, Ib, NOARG, REX (_B) ,1,1,1},
  /* B6 */ {BT_Imov, DHr14b, Ib, NOARG, REX (_B) ,1,1,1},
  /* B7 */ {BT_Imov, BHr15b, Ib, NOARG, REX (_B) ,1,1,1},
  /* B8 */ {BT_Imov, rAXr8, Iv, NOARG, Po32 | REX (_W | _B) ,1,1,1},
  /* B9 */ {BT_Imov, rCXr9, Iv, NOARG, Po32 | REX (_W | _B) ,1,1,1},
  /* BA */ {BT_Imov, rDXr10, Iv, NOARG, Po32 | REX (_W | _B) ,1,1,1},
  /* BB */ {BT_Imov, rBXr11, Iv, NOARG, Po32 | REX (_W | _B) ,1,1,1},
  /* BC */ {BT_Imov, rSPr12, Iv, NOARG, Po32 | REX (_W | _B) ,1,1,1},
  /* BD */ {BT_Imov, rBPr13, Iv, NOARG, Po32 | REX (_W | _B) ,1,1,1},
  /* BE */ {BT_Imov, rSIr14, Iv, NOARG, Po32 | REX (_W | _B) ,1,1,1},
  /* BF */ {BT_Imov, rDIr15, Iv, NOARG, Po32 | REX (_W | _B) ,1,1,1},
  /* C0 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_C0,INVAL, INVAL, INVAL },
  /* C1 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_C1,INVAL, INVAL, INVAL },
  /* C2 */ {BT_Iret, Iw, NOARG, NOARG, Pnone,0,1,0},
  /* C3 */ {BT_Iret, NOARG, NOARG, NOARG, Pnone,0,0,0},
  /* C4 */ {BT_Iles, ES, Gv, M,  Po32 | Pa32 | Pinv64,2,1,2},
  /* C5 */ {BT_Ilds, DS, Gv, M,  Po32 | Pa32 | Pinv64,2,1,2},
  /* C6 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_C6,INVAL, INVAL, INVAL },
  /* C7 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_C7,INVAL, INVAL, INVAL },
  /* C8 */ {BT_Ienter, Iw, Ib, NOARG, Pnone | Pdef64,0,2,0},
  /* C9 */ {BT_Ileave, NOARG, NOARG, NOARG, Pnone,0,0,INVAL},
  /* CA */ {BT_Iretf, Iw, NOARG, NOARG, Pnone,0,1,0},
  /* CB */ {BT_Iretf, NOARG, NOARG, NOARG, Pnone,0,0,INVAL},
  /* CC */ {BT_Iint3, NOARG, NOARG, NOARG, Pnone,ALLINTR,ALLINTR,INVAL},
  /* CD */ {BT_Iint, Ib, NOARG, NOARG, Pnone,ALLINTR,ALLINTR,0},
  /* CE */ {BT_Iinto, NOARG, NOARG, NOARG, Pinv64,0,0,INVAL},
  /* CF */ {BT_Iiretw, NOARG, NOARG, NOARG, Po32 | PdepM | REX (_W),0,0,INVAL},
  /* D0 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_D0,INVAL, INVAL, INVAL },
  /* D1 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_D1,INVAL, INVAL, INVAL },
  /* D2 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_D2,INVAL, INVAL, INVAL },
  /* D3 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_D3,INVAL, INVAL, INVAL },
  /* D4 */ {BT_Iaam, AX, Ib,  NOARG, Pinv64,1,1,1},
  /* D5 */ {BT_Iaad, AX, Ib,  NOARG, Pinv64,1,1,1},
  /* D6 */ {BT_Isalc, NOARG, NOARG, NOARG, Pinv64,INVAL, INVAL, INVAL },
  /* D7 */ {BT_Ixlatb, AL, eBX, NOARG, REX (_W),1,2,0},
  /* D8 */ {BT_Ix87, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* D9 */ {BT_Ix87, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* DA */ {BT_Ix87, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* DB */ {BT_Ix87, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* DC */ {BT_Ix87, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* DD */ {BT_Ix87, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* DE */ {BT_Ix87, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* DF */ {BT_Ix87, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* E0 */ {BT_Iloopnz, rCX, Jb, NOARG, Pnone,1,2,0},
  /* E1 */ {BT_Iloope, rCX, Jb, NOARG, Pnone,1,2,0},
  /* E2 */ {BT_Iloop, rCX, Jb, NOARG, Pdef64,1,2,0},
  /* E3 */ {BT_Ijcxz, rCX, Jb, NOARG, Pa32 | PdepM,0,2,0},
  /* E4 */ {BT_Iin, AL, Ib, NOARG, Pnone,1,1,1},
  /* E5 */ {BT_Iin, eAX, Ib, NOARG, Pnone | Po32,1,1,1},
  /* E6 */ {BT_Iout, Ib, AL, NOARG, Pnone,1,1,1},
  /* E7 */ {BT_Iout, Ib, eAX, NOARG, Po32 | Pnone,1,1,1},
  /* E8 */ {BT_Icall, Jz, NOARG, NOARG, Po32 | Pdef64,0,1,0},
  /* E9 */ {BT_Ijmp, Jz, NOARG, NOARG, Po32 | Pdef64,0,1,0},
  /* EA */ {BT_Iljmp, Ap, NOARG, NOARG, Pinv64,0,1,0},
  /* EB */ {BT_Ijmp, Jb, NOARG, NOARG, Pnone,0,1,0},
  /* EC */ {BT_Iin, AL, DX, NOARG, Pnone,1,1,1},
  /* ED */ {BT_Iin, eAX, DX, NOARG, Po32 | Pnone,1,1,1},
  /* EE */ {BT_Iout, DX, AL, NOARG, Pnone,1,1,1},
  /* EF */ {BT_Iout, DX, eAX, NOARG, Po32 | Pnone,1,1,1},
  /* F0 */ {BT_Ilock, NOARG, NOARG, NOARG, Pnone,0,0, INVAL },
  /* F1 */ {BT_Iint1, NOARG, NOARG, NOARG, Pnone,0,0, INVAL },
  /* F2 */ {BT_Irepne, NOARG, NOARG, NOARG, Pnone,0,0, INVAL },
  /* F3 */ {BT_Irep, NOARG, NOARG, NOARG, Pnone,0,0, INVAL },
  /* F4 */ {BT_Ihlt, NOARG, NOARG, NOARG, Pnone,0,0, INVAL },
  /* F5 */ {BT_Icmc, NOARG, NOARG, NOARG, Pnone,0,0, INVAL },
  /* F6 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_F6,INVAL, INVAL, INVAL },
  /* F7 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_F7,INVAL, INVAL, INVAL },
  /* F8 */ {BT_Iclc, NOARG, NOARG, NOARG, Pnone,0,0, INVAL },
  /* F9 */ {BT_Istc, NOARG, NOARG, NOARG, Pnone,0,0, INVAL },
  /* FA */ {BT_Icli, NOARG, NOARG, NOARG, Pnone,0,0, INVAL },
  /* FB */ {BT_Isti, NOARG, NOARG, NOARG, Pnone,0,0, INVAL },
  /* FC */ {BT_Icld, NOARG, NOARG, NOARG, Pnone,0,0, INVAL },
  /* FD */ {BT_Istd, NOARG, NOARG, NOARG, Pnone,0,0, INVAL },
  /* FE */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_FE,INVAL, INVAL, INVAL },
  /* FF */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_FF,INVAL, INVAL, INVAL }

};

/* 2byte no-prefix opcodes */
MAP_ENTRY itab_2byte[0x100] = {
  /* 00 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_0F00,INVAL, INVAL, INVAL },
  /* 01 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_0F01,INVAL, INVAL, INVAL },
  /* 02 */ {BT_Ilar, Gv, Ew, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,1,1},
  /* 03 */ {BT_Ilsl, Gv, Ew, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,1,1},
  /* 04 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 05 */ {BT_Isyscall, NOARG, NOARG, NOARG, Pnone,ALLINTR,ALLINTR, INVAL},
  /* 06 */ {BT_Iclts, NOARG, NOARG, NOARG, Pnone,0,0, INVAL },
  /* 07 */ {BT_Isysret, NOARG, NOARG, NOARG, Pnone,0,0, INVAL },
  /* 08 */ {BT_Iinvd, NOARG, NOARG, NOARG, Pnone,0,0, INVAL },
  /* 09 */ {BT_Iwbinvd, NOARG, NOARG, NOARG, Pnone,0,0, INVAL },
  /* 0A */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,0,0, INVAL },
  /* 0B */ {BT_Iud2, NOARG, NOARG, NOARG, Pnone,0,0, INVAL },
  /* 0C */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 0D */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_0F0D,INVAL, INVAL, INVAL },
  /* 0E */ {BT_Ifemms, NOARG, NOARG, NOARG, Pnone,0,0, INVAL },
  /* 0F */ {BT_I3dnow, NOARG, NOARG, NOARG, Pnone,0,0, INVAL },
  /* 10 */ {BT_Imovups, V, W, NOARG, Pa32 | REX (_R | _X | _B) ,1,1,1},
  /* 11 */ {BT_Imovups, W, V, NOARG, Pa32 | REX (_R | _X | _B) ,1,1,1},
  /* 12 */ {BT_Imovlps, V, W, NOARG, Pa32 | REX (_R | _X | _B) ,1,1,1},
  /* 13 */ {BT_Imovlps, M, V, NOARG, Pa32 | REX (_R | _X | _B) ,1,1,1},
  /* 14 */ {BT_Iunpcklps, V, W, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 15 */ {BT_Iunpckhps, V, W, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 16 */ {BT_Imovhps, V, W, NOARG, Pa32 | REX (_R | _X | _B) ,1,1,1},
  /* 17 */ {BT_Imovhps, M, V, NOARG, Pa32 | REX (_R | _X | _B) ,1,1,1},
  /* 18 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_0F18,INVAL, INVAL, INVAL },
  /* 19 */ {BT_Inop, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,0,1,0},
  /* 1A */ {BT_Inop, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,0,1,0},
  /* 1B */ {BT_Inop, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,0,1,0},
  /* 1C */ {BT_Inop, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,0,1,0},
  /* 1D */ {BT_Inop, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,0,1,0},
  /* 1E */ {BT_Inop, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,0,1,0},
  /* 1F */ {BT_Inop, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,0,1,0},
  /* 20 */ {BT_Imov, R, C, NOARG, REX (_R) ,1,1,1},
  /* 21 */ {BT_Imov, R, D, NOARG, REX (_R) ,1,1,1},
  /* 22 */ {BT_Imov, C, R, NOARG, REX (_R) ,1,1,1},
  /* 23 */ {BT_Imov, D, R, NOARG, REX (_R) ,1,1,1},
  /* 24 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 25 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 26 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 27 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 28 */ {BT_Imovaps, V, W, NOARG, Pa32 | REX (_R | _X | _B) ,1,1,1},
  /* 29 */ {BT_Imovaps, W, V, NOARG, Pa32 | REX (_R | _X | _B) ,1,1,1},
  /* 2A */ {BT_Icvtpi2ps, V, Q, NOARG, Pa32 | REX (_R | _X | _B) ,1,1,1},
  /* 2B */ {BT_Imovntps, M, V, NOARG, Pa32 | REX (_R | _X | _B) ,1,1,1},
  /* 2C */ {BT_Icvttps2pi, P, W, NOARG, Pa32 | REX (_R | _X | _B) ,1,1,1},
  /* 2D */ {BT_Icvtps2pi, P, W, NOARG, Pa32 | REX (_R | _X | _B) ,1,1,1},
  /* 2E */ {BT_Iucomiss, V, W, NOARG, Pa32 | REX (_R | _X | _B) ,0,2,0},
  /* 2F */ {BT_Icomiss, V, W, NOARG, Pa32 | REX (_R | _X | _B) ,0,2,0},
  /* 30 */ {BT_Iwrmsr, eDX, eAX, NOARG, Pnone,0,2,0},
  /* 31 */ {BT_Irdtsc, eDX, eAX, NOARG, Pnone,2,0,INVAL},
  /* 32 */ {BT_Irdmsr, eDX, eAX, NOARG, Pnone,2,0,INVAL},
  /* 33 */ {BT_Irdpmc, eDX, eAX, NOARG, Pnone,2,0,INVAL},
  /* 34 */ {BT_Isysenter, NOARG, NOARG, NOARG, Pinv64,0,0,INVAL},
  /* 35 */ {BT_Isysexit, NOARG, NOARG, NOARG, Pinv64,0,0,INVAL},
  /* 36 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 37 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 38 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 39 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 3A */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 3B */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 3C */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 3D */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 3E */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 3F */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 40 */ {BT_Icmovo, Gv, Ev, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 41 */ {BT_Icmovno, Gv, Ev, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 42 */ {BT_Icmovb, Gv, Ev, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 43 */ {BT_Icmovae, Gv, Ev, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 44 */ {BT_Icmovz, Gv, Ev, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 45 */ {BT_Icmovnz, Gv, Ev, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 46 */ {BT_Icmovbe, Gv, Ev, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 47 */ {BT_Icmova, Gv, Ev, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 48 */ {BT_Icmovs, Gv, Ev, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 49 */ {BT_Icmovns, Gv, Ev, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 4A */ {BT_Icmovp, Gv, Ev, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 4B */ {BT_Icmovnp, Gv, Ev, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 4C */ {BT_Icmovl, Gv, Ev, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 4D */ {BT_Icmovge, Gv, Ev, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 4E */ {BT_Icmovle, Gv, Ev, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 4F */ {BT_Icmovg, Gv, Ev, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* 50 */ {BT_Imovmskps, Gd, VR, NOARG, Po32 | REX (_W | _R | _B) ,1,1,1},
  /* 51 */ {BT_Isqrtps, V, W, NOARG, Pa32 | REX (_R | _X | _B) ,1,1,1},
  /* 52 */ {BT_Irsqrtps, V, W, NOARG, Pa32 | REX (_R | _X | _B) ,1,1,1},
  /* 53 */ {BT_Ircpps, V, W, NOARG, Pa32 | REX (_R | _X | _B) ,1,1,1},
  /* 54 */ {BT_Iandps, V, W, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 55 */ {BT_Iandnps, V, W, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 56 */ {BT_Iorps, V, W, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 57 */ {BT_Ixorps, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* 58 */ {BT_Iaddps, V, W, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 59 */ {BT_Imulps, V, W, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 5A */ {BT_Icvtps2pd, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,1,1},
  /* 5B */ {BT_Icvtdq2ps, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,1,1},
  /* 5C */ {BT_Isubps, V, W, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 5D */ {BT_Iminps, V, W, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 5E */ {BT_Idivps, V, W, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 5F */ {BT_Imaxps, V, W, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 60 */ {BT_Ipunpcklbw, P, Q, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 61 */ {BT_Ipunpcklwd, P, Q, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 62 */ {BT_Ipunpckldq, P, Q, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 63 */ {BT_Ipacksswb, P, Q, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 64 */ {BT_Ipcmpgtb, P, Q, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 65 */ {BT_Ipcmpgtw, P, Q, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 66 */ {BT_Ipcmpgtd, P, Q, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 67 */ {BT_Ipackuswb, P, Q, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 68 */ {BT_Ipunpckhbw, P, Q, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 69 */ {BT_Ipunpckhwd, P, Q, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 6A */ {BT_Ipunpckhdq, P, Q, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 6B */ {BT_Ipackssdw, P, Q, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 6C */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 6D */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 6E */ {BT_Imovd, P, Ex, NOARG, Pc2 | Pa32 | REX (_R | _X | _B) ,1,1,1},
  /* 6F */ {BT_Imovq, P, Q, NOARG, Pa32 | REX (_R | _X | _B) ,1,1,1},
  /* 70 */ {BT_Ipshufw, P, Q, Ib, Pa32 | REX (_R | _X | _B),1,2,1},
  /* 71 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_0F71,INVAL, INVAL, INVAL },
  /* 72 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_0F72,INVAL, INVAL, INVAL },
  /* 73 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_0F73,INVAL, INVAL, INVAL },
  /* 74 */ {BT_Ipcmpeqb, P, Q, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 75 */ {BT_Ipcmpeqw, P, Q, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 76 */ {BT_Ipcmpeqd, P, Q, NOARG, Pa32 | REX (_R | _X | _B) ,1,2,0},
  /* 77 */ {BT_Iemms, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 78 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 79 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 7A */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 7B */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 7C */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 7D */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* 7E */ {BT_Imovd, Ex, P, NOARG, Pc1 | Pa32 | REX (_R | _X | _B),1,1,1},
  /* 7F */ {BT_Imovq, Q, P, NOARG, Pa32 | REX (_R | _X | _B),1,1,1},
  /* 80 */ {BT_Ijo, Jz, NOARG, NOARG, Pc1 | Po32 | Pdef64,0,1,0},
  /* 81 */ {BT_Ijno, Jz, NOARG, NOARG, Pc1 | Po32 | Pdef64,0,1,0},
  /* 82 */ {BT_Ijb, Jz, NOARG, NOARG, Pc1 | Po32 | Pdef64,0,1,0},
  /* 83 */ {BT_Ijae, Jz, NOARG, NOARG, Pc1 | Po32 | Pdef64,0,1,0},
  /* 84 */ {BT_Ijz, Jz, NOARG, NOARG, Pc1 | Po32 | Pdef64,0,1,0},
  /* 85 */ {BT_Ijnz, Jz, NOARG, NOARG, Pc1 | Po32 | Pdef64,0,1,0},
  /* 86 */ {BT_Ijbe, Jz, NOARG, NOARG, Pc1 | Po32 | Pdef64,0,1,0},
  /* 87 */ {BT_Ija, Jz, NOARG, NOARG, Pc1 | Po32 | Pdef64,0,1,0},
  /* 88 */ {BT_Ijs, Jz, NOARG, NOARG, Pc1 | Po32 | Pdef64,0,1,0},
  /* 89 */ {BT_Ijns, Jz, NOARG, NOARG, Pc1 | Po32 | Pdef64,0,1,0},
  /* 8A */ {BT_Ijp, Jz, NOARG, NOARG, Pc1 | Po32 | Pdef64,0,1,0},
  /* 8B */ {BT_Ijnp, Jz, NOARG, NOARG, Pc1 | Po32 | Pdef64,0,1,0},
  /* 8C */ {BT_Ijl, Jz, NOARG, NOARG, Pc1 | Po32 | Pdef64,0,1,0},
  /* 8D */ {BT_Ijge, Jz, NOARG, NOARG, Pc1 | Po32 | Pdef64,0,1,0},
  /* 8E */ {BT_Ijle, Jz, NOARG, NOARG, Pc1 | Po32 | Pdef64,0,1,0},
  /* 8F */ {BT_Ijg, Jz, NOARG, NOARG, Pc1 | Po32 | Pdef64,0,1,0},
  /* 90 */ {BT_Iseto, Eb, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,1,0,INVAL},
  /* 91 */ {BT_Isetno, Eb, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,1,0, INVAL },
  /* 92 */ {BT_Isetb, Eb, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,1,0, INVAL },
  /* 93 */ {BT_Isetnb, Eb, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,1,0, INVAL },
  /* 94 */ {BT_Isetz, Eb, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,1,0, INVAL },
  /* 95 */ {BT_Isetnz, Eb, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,1,0, INVAL },
  /* 96 */ {BT_Isetbe, Eb, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,1,0, INVAL },
  /* 97 */ {BT_Iseta, Eb, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,1,0, INVAL },
  /* 98 */ {BT_Isets, Eb, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,1,0, INVAL },
  /* 99 */ {BT_Isetns, Eb, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,1,0, INVAL },
  /* 9A */ {BT_Isetp, Eb, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,1,0, INVAL },
  /* 9B */ {BT_Isetnp, Eb, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,1,0, INVAL },
  /* 9C */ {BT_Isetl, Eb, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,1,0, INVAL },
  /* 9D */ {BT_Isetge, Eb, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,1,0, INVAL },
  /* 9E */ {BT_Isetle, Eb, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,1,0, INVAL },
  /* 9F */ {BT_Isetg, Eb, NOARG, NOARG, Pa32 | REX (_R | _X | _B) ,1,0, INVAL },
  /* A0 */ {BT_Ipush, FS, NOARG, NOARG, Pnone,0,1,0},
  /* A1 */ {BT_Ipop, FS, NOARG, NOARG, Pnone,1,0, INVAL },
  /* A2 */ {BT_Icpuid, NOARG, NOARG, NOARG, Pnone,0,0, INVAL },
  /* A3 */ {BT_Ibt, Ev, Gv, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B),0,2,0},
  /* A4 */ {BT_Ishld, Ev, Gv, Ib, Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,1},
  /* A5 */ {BT_Ishld, Ev, Gv, CL, Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,1},
  /* A6 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* A7 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* A8 */ {BT_Ipush, GS, NOARG, NOARG, Pnone,0,1,0},
  /* A9 */ {BT_Ipop, GS, NOARG, NOARG, Pnone,1,0, INVAL },
  /* AA */ {BT_Irsm, NOARG, NOARG, NOARG, Pnone,INVAL, INVAL, INVAL },
  /* AB */ {BT_Ibts, Ev, Gv, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  /* AC */ {BT_Ishrd, Ev, Gv, Ib, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,2,1},
  /* AD */ {BT_Ishrd, Ev, Gv, CL, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,2,1},
  /* AE */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_0FAE,INVAL, INVAL, INVAL },
  /* AF */ {BT_Iimul, Gv, Ev, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B) ,1,2,0},
  /* B0 */ {BT_Icmpxchg, Eb, Gb, NOARG, Pa32 | REX (_R | _X | _B), 2,2,0},
  /* B1 */ {BT_Icmpxchg, Ev, Gv, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B), 2,2,0},
  /* B2 */ {BT_Ilss, SS, Gz, M,  Po32 | Pa32 | REX (_W | _R | _X | _B),2,1,2},
  /* B3 */ {BT_Ibtr, Ev, Gv, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  /* B4 */ {BT_Ilfs, FS, Gz, M,  Po32 | Pa32 | REX (_W | _R | _X | _B),2,1,2},
/* B5 */ {BT_Ilgs, GS, Gz, M, Po32 | Pa32 | REX (_W | _R | _X | _B), 2, 1, 2},
  /* B6 */ {BT_Imovzx, Gv, Eb, NOARG, Pc2 | Po32 | Pa32 | REX (_W | _R | _X | _B), 1, 1, 1},
  /* B7 */ {BT_Imovzx, Gv, Ew, NOARG, Pc2 | Po32 | Pa32 | REX (_W | _R | _X | _B), 1, 1, 1},
  /* B8 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* B9 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_0FB9, INVAL, INVAL, INVAL },
  /* BA */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_0FBA, INVAL, INVAL, INVAL },
  /* BB */ {BT_Ibtc, Ev, Gv, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B), 1, 2, 0},
  /* BC */ {BT_Ibsf, Gv, Ev, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B), 1, 1, 1},
  /* BD */ {BT_Ibsr, Gv, Ev, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B), 1, 1, 1},
  /* BE */ {BT_Imovsx, Gv, Eb, NOARG, Pc2 | Po32 | Pa32 | REX (_W | _R | _X | _B), 1, 1, 1},
  /* BF */ {BT_Imovsx, Gv, Ew, NOARG, Pc2 | Po32 | Pa32 | REX (_W | _R | _X | _B), 1, 1, 1},
  /* C0 */ {BT_Ixadd, Eb, Gb, NOARG, Po32 | Pa32 | REX (_R | _X | _B), 2, 2, 0},
  /* C1 */ {BT_Ixadd, Ev, Gv, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B), 2, 2, 0},
  /* C2 */ {BT_Icmpps, V, W, Ib, Pa32 | REX (_R | _X | _B), 1, 3, 0},
  /* C3 */ {BT_Imovnti, Ev, Gx, NOARG, Pa32 | REX (_W | _R | _X | _B), 1, 1, 1},
  /* C4 */ {BT_Ipinsrw, P, Ew, Ib, Po32 | Pa32 | REX (_W | _R | _X | _B), 1, 2, 1},
  /* C5 */ {BT_Ipextrw, Gd, PR, Ib, Po32 | Pa32 | REX (_W | _R | _X | _B), 1, 2, 1},
  /* C6 */ {BT_Ishufps, V, W, Ib, Pa32 | REX (_R | _X | _B), 1, 3, 0},
  /* C7 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_0FC7, INVAL, INVAL, INVAL },
  /* C8 */ {BT_Ibswap, rAXr8, NOARG, NOARG, Po32 | REX (_W | _B), 1, 1, 0},
  /* C9 */ {BT_Ibswap, rCXr9, NOARG, NOARG, Po32 | REX (_W | _B), 1, 1, 0},
  /* CA */ {BT_Ibswap, rDXr10, NOARG, NOARG, Po32 | REX (_W | _B), 1, 1, 0},
  /* CB */ {BT_Ibswap, rBXr11, NOARG, NOARG, Po32 | REX (_W | _B), 1, 1, 0},
  /* CC */ {BT_Ibswap, rSPr12, NOARG, NOARG, Po32 | REX (_W | _B), 1, 1, 0},
  /* CD */ {BT_Ibswap, rBPr13, NOARG, NOARG, Po32 | REX (_W | _B), 1, 1, 0},
  /* CE */ {BT_Ibswap, rSIr14, NOARG, NOARG, Po32 | REX (_W | _B), 1, 1, 0},
  /* CF */ {BT_Ibswap, rDIr15, NOARG, NOARG, Po32 | REX (_W | _B), 1, 1, 0},
  /* D0 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* D1 */ {BT_Ipsrlw, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* D2 */ {BT_Ipsrld, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* D3 */ {BT_Ipsrlq, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* D4 */ {BT_Ipaddq, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* D5 */ {BT_Ipmullw, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* D6 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* D7 */ {BT_Ipmovmskb, Gd, PR, NOARG, Pnone, 1, 1, 1},
  /* D8 */ {BT_Ipsubusb, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* D9 */ {BT_Ipsubusw, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* DA */ {BT_Ipminub, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* DB */ {BT_Ipand, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* DC */ {BT_Ipaddusb, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* DD */ {BT_Ipaddusw, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* DE */ {BT_Ipmaxub, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* DF */ {BT_Ipandn, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* E0 */ {BT_Ipavgb, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* E1 */ {BT_Ipsraw, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* E2 */ {BT_Ipsrad, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* E3 */ {BT_Ipavgw, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* E4 */ {BT_Ipmulhuw, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* E5 */ {BT_Ipmulhw, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* E6 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* E7 */ {BT_Imovntq, M, P, NOARG, Pnone, 1, 1, 1},
  /* E8 */ {BT_Ipsubsb, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* E9 */ {BT_Ipsubsw, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* EA */ {BT_Ipminsw, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* EB */ {BT_Ipor, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* EC */ {BT_Ipaddsb, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* ED */ {BT_Ipaddsw, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* EE */ {BT_Ipmaxsw, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* EF */ {BT_Ipxor, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* F0 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* F1 */ {BT_Ipsllw, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* F2 */ {BT_Ipslld, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* F3 */ {BT_Ipsllq, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* F4 */ {BT_Ipmuludq, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* F5 */ {BT_Ipmaddwd, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* F6 */ {BT_Ipsadbw, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* F7 */ {BT_Imaskmovq, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 0, 2, 0},
  /* F8 */ {BT_Ipsubb, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* F9 */ {BT_Ipsubw, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* FA */ {BT_Ipsubd, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* FB */ {BT_Ipsubq, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* FC */ {BT_Ipaddb, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* FD */ {BT_Ipaddw, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* FE */ {BT_Ipaddd, P, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* FF */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL }
};

MAP_ENTRY itab_2byte_prefixF3[0x100] = {
  /* 00 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 01 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 02 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 03 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 04 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 05 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 06 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 07 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 08 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 09 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 0A */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 0B */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 0C */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 0D */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 0E */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 0F */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 10 */ {BT_Imovss, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 11 */ {BT_Imovss, W, V, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 12 */ {BT_Imovsldup, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 13 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 14 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 15 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 16 */ {BT_Imovshdup, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 17 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 18 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 19 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 1A */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 1B */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 1C */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 1D */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 1E */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 1F */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 20 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 21 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 22 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 23 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 24 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 25 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 26 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 27 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 28 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 29 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 2A */ {BT_Icvtsi2ss, V, Ex, NOARG, Pc2 | Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 2B */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone,INVAL,INVAL,INVAL},
  /* 2C */ {BT_Icvttss2si, Gvw, W, NOARG, Pc1 | Pa32 | REX (_W |_R | _X | _B), 1, 1, 1},
  /* 2D */ {BT_Icvtss2si, Gvw, W, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 2E */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 2F */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 30 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 31 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 32 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 33 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 34 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 35 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 36 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 37 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 38 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 39 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 3A */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 3B */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 3C */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 3D */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 3E */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 3F */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 40 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 41 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 42 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 43 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 44 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 45 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 46 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 47 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 48 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 49 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4A */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4B */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4C */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4D */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4E */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4F */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 50 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 51 */ {BT_Isqrtss, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 52 */ {BT_Irsqrtss, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 53 */ {BT_Ircpss, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 54 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 55 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 56 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 57 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 58 */ {BT_Iaddss, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 59 */ {BT_Imulss, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 5A */ {BT_Icvtss2sd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 5B */ {BT_Icvttps2dq, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 5C */ {BT_Isubss, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 5D */ {BT_Iminss, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 5E */ {BT_Idivss, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 5F */ {BT_Imaxss, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 60 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 61 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 62 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 63 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 64 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 65 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 66 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 67 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 68 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 69 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 6A */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 6B */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 6C */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 6D */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 6E */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 6F */ {BT_Imovdqu, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 70 */ {BT_Ipshufhw, V, W, Ib, Pa32 | REX (_R | _X | _B), 1, 2, 1},
  /* 71 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 72 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 73 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 74 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 75 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 76 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 77 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 78 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 79 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 7A */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 7B */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 7C */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 7D */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 7E */ {BT_Imovq, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 7F */ {BT_Imovdqu, W, V, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 80 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 81 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 82 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 83 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 84 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 85 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 86 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 87 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 88 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 89 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 8A */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 8B */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 8C */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 8D */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 8E */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 8F */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 90 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 91 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 92 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 93 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 94 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 95 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 96 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 97 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 98 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 99 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 9A */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 9B */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 9C */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 9D */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 9E */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 9F */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* A0 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* A1 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* A2 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* A3 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* A4 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* A5 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* A6 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* A7 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* A8 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* A9 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* AA */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* AB */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* AC */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* AD */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* AE */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* AF */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* B0 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* B1 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* B2 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* B3 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* B4 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* B5 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* B6 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* B7 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* B8 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* B9 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* BA */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* BB */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* BC */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* BD */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* BE */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* BF */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* C0 */ {BT_Ixadd, Eb, Gb, NOARG, Pa32 | REX (_W | _R | _X | _B), 2, 2, 0},
  /* C1 */ {BT_Ixadd, Ev, Gv, NOARG, Pa32 | REX (_W | _R | _X | _B), 2, 2, 0},
  /* C2 */ {BT_Icmpss, V, W, Ib, Pa32 | REX (_R | _X | _B), 1, 3, 0},
  /* C3 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* C4 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* C5 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* C6 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* C7 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_0FC7, INVAL, INVAL, INVAL },
  /* C8 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* C9 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* CA */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* CB */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* CC */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* CD */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* CE */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* CF */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* D0 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* D1 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* D2 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* D3 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* D4 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* D5 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* D6 */ {BT_Imovq2dq, V, PR, NOARG, Pa32, 1, 1, 1},
  /* D7 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* D8 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* D9 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* DA */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* DB */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* DC */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* DD */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* DE */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* CF */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* E0 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* E1 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* E2 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* E3 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* E4 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* E5 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* E6 */ {BT_Icvtdq2pd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* E7 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* E8 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* E9 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* EA */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* EB */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* EC */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* ED */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* EE */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* EF */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* F0 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* F1 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* F2 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* F3 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* F4 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* F5 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* F6 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* F7 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* F8 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* F9 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* FA */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* FB */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* FC */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* FD */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* FE */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* FF */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL }
};

MAP_ENTRY itab_2byte_prefix66[0x100] = {
  /* 00 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 01 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 02 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 03 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 04 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 05 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 06 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 07 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 08 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 09 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 0A */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 0B */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 0C */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 0D */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 0E */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 0F */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 10 */ {BT_Imovupd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 11 */ {BT_Imovupd, W, V, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 12 */ {BT_Imovlpd, Vq, Mq, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 13 */ {BT_Imovlpd, Mq, Vq, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 14 */ {BT_Iunpcklpd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 15 */ {BT_Iunpckhpd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 16 */ {BT_Imovhpd, V, M, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 17 */ {BT_Imovhpd, M, V, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 18 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 19 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 1A */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 1B */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 1C */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 1D */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 1E */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 1F */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 20 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 21 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 22 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 23 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 24 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 25 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 26 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 27 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 28 */ {BT_Imovapd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 29 */ {BT_Imovapd, W, V, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 2A */ {BT_Icvtpi2pd, V, Q, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 2B */ {BT_Imovntpd, M, V, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 2C */ {BT_Icvttpd2pi, P, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 2D */ {BT_Icvtpd2pi, P, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 2E */ {BT_Iucomisd, V, W, NOARG, Pa32 | REX (_R | _X | _B), INVAL, 2, 0},
  /* 2F */ {BT_Icomisd, V, W, NOARG, Pa32 | REX (_R | _X | _B), INVAL, 2, 0},
  /* 30 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 31 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 32 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 33 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 34 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 35 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 36 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 37 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 38 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 39 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 3A */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 3B */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 3C */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 3D */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 3E */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 3F */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 40 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 41 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 42 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 43 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 44 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 45 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 46 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 47 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 48 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 49 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4A */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4B */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4C */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4D */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4E */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4F */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 50 */ {BT_Imovmskpd, Gd, VR, NOARG, Po32 | REX (_W | _R | _B), 1, 1, 1},
  /* 51 */ {BT_Isqrtpd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 52 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 53 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 54 */ {BT_Iandpd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 55 */ {BT_Iandnpd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 56 */ {BT_Iorpd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 57 */ {BT_Ixorpd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 58 */ {BT_Iaddpd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 59 */ {BT_Imulpd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 5A */ {BT_Icvtpd2ps, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 5B */ {BT_Icvtps2dq, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 5C */ {BT_Isubpd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 5D */ {BT_Iminpd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 5E */ {BT_Idivpd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 5F */ {BT_Imaxpd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 60 */ {BT_Ipunpcklbw, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 61 */ {BT_Ipunpcklwd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 62 */ {BT_Ipunpckldq, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 63 */ {BT_Ipacksswb, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 64 */ {BT_Ipcmpgtb, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 65 */ {BT_Ipcmpgtw, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 66 */ {BT_Ipcmpgtd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 67 */ {BT_Ipackuswb, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 68 */ {BT_Ipunpckhbw, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 69 */ {BT_Ipunpckhwd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 6A */ {BT_Ipunpckhdq, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 6B */ {BT_Ipackssdw, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 6C */ {BT_Ipunpcklqdq, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 6D */ {BT_Ipunpckhqdq, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 6E */ {BT_Imovd, V, Ex, NOARG, Pc2 | Pa32 | REX (_W | _R | _X | _B), 1, 1, 1},
  /* 6F */ //{BT_Imovqa, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 6F */ {BT_Imovdqa, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 70 */ {BT_Ipshufd, V, W, Ib, Pa32 | REX (_R | _X | _B), 1, 2, 1},
  /* 71 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_0F71, INVAL, INVAL, INVAL },
  /* 72 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_0F72, INVAL, INVAL, INVAL },
  /* 73 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_0F73, INVAL, INVAL, INVAL },
  /* 74 */ {BT_Ipcmpeqb, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 75 */ {BT_Ipcmpeqw, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 76 */ {BT_Ipcmpeqd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 77 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 78 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 79 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 7A */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 7B */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 7C */ {BT_Ihaddpd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 7D */ {BT_Ihsubpd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 7E */ {BT_Imovd, Ex, V, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B), 1, 1, 1},
  /* 7F */ {BT_Imovdqa, W, V, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 80 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 81 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 82 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 83 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 84 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 85 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 86 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 87 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 88 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 89 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 8A */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 8B */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 8C */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 8D */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 8E */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 8F */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 90 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 91 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 92 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 93 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 94 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 95 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 96 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 97 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 98 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 99 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 9A */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 9B */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 9C */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 9D */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 9E */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 9F */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* A0 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* A1 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* A2 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* A3 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* A4 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* A5 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* A6 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* A7 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* A8 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* A9 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* AA */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* AB */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* AC */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* AD */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* AE */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* AF */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* B0 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* B1 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* B2 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* B3 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* B4 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* B5 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* B6 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* B7 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* B8 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* B9 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* BA */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* BB */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* BC */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* BD */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* BE */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* BF */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL}, 
   /* C0 */ {BT_Ixadd, Eb, Gb, NOARG, Pa32 | REX (_W | _R | _X | _B),2,2,0},
  /* C1 */ {BT_Ixadd, Ev, Gv, NOARG, Po32 | Pa32 | REX (_W | _R | _X | _B),2,2,0},
  /* C2 */ {BT_Icmppd, V, W, Ib, Pa32 | REX (_R | _X | _B),1,3,0},
  /* C3 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* C4 */ {BT_Ipinsrw, V, Ew, Ib, Pa32 | REX (_W | _R | _X | _B),1,3,0},
  /* C5 */ {BT_Ipextrw, Gd, VR, Ib, Pa32  | REX (_R | _X | _B),1,2,1},
  /* C6 */ {BT_Ishufpd, V, W, Ib, Pa32 | REX (_R | _X | _B),1,3,0},
  /* C7 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_0FC7,},
  /* C8 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* C9 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* CA */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* CB */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* CC */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* CD */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* CE */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* CF */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* D0 */ {BT_Iaddsubpd, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* D1 */ {BT_Ipsrlw, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* D2 */ {BT_Ipsrld, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* D3 */ {BT_Ipsrlq, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* D4 */ {BT_Ipaddq, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* D5 */ {BT_Ipmullw, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* D6 */ {BT_Imovq, Wq, Vq, NOARG, Pa32 | REX (_R | _X | _B),1,1,1},
  /* D7 */ {BT_Ipmovmskb, Gd, VR, NOARG, Pnone,1,1,1},
  /* D8 */ {BT_Ipsubusb, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* D9 */ {BT_Ipsubusw, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* DA */ {BT_Ipminub, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* DB */ {BT_Ipand, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* DC */ {BT_Ipaddusb, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* DD */ {BT_Ipaddusw, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* DE */ {BT_Ipmaxub, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* DF */ {BT_Ipandn, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* E0 */ {BT_Ipavgb, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* E1 */ {BT_Ipsraw, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* E2 */ {BT_Ipsrad, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* E3 */ {BT_Ipavgw, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* E4 */ {BT_Ipmulhuw, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* E5 */ {BT_Ipmulhw, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* E6 */ {BT_Icvttpd2dq, V, W, NOARG, Pnone,1,1,1},
  /* E7 */ {BT_Imovntdq, M, V, NOARG, Pa32 | REX (_R | _X | _B),1,1,1},
  /* E8 */ {BT_Ipsubsb, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* E9 */ {BT_Ipsubsw, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2.0},
  /* EA */ {BT_Ipminsw, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* EB */ {BT_Ipor, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* EC */ {BT_Ipaddsb, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* ED */ {BT_Ipaddsw, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* EE */ {BT_Ipmaxsw, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* EF */ {BT_Ipxor, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* F0 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* F1 */ {BT_Ipsllw, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* F2 */ {BT_Ipslld, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* F3 */ {BT_Ipsllq, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* F4 */ {BT_Ipmuludq, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* F5 */ {BT_Ipmaddwd, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* F6 */ {BT_Ipsadbw, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* F7 */ {BT_Imaskmovdqu, V, W, NOARG, Pa32 | REX (_R | _X | _B),0,2,0},
  /* F8 */ {BT_Ipsubb, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* F9 */ {BT_Ipsubw, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* FA */ {BT_Ipsubd, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* FB */ {BT_Ipsubq, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* FC */ {BT_Ipaddb, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* FD */ {BT_Ipaddw, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* FE */ {BT_Ipaddd, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* FF */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL}
};

MAP_ENTRY itab_2byte_prefixF2[0x100] = {
  /* 00 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 01 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 02 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 03 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 04 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 05 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 06 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 07 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 08 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 09 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 0A */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 0B */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 0C */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 0D */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 0E */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 0F */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 10 */ {BT_Imovsd_sse, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,1,1},
  /* 11 */ {BT_Imovsd_sse, W, V, NOARG, Pa32 | REX (_R | _X | _B),1,1,1},
  /* 12 */ {BT_Imovddup, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,1,1},
  /* 13 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 14 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 15 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 16 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 17 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 18 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 19 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 1A */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 1B */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 1C */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 1D */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 1E */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 1F */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 20 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 21 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 22 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 23 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 24 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 25 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 26 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 27 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 28 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 29 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 2A */ {BT_Icvtsi2sd, V, Ex, NOARG, Pc2 | Pa32 | REX (_W | _R | _X | _B),1,1,1},
  /* 2B */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 2C */ {BT_Icvttsd2si, Gvw, W, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,1,1},
  /* 2D */ {BT_Icvtsd2si, Gvw, W, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,1,1},
  /* 2E */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 2F */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 30 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 31 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 32 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 33 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 34 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 35 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 36 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 37 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 38 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 39 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 3A */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 3B */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 3C */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 3D */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 3E */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 3F */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 40 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 41 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 42 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 43 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 44 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 45 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 46 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 47 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 48 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 49 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 4A */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 4B */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 4C */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 4D */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 4E */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 4F */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 50 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 51 */ {BT_Isqrtsd, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,1,1},
  /* 52 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 53 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 54 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 55 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 56 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 57 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 58 */ {BT_Iaddsd, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* 59 */ {BT_Imulsd, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* 5A */ {BT_Icvtsd2ss, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,1,1},
  /* 5B */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 5C */ {BT_Isubsd, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* 5D */ {BT_Iminsd, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* 5E */ {BT_Idivsd, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* 5F */ {BT_Imaxsd, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* 60 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 61 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 62 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 63 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 64 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 65 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 66 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 67 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 68 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 69 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 6A */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 6B */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 6C */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 6D */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 6E */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 6F */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 70 */ {BT_Ipshuflw, V, W, Ib, Pa32 | REX (_R | _X | _B),1,2,1},
  /* 71 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 72 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 73 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 74 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 75 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 76 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 77 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 78 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 79 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 7A */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 7B */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 7C */ {BT_Ihaddps, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* 7D */ {BT_Ihsubps, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* 7E */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 7F */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 80 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 81 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 82 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 83 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 84 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 85 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 86 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 87 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 88 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 89 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 8A */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 8B */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 8C */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 8D */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 8E */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 8F */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 90 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 91 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 92 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 93 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 94 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 95 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 96 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 97 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 98 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 99 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 9A */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 9B */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 9C */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 9D */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 9E */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* 9F */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* A0 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* A1 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* A2 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* A3 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* A4 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* A5 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* A6 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* A7 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* A8 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* A9 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* AA */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* AB */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* AC */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* AD */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* AE */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* AF */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* B0 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* B1 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* B2 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* B3 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* B4 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* B5 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* B6 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* B7 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* B8 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* B9 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* BA */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* BB */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* BC */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* BD */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* BE */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* BF */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* C0 */ {BT_Ixadd, Eb, Gb, NOARG, Pa32 | REX (_W | _R | _X | _B),2,2,0},
  /* C1 */ {BT_Ixadd, Ev, Gv, NOARG, Po32 | Pa32 | REX (_R | _X | _B),2,2,0},
  /* C2 */ {BT_Icmpsd_sse, V, W, Ib, Pa32 | REX (_R | _X | _B),1,3,0},
  /* C3 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* C4 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* C5 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* C6 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* C7 */ {BT_Igrp, NOARG, NOARG, NOARG, GRP_0FC7},
  /* C8 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* C9 */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* CA */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* CB */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* CC */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* CD */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* CE */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* CF */ {BT_Ina, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* D0 */ {BT_Iaddsubps, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,2,0},
  /* D1 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* D2 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* D3 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* D4 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* D5 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* D6 */ {BT_Imovdq2q, P, VR, NOARG, Pa32,1,1,1},
  /* D7 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* D8 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* D9 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* DA */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* DB */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* DC */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* DD */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* DE */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* DF */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* E0 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* E1 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* E2 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* E3 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* E4 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* E5 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* E6 */ {BT_Icvtpd2dq, V, W, NOARG, Pa32 | REX (_R | _X | _B),1,1,1},
  /* E7 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* E8 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* E9 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* EA */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* EB */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* EC */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* ED */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* EE */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* EF */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* F0 */ {BT_Ilddqu, V, M, NOARG, Pa32 | REX (_R | _X | _B),1,1,1},
  /* F1 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* F2 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* F3 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* F4 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* F5 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* F6 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* F7 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* F8 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* F9 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* FA */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* FB */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* FC */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* FD */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* FE */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  /* FF */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL}
};

MAP_ENTRY itab_3byte_prefix660f38[0x50] = {
  /* 00 */ {BT_Ipshufb, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 01 */ {BT_Iphaddw, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 02 */ {BT_Iphaddd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 03 */ {BT_Iphaddsw, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 04 */ {BT_Ipmaddubsw, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 05 */ {BT_Iphsubw, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 06 */ {BT_Iphsubd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 07 */ {BT_Iphsubsw, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 08 */ {BT_Ipsignb, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 09 */ {BT_Ipsignw, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 0A */ {BT_Ipsignd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 0B */ {BT_Ipmulhrsw, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 0C */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 0D */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 0E */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 0F */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 10 */ {BT_Ipblendvb, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 11 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 12 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 13 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 14 */ {BT_Iblendvps, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 15 */ {BT_Iblendvpd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 16 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 17 */ {BT_Iptest, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 18 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 19 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 1A */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 1B */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 1C */ {BT_Ipabsb, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 1D */ {BT_Ipabsw, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 1E */ {BT_Ipabsd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 1F */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 20 */ {BT_Ipmovsxbw, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 21 */ {BT_Ipmovsxbd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 22 */ {BT_Ipmovsxbq, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 23 */ {BT_Ipmovsxwd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 24 */ {BT_Ipmovsxwq, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 25 */ {BT_Ipmovsxdq, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 26 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 27 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 28 */ {BT_Ipmuldq, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 29 */ {BT_Ipcmpeqq, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 2A */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 2B */ {BT_Ipackusdw, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 2C */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 2D */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 2E */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 2F */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 30 */ {BT_Ipmovzxbw, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 31 */ {BT_Ipmovzxbd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 32 */ {BT_Ipmovzxbq, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 33 */ {BT_Ipmovzxwd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 34 */ {BT_Ipmovzxwq, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 35 */ {BT_Ipmovzxdq, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 1, 1},
  /* 36 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 37 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 38 */ {BT_Ipminsb, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 39 */ {BT_Ipminsd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 3A */ {BT_Ipminuw, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 3B */ {BT_Ipminud, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 3C */ {BT_Ipmaxsb, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 3D */ {BT_Ipmaxsd, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 3E */ {BT_Ipmaxuw, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 3F */ {BT_Ipmaxud, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 40 */ {BT_Ipmulld, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 41 */ {BT_Iphminposuw, V, W, NOARG, Pa32 | REX (_R | _X | _B), 1, 2, 0},
  /* 42 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 43 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 44 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 45 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 46 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 47 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 48 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 49 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4A */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4B */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4C */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4D */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4E */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4F */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL }
};

MAP_ENTRY itab_3byte_prefix660f3a[0x50] = {
  /* 00 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 01 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 02 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 03 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 04 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 05 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 06 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 07 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 08 */ {BT_Iroundps, V, W, Ib, Pa32 | REX (_R | _X | _B), 1, 2, 1},
  /* 09 */ {BT_Iroundpd, V, W, Ib, Pa32 | REX (_R | _X | _B), 1, 2, 1},
  /* 0A */ {BT_Iroundss, V, W, Ib, Pa32 | REX (_R | _X | _B), 1, 2, 1},
  /* 0B */ {BT_Iroundsd, V, W, Ib, Pa32 | REX (_R | _X | _B), 1, 2, 1},
  /* 0C */ {BT_Iblendps, V, W, Ib, Pa32 | REX (_R | _X | _B), 1, 2, 1},
  /* 0D */ {BT_Iblendpd, V, W, Ib, Pa32 | REX (_R | _X | _B), 1, 2, 1},
  /* 0E */ {BT_Ipblendw, V, W, Ib, Pa32 | REX (_R | _X | _B), 1, 2, 1},
  /* 0F */ {BT_Ipalignr, V, W, Ib, Pa32 | REX (_R | _X | _B), 1, 3, 0},
  /* 10 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 11 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 12 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 13 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 14 */ {BT_Ipextrb, Eb, V, Ib, Pa32 | REX (_R | _X | _B), 1, 2, 1},
  /* 15 */ {BT_Ipextrw, Ew, V, Ib, Pa32 | REX (_R | _X | _B), 1, 2, 1},
  /* 16 */ {BT_Ipextrd, Ed, V, Ib, Pa32 | REX (_R | _X | _B), 1, 2, 1},
  /* 17 */ {BT_Iextractps, Ed, V, Ib, Pa32 | REX (_R | _X | _B), 1, 2, 1},
  /* 18 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 19 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 1A */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 1B */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 1C */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 1D */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 1E */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 1F */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 20 */ {BT_Ipinsrb, V, Ed, Ib, Pa32 | REX (_R | _X | _B), 1, 3, 0},
  /* 21 */ {BT_Iinsertps, V, W, Ib, Pa32 | REX (_R | _X | _B), 1, 3, 0},
  /* 22 */ {BT_Ipinsrd, V, Ed, Ib, Pa32 | REX (_R | _X | _B), 1, 3, 0},
  /* 23 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 24 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 25 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 26 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 27 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 28 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 29 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 2A */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 2B */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 2C */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 2D */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 2E */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 2F */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 30 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 31 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 32 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 33 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 34 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 35 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 36 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 37 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 38 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 39 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 3A */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 3B */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 3C */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 3D */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 3E */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 3F */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 40 */ {BT_Idpps, V, W, Ib, Pa32 | REX (_R | _X | _B), 1, 3, 0},
  /* 41 */ {BT_Idppd, V, W, Ib, Pa32 | REX (_R | _X | _B), 1, 3, 0},
  /* 42 */ {BT_Impsadbw, V, W, Ib, Pa32 | REX (_R | _X | _B), 1, 3, 0},
  /* 43 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 44 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 45 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 46 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 47 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 48 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 49 */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4A */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4B */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4C */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4D */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4E */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  /* 4F */ {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL }
};


MAP_ENTRY itab_g1_op80[0x8] = {
  {BT_Iadd, Eb, Ib, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ior, Eb, Ib, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Iadc, Eb, Ib, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Isbb, Eb, Ib, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Iand, Eb, Ib, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Isub, Eb, Ib, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ixor, Eb, Ib, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Icmp, Eb, Ib, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),0,2,0}
};

MAP_ENTRY itab_g1_op81[0x8] = {
  {BT_Iadd, Ev, Iz, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ior, Ev, Iz, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Iadc, Ev, Iz, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Isbb, Ev, Iz, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Iand, Ev, Iz, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Isub, Ev, Iz, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ixor, Ev, Iz, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Icmp, Ev, Iz, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),0,2,0}
};

MAP_ENTRY itab_g1_op82[0x8] = {
  {BT_Iadd, Eb, Ib, NOARG, Pc1 | Pinv64 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ior, Eb, Ib, NOARG, Pc1 | Pinv64 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Iadc, Eb, Ib, NOARG, Pc1 | Pinv64 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Isbb, Eb, Ib, NOARG, Pc1 | Pinv64 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Iand, Eb, Ib, NOARG, Pc1 | Pinv64 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Isub, Eb, Ib, NOARG, Pc1 | Pinv64 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ixor, Eb, Ib, NOARG, Pc1 | Pinv64 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Icmp, Eb, Ib, NOARG, Pc1 | Pinv64 | Pa32 | REX (_W | _R | _X | _B),0,2,0}
};

MAP_ENTRY itab_g1_op83[0x8] = {
  {BT_Iadd, Ev, Ib, NOARG, Pc1 | Po32 | Pa32 | REX (_R | _X | _B | _W),1,2,0},
  {BT_Ior, Ev, Ib, NOARG, Pc1 | Po32 | Pa32 | REX (_R | _X | _B | _W),1,2,0},
  {BT_Iadc, Ev, Ib, NOARG, Pc1 | Po32 | Pa32 | REX (_R | _X | _B | _W),1,2,0},
  {BT_Isbb, Ev, Ib, NOARG, Pc1 | Po32 | Pa32 | REX (_R | _X | _B | _W),1,2,0},
  {BT_Iand, Ev, Ib, NOARG, Pc1 | Po32 | Pa32 | REX (_R | _X | _B | _W),1,2,0},
  {BT_Isub, Ev, Ib, NOARG, Pc1 | Po32 | Pa32 | REX (_R | _X | _B | _W),1,2,0},
  {BT_Ixor, Ev, Ib, NOARG, Pc1 | Po32 | Pa32 | REX (_R | _X | _B | _W),1,2,0},
  {BT_Icmp, Ev, Ib, NOARG, Pc1 | Po32 | Pa32 | REX (_R | _X | _B | _W),0,2,0}
};

MAP_ENTRY itab_g1A_op8F[0x8] = {
  {BT_Ipop, Ev, NOARG, NOARG, Pc1 | Po32 | Pa32 | Pdef64 | REX (_W | _R | _X | _B),1,0,INVAL},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL}
};

MAP_ENTRY itab_g2_opC0[0x8] = {
  {BT_Irol, Eb, Ib, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Iror, Eb, Ib, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ircl, Eb, Ib, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ircr, Eb, Ib, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ishl, Eb, Ib, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ishr, Eb, Ib, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Isal, Eb, Ib, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Isar, Eb, Ib, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0}
};

MAP_ENTRY itab_g2_opC1[0x8] = {
  {BT_Irol, Ev, Ib, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Iror, Ev, Ib, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ircl, Ev, Ib, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ircr, Ev, Ib, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ishl, Ev, Ib, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ishr, Ev, Ib, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Isal, Ev, Ib, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Isar, Ev, Ib, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0}
};

MAP_ENTRY itab_g2_opD0[0x8] = {
  {BT_Irol, Eb, I1, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Iror, Eb, I1, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ircl, Eb, I1, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ircr, Eb, I1, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ishl, Eb, I1, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ishr, Eb, I1, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Isal, Eb, I1, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Isar, Eb, I1, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0}
};

MAP_ENTRY itab_g2_opD1[0x8] = {
  {BT_Irol, Ev, I1, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Iror, Ev, I1, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ircl, Ev, I1, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ircr, Ev, I1, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ishl, Ev, I1, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ishr, Ev, I1, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Iinvalid, Ev, I1, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),INVAL, INVAL, INVAL},
  {BT_Isar, Ev, I1, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0}
};

MAP_ENTRY itab_g2_opD2[0x8] = {
  {BT_Irol, Eb, CL, NOARG, Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Iror, Eb, CL, NOARG, Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ircl, Eb, CL, NOARG, Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ircr, Eb, CL, NOARG, Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ishl, Eb, CL, NOARG, Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ishr, Eb, CL, NOARG, Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Isal, Eb, CL, NOARG, Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Isar, Eb, CL, NOARG, Pa32 | REX (_W | _R | _X | _B),1,2,0}
};

MAP_ENTRY itab_g2_opD3[0x8] = {
  {BT_Irol, Ev, CL, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Iror, Ev, CL, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ircl, Ev, CL, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ircr, Ev, CL, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ishl, Ev, CL, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Ishr, Ev, CL, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Isal, Ev, CL, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Isar, Ev, CL, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,2,0}
};

MAP_ENTRY itab_g3_opF6[0x8] = {
  {BT_Itest, Eb, Ib, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),0,2,0},
  {BT_Itest, Eb, Ib, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),0,2,0},
  {BT_Inot, Eb, NOARG, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,1,0},
  {BT_Ineg, Eb, NOARG, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,1,0},
  {BT_Imul, AX,AL ,Eb, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,1},
  {BT_Iimul, AX,AL,Eb, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,1},
  {BT_Idiv, AX,Eb,NOARG,  Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Iidiv, AX,Eb, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0}
};

MAP_ENTRY itab_g3_opF7[0x8] = {
  {BT_Itest, Ev, Iz, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),0,2,0},
  {BT_Itest, Ev, Iz, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),0,2,0},
  {BT_Inot, Ev, NOARG, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,1,0},
  {BT_Ineg, Ev, NOARG, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),1,1,0},
  {BT_Imul, rDX,rAX,Ev,Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),2,2,1},
  {BT_Iimul, rDX,rAX,Ev,Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),2,2,1},
  {BT_Idiv, rDX,rAX,Ev, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),2,3,0},
  {BT_Iidiv, rDX,rAX,Ev, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B),2,3,0}
};

MAP_ENTRY itab_g4_opFE[0x8] = {
  {BT_Iinc, Eb, NOARG, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Idec, Eb, NOARG, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B),1,2,0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL }
};

MAP_ENTRY itab_g5_opFF[0x8] = {
  {BT_Iinc, Ev, NOARG, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B), 1, 2, 0},
  {BT_Idec, Ev, NOARG, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B), 1, 2, 0},
  {BT_Icallin, Ev, NOARG, NOARG, Pc1 | Po32 | Pa32 | Pdef64 | REX (_W | _R | _X | _B), 0, 1, 0},
  {BT_Ilcall, Ep, NOARG, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B), 0, 1, 0},
  {BT_Ijmpin, Ev, NOARG, NOARG, Pc1 | Po32 | Pa32 | Pdef64 | REX (_W | _R | _X | _B), 0, 1, 0},
  {BT_Iljmp, Ep, NOARG, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B) , 0, 1, 0},
  {BT_Ipush, Ev, NOARG, NOARG, Pc1 | Pdef64 | Po32 | Pa32 | REX (_W | _R | _X | _B), 0, 1, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL }
};

/* group 6 */
MAP_ENTRY itab_g6_op0F00[0x8] = {
  {BT_Isldt, M, NOARG, NOARG, Po32 | Pa32 | REX (_R | _X | _B), 1, 0, INVAL},
  {BT_Istr, M, NOARG, NOARG, Po32 | Pa32 | REX (_R | _X | _B), 1, 0, INVAL},
  {BT_Illdt, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B), 0, 1, 0},
  {BT_Iltr, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B), 0, 1, 0},
  {BT_Iverr, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B), 0, 1, 0},
  {BT_Iverw, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B), 0, 1, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL }
};

/* group 7 */
MAP_ENTRY itab_g7_op0F01[0x8] = {
  {BT_Isgdt, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B), 1, 0, INVAL},
  {BT_Isidt, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B), 1, 0, INVAL},
  {BT_Ilgdt, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B), 0, 1, 0},
  {BT_Ilidt, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B), 0, 1, 0},
  {BT_Ismsw, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B), 1, 0, INVAL},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ilmsw, Ew, NOARG, NOARG, Pa32 | REX (_R | _X | _B), 0, 1, 0},
  {BT_Iinvlpg, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B), 0, 1, 0}
};

/* group 7 -- Reg7 */
MAP_ENTRY itab_g7_op0F01_Reg7[0x8] = {
  {BT_Iswapgs, GS, NOARG, NOARG, PdepM, 1, 1, 0},
  {BT_Irdtscp, eDX, eAX, NOARG, Pnone, 2, 0, INVAL},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL }
};

/* group 7 -- Reg7 */
MAP_ENTRY itab_g7_op0F01_Reg7_intel[0x8] = {
  {BT_Iswapgs, GS, NOARG, NOARG, PdepM, 1, 1, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL }
};

/* group 7 -- Reg3 */
MAP_ENTRY itab_g7_op0F01_Reg3[0x8] = {
  {BT_Ivmrun, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ivmmcall, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ivmload, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ivmsave, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Istgi, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iclgi, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iskinit, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvlpga, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL }
};

/* group 7 -- Reg0: Intel */
MAP_ENTRY itab_g7_op0F01_Reg0_intel[0x8] = {
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ivmcall, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ivmlaunch, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ivmresume, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ivmxoff, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
};

/* group 7 -- Reg1: Intel */
MAP_ENTRY itab_g7_op0F01_Reg1_intel[0x8] = {
  {BT_Imonitor, eAX, NOARG, NOARG, Pnone, 0, 1, 0},
  {BT_Imwait, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
};

/* group 8 */
MAP_ENTRY itab_g8_op0FBA[0x8] = {
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ibt, Ev, Ib, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B), 0, 2, 0},
  {BT_Ibts, Ev, Ib, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B), 1, 2, 0},
  {BT_Ibtr, Ev, Ib, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B), 1, 2, 0},
  {BT_Ibtc, Ev, Ib, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B), 0, 2, 0},
};

/* group 9 */
MAP_ENTRY itab_g9_op0FC7[0x8] = {
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Icmpxchg8b, M, eDX, eAX, Pa32 | REX (_R | _X | _B) | PdepM, 3, 3, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
};

/* group 9 - Intel */
MAP_ENTRY itab_g9_op0FC7_intel[0x8] = {
  {BT_Ivmptrld, Mq, NOARG, NOARG, Pa32 | REX (_R | _X | _B) , INVAL, INVAL , INVAL },
  {BT_Icmpxchg8b, M, eDX, eAX, Pa32 | REX (_R | _X | _B) | PdepM, 3, 3, 0 },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ivmptrst, Mq, NOARG, NOARG, Pa32 | REX (_R | _X | _B) , INVAL, INVAL , INVAL },
};

/* group 9 - Intel */
MAP_ENTRY itab_g9_op0FC7_prefix66_intel[0x8] = {
  {BT_Ivmclear, Mq, NOARG, NOARG, Pa32 | REX (_R | _X | _B) , INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
};

/* group 9 - Intel */
MAP_ENTRY itab_g9_op0FC7_prefixF3_intel[0x8] = {
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ivmxon, Mq, NOARG, NOARG, Pa32 | REX (_R | _X | _B) , INVAL, INVAL , INVAL },
};

/* group A */
MAP_ENTRY itab_gA_op0FB9[0x8] = {
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
};

/* group B */
MAP_ENTRY itab_gB_opC6[0x8] = {
  {BT_Imov, Eb, Ib, NOARG, Pc1 | Pa32 | REX (_W | _R | _X | _B), 1, 1, 1},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone},
};

/* group B */
MAP_ENTRY itab_gB_opC7[0x8] = {
  {BT_Imov, Ev, Iz, NOARG, Pc1 | Po32 | Pa32 | REX (_W | _R | _X | _B), 1, 1, 1},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
};

/* group C */
MAP_ENTRY itab_gC_op0F71[0x8] = {
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ipsrlw, PR, Ib, NOARG, Pnone, 1, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ipsraw, PR, Ib, NOARG, Pnone, 1, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ipsllw, PR, Ib, NOARG, Pnone, 1, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
};

MAP_ENTRY itab_gC_op0F71_prefix66[0x8] = {
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ipsrlw, VR, Ib, NOARG, Pnone, 1, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ipsraw, VR, Ib, NOARG, Pnone, 1, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ipsllw, VR, Ib, NOARG, Pnone, 1, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
};

MAP_ENTRY itab_gC_op0F71_prefixF3[0x8] = {
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL }
};

MAP_ENTRY itab_gC_op0F71_prefixF2[0x8] = {
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL }
};

/* group D */
MAP_ENTRY itab_gD_op0F72[0x8] = {
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ipsrld, PR, Ib, NOARG, Pnone, 1, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ipsrad, PR, Ib, NOARG, Pnone, 1, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ipslld, PR, Ib, NOARG, Pnone, 1, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
};

/* group D, prefixed by 0x66 */
MAP_ENTRY itab_gD_op0F72_prefix66[0x8] = {
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ipsrld, VR, Ib, NOARG, Pnone, 1, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ipsrad, VR, Ib, NOARG, Pnone, 1, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ipslld, VR, Ib, NOARG, Pnone, 1, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
};

MAP_ENTRY itab_gD_op0F72_prefixF3[0x8] = {
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL }
};

MAP_ENTRY itab_gD_op0F72_prefixF2[0x8] = {
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL }
};

/* group E */
MAP_ENTRY itab_gE_op0F73[0x8] = {
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ipsrlq, PR, Ib, NOARG, Pnone, 1, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ipsllq, PR, Ib, NOARG, Pnone, 1, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL }
};

MAP_ENTRY itab_gE_op0F73_prefix66[0x8] = {
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ipsrlq, VR, Ib, NOARG, Pnone, 1, 2, 0},
  {BT_Ipsrldq, VR, Ib, NOARG, Pnone, 1, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Ipsllq, VR, Ib, NOARG, Pnone, 1, 2, 0},
  {BT_Ipslldq, VR, Ib, NOARG, Pnone, 1, 2, 0}
};

MAP_ENTRY itab_gE_op0F73_prefixF3[0x8] = {
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL }
};

MAP_ENTRY itab_gE_op0F73_prefixF2[0x8] = {
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL }
};

/* group F */
MAP_ENTRY itab_gF_op0FAE[0x8] = {
  {BT_Ifxsave, M, NOARG, NOARG, Pa32 | REX (_W | _R | _X | _B), 1, ALLFR, INVAL},
  {BT_Ifxrstor, M, NOARG, NOARG, Pa32 | REX (_W | _R | _X | _B), ALLFR, 1, 0},
  {BT_Ildmxcsr, Md, NOARG, NOARG, Pa32 | REX (_W | _R | _X | _B), 0, 1, 0},
  {BT_Istmxcsr, Md, NOARG, NOARG, Pa32 | REX (_W | _R | _X | _B), 1, 0, INVAL},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iclflush, M, NOARG, NOARG, Pa32 | REX (_W | _R | _X | _B), 0, 1, 0},
};

MAP_ENTRY itab_gF_op0FAE_prefix66[0x8] = {
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL }
};

MAP_ENTRY itab_gF_op0FAE_prefixF3[0x8] = {
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL }
};

MAP_ENTRY itab_gF_op0FAE_prefixF2[0x8] = {
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL }
};

/* group F -- Extensions */
MAP_ENTRY itab_gF_op0FAE_Reg5 = {
  BT_Ilfence, NOARG, NOARG, NOARG, Pnone
};
MAP_ENTRY itab_gF_op0FAE_Reg6 = {
  BT_Imfence, NOARG, NOARG, NOARG, Pnone
};
MAP_ENTRY itab_gF_op0FAE_Reg7 = {
  BT_Isfence, NOARG, NOARG, NOARG, Pnone
};

/* group 10 */
MAP_ENTRY itab_g10_op0F18[0x8] = {
  {BT_Iprefetchnta, M, NOARG, NOARG, Pa32 | REX (_W | _R | _X | _B)},
  {BT_Iprefetcht0, M, NOARG, NOARG, Pa32 | REX (_W | _R | _X | _B)},
  {BT_Iprefetcht1, M, NOARG, NOARG, Pa32 | REX (_W | _R | _X | _B)},
  {BT_Iprefetcht2, M, NOARG, NOARG, Pa32 | REX (_W | _R | _X | _B)},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL , INVAL }
};

/* group P */
MAP_ENTRY itab_gP_op0F0D[0x8] = {
  {BT_Iprefetch, M, NOARG, NOARG, Pa32 | REX (_W | _R | _X | _B), 0, 1, 0},
  {BT_Iprefetch, M, NOARG, NOARG, Pa32 | REX (_W | _R | _X | _B) , 0, 1, 0},
  {BT_Iprefetch, M, NOARG, NOARG, Pa32 | REX (_W | _R | _X | _B) , 0, 1, 0},
  {BT_Iprefetch, M, NOARG, NOARG, Pa32 | REX (_W | _R | _X | _B) , 0, 1, 0},
  {BT_Iprefetch, M, NOARG, NOARG, Pa32 | REX (_W | _R | _X | _B) , 0, 1, 0},
  {BT_Iprefetch, M, NOARG, NOARG, Pa32 | REX (_W | _R | _X | _B) , 0, 1, 0},
  {BT_Iprefetch, M, NOARG, NOARG, Pa32 | REX (_W | _R | _X | _B) , 0, 1, 0},
  {BT_Iprefetch, M, NOARG, NOARG, Pa32 | REX (_W | _R | _X | _B) , 0, 1, 0}
};

struct
{
  MAP_ENTRY *me_pfx_none;
  MAP_ENTRY *me_pfx_66;
  MAP_ENTRY *me_pfx_f2;
  MAP_ENTRY *me_pfx_f3;
} itab_groups[] =
{
  {
  itab_g1_op80, 0, 0, 0},
  {
  itab_g1_op81, 0, 0, 0},
  {
  itab_g1_op82, 0, 0, 0},
  {
  itab_g1_op83, 0, 0, 0},
  {
  itab_g1A_op8F, 0, 0, 0},
  {
  itab_g2_opC0, 0, 0, 0},
  {
  itab_g2_opC1, 0, 0, 0},
  {
  itab_gB_opC6, 0, 0, 0},
  {
  itab_gB_opC7, 0, 0, 0},
  {
  itab_g2_opD0, 0, 0, 0},
  {
  itab_g2_opD1, 0, 0, 0},
  {
  itab_g2_opD2, 0, 0, 0},
  {
  itab_g2_opD3, 0, 0, 0},
  {
  itab_g3_opF6, 0, 0, 0},
  {
  itab_g3_opF7, 0, 0, 0},
  {
  itab_g4_opFE, 0, 0, 0},
  {
  itab_g5_opFF, 0, 0, 0},
  {
  itab_g6_op0F00, 0, 0, 0},
  {
  itab_g7_op0F01, 0, 0, 0},
  {
  itab_gP_op0F0D, 0, 0, 0},
  {
  itab_g10_op0F18, 0, 0, 0},
  {
  itab_gC_op0F71, itab_gC_op0F71_prefix66, itab_gC_op0F71_prefixF3, itab_gC_op0F71_prefixF2},
  {
  itab_gD_op0F72, itab_gD_op0F72_prefix66, itab_gD_op0F72_prefixF3, itab_gD_op0F72_prefixF2},
  {
  itab_gE_op0F73, itab_gE_op0F73_prefix66, itab_gE_op0F73_prefixF3, itab_gE_op0F73_prefixF2},
  {
  itab_gF_op0FAE, itab_gF_op0FAE_prefix66, itab_gF_op0FAE_prefixF3, itab_gF_op0FAE_prefixF2},
  {
  itab_g8_op0FBA, 0, 0, 0},
  {
  itab_gA_op0FB9, 0, 0, 0},
  {
  itab_g9_op0FC7, 0, 0, 0},
#define ITAB_GROUPS_START_INTEL 28
  {
  itab_g1_op80, 0, 0, 0},
  {
  itab_g1_op81, 0, 0, 0},
  {
  itab_g1_op82, 0, 0, 0},
  {
  itab_g1_op83, 0, 0, 0},
  {
  itab_g1A_op8F, 0, 0, 0},
  {
  itab_g2_opC0, 0, 0, 0},
  {
  itab_g2_opC1, 0, 0, 0},
  {
  itab_gB_opC6, 0, 0, 0},
  {
  itab_gB_opC7, 0, 0, 0},
  {
  itab_g2_opD0, 0, 0, 0},
  {
  itab_g2_opD1, 0, 0, 0},
  {
  itab_g2_opD2, 0, 0, 0},
  {
  itab_g2_opD3, 0, 0, 0},
  {
  itab_g3_opF6, 0, 0, 0},
  {
  itab_g3_opF7, 0, 0, 0},
  {
  itab_g4_opFE, 0, 0, 0},
  {
  itab_g5_opFF, 0, 0, 0},
  {
  itab_g6_op0F00, 0, 0, 0},
  {
  itab_g7_op0F01, 0, 0, 0},
  {
  itab_gP_op0F0D, 0, 0, 0},
  {
  itab_g10_op0F18, 0, 0, 0},
  {
  itab_gC_op0F71, itab_gC_op0F71_prefix66, itab_gC_op0F71_prefixF3, itab_gC_op0F71_prefixF2},
  {
  itab_gD_op0F72, itab_gD_op0F72_prefix66, itab_gD_op0F72_prefixF3, itab_gD_op0F72_prefixF2},
  {
  itab_gE_op0F73, itab_gE_op0F73_prefix66, itab_gE_op0F73_prefixF3, itab_gE_op0F73_prefixF2},
  {
  itab_gF_op0FAE, itab_gF_op0FAE_prefix66, itab_gF_op0FAE_prefixF3, itab_gF_op0FAE_prefixF2},
  {
  itab_g8_op0FBA, 0, 0, 0},
  {
  itab_gA_op0FB9, 0, 0, 0},
  {
itab_g9_op0FC7_intel, itab_g9_op0FC7_prefix66_intel, itab_g9_op0FC7_prefixF3_intel, 0},};

/* D8 Opcode Map */
MAP_ENTRY itab_x87_opD8reg[0x8] = {
  {BT_Ifadd, ST0, Md, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0},
  {BT_Ifmul, ST0, Md, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0},
  {BT_Ifcom, ST0, Md, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 0, 2, 0},
  {BT_Ifcomp, ST0, Md, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 0, 2, 0},
  {BT_Ifsub, ST0, Md, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0},
  {BT_Ifsubr, ST0, Md, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0},
  {BT_Ifdiv, ST0, Md, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0},
  {BT_Ifdivr, ST0, Md, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0}
};

/* D9 Opcode Map */
MAP_ENTRY itab_x87_opD9reg[0x8] = {
  {BT_Ifld, ST0, Md, NOARG,  Pc1 | Pa32 | REX (_R | _X | _B), 1, 1, 1},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  {BT_Ifst, Md, ST0, NOARG,  Pc1 | Pa32 | REX (_R | _X | _B), 1, 1, 1},
  {BT_Ifstp, Md, ST0, NOARG,  Pc1 | Pa32 | REX (_R | _X | _B), 1, 1, 1},
  {BT_Ifldenv, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B), ALLFR, 1, 0},
  {BT_Ifldcw, Mw, NOARG, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), INVAL, 1, 0},
  {BT_Ifnstenv, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B), 1, ALLFR, INVAL},
  {BT_Ifnstcw, Mw, NOARG, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 0, INVAL}
};

/* DA Opcode Map */
MAP_ENTRY itab_x87_opDAreg[0x8] = {
  {BT_Ifiadd, ST0, Md, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0},
  {BT_Ifimul, ST0, Md, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0},
  {BT_Ificom, ST0, Md, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 0, 2, 0},
  {BT_Ificomp, ST0, Md, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 0, 2, 0},
  {BT_Ifisub, ST0, Md, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0},
  {BT_Ifisubr, ST0, Md, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0},
  {BT_Ifidiv, ST0, Md, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0},
  {BT_Ifidivr, ST0, Md, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0}
};

/* DB Opcode Map */
MAP_ENTRY itab_x87_opDBreg[0x8] = {
  {BT_Ifild, ST0, Md, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 1, 1},
  {BT_Ifisttp, Md, ST0, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 1, 1},
  {BT_Ifist, Md, ST0, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 1, 1},
  {BT_Ifistp, Md, ST0, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 1, 1},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  {BT_Ifld, ST0, Mt, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 1, 1},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Ifstp, Mt, ST0, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 1, 1}
};

/* DC Opcode Map */
MAP_ENTRY itab_x87_opDCreg[0x8] = {
  {BT_Ifadd, ST0, Mq, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0},
  {BT_Ifmul, ST0, Mq, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0},
  {BT_Ifcom, ST0, Mq, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 0, 2, 0},
  {BT_Ifcomp, ST0, Mq, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 0, 2, 0},
  {BT_Ifsub, ST0, Mq, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0},
  {BT_Ifsubr, ST0, Mq, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0},
  {BT_Ifdiv, ST0, Mq, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0},
  {BT_Ifdivr, ST0, Mq, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0}
};

/* DD Opcode Map */
MAP_ENTRY itab_x87_opDDreg[0x8] = {
  {BT_Ifld, ST0, Mq, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 1, 1},
  {BT_Ifisttp, Mq, ST0, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 1, 1},
  {BT_Ifst, Mq, ST0, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 1, 1},
  {BT_Ifstp, Mq, ST0, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 1, 1},
  {BT_Ifrstor, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B), ALLFR, 1, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Ifnsave, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B), 1, ALLFR, INVAL},
  {BT_Ifnstsw, M, NOARG, NOARG, Pa32 | REX (_R | _X | _B), 1, 0, INVAL}
};

/* DE Opcode Map */
MAP_ENTRY itab_x87_opDEreg[0x8] = {
  {BT_Ifiadd, ST0, Mw, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0},
  {BT_Ifimul, ST0, Mw, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0},
  {BT_Ificom, ST0, Mw, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 0, 2, 0},
  {BT_Ificomp, ST0, Mw, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 0, 2, 0},
  {BT_Ifisub, ST0, Mw, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0},
  {BT_Ifisubr, ST0, Mw, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0},
  {BT_Ifidiv, ST0, Mw, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0},
  {BT_Ifidivr, ST0, Mw, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 2, 0}
};

/* DF Opcode Map */
MAP_ENTRY itab_x87_opDFreg[0x8] = {
  {BT_Ifild, ST0, Mw, NOARG, Pc1 | Pa32 | REX (_R | _X | _B), 1, 1, 1},
  {BT_Ifisttp, Mw, ST0, NOARG, Pc1 | Pa32 | REX (_R | _X | _B) , 1, 1, 1},
  {BT_Ifist, Mw, ST0, NOARG, Pc1 | Pa32 | REX (_R | _X | _B) , 1, 1, 1},
  {BT_Ifistp, Mw, ST0, NOARG, Pc1 | Pa32 | REX (_R | _X | _B) , 1, 1, 1},
  {BT_Ifbld, ST0, Mt, NOARG, Pa32 | REX (_R | _X | _B) , 1, 1, 1},
  {BT_Ifild, ST0, Mq, NOARG, Pc1 | Pa32 | REX (_R | _X | _B) , 1, 1, 1},
  {BT_Ifbstp, Mt, ST0, NOARG, Pa32 | REX (_R | _X | _B) , 1, 1, 1},
  {BT_Ifistp, Mq, ST0, NOARG, Pc1 | Pa32 | REX (_R | _X | _B) , 1, 1, 1}
};

MAP_ENTRY itab_g_invalid[0x8] = {
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
};

/* D8 Opcode Map */
MAP_ENTRY itab_x87_opD8[0x8 * 0x8] = {
  {BT_Ifadd, ST0, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifadd, ST0, ST1, NOARG, Pnone, 1, 2, 0},
  {BT_Ifadd, ST0, ST2, NOARG, Pnone, 1, 2, 0},
  {BT_Ifadd, ST0, ST3, NOARG, Pnone, 1, 2, 0},
  {BT_Ifadd, ST0, ST4, NOARG, Pnone, 1, 2, 0},
  {BT_Ifadd, ST0, ST5, NOARG, Pnone, 1, 2, 0},
  {BT_Ifadd, ST0, ST6, NOARG, Pnone, 1, 2, 0},
  {BT_Ifadd, ST0, ST7, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmul, ST0, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmul, ST0, ST1, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmul, ST0, ST2, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmul, ST0, ST3, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmul, ST0, ST4, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmul, ST0, ST5, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmul, ST0, ST6, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmul, ST0, ST7, NOARG, Pnone, 1, 2, 0},
  {BT_Ifcom, ST0, ST0, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcom, ST0, ST1, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcom, ST0, ST2, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcom, ST0, ST3, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcom, ST0, ST4, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcom, ST0, ST5, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcom, ST0, ST6, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcom, ST0, ST7, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomp, ST0, ST0, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomp, ST0, ST1, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomp, ST0, ST2, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomp, ST0, ST3, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomp, ST0, ST4, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomp, ST0, ST5, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomp, ST0, ST6, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomp, ST0, ST7, NOARG, Pnone, 0, 2, 0},
  {BT_Ifsub, ST0, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsub, ST0, ST1, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsub, ST0, ST2, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsub, ST0, ST3, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsub, ST0, ST4, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsub, ST0, ST5, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsub, ST0, ST6, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsub, ST0, ST7, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubr, ST0, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubr, ST0, ST1, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubr, ST0, ST2, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubr, ST0, ST3, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubr, ST0, ST4, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubr, ST0, ST5, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubr, ST0, ST6, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubr, ST0, ST7, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdiv, ST0, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdiv, ST0, ST1, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdiv, ST0, ST2, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdiv, ST0, ST3, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdiv, ST0, ST4, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdiv, ST0, ST5, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdiv, ST0, ST6, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdiv, ST0, ST7, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivr, ST0, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivr, ST0, ST1, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivr, ST0, ST2, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivr, ST0, ST3, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivr, ST0, ST4, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivr, ST0, ST5, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivr, ST0, ST6, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivr, ST0, ST7, NOARG, Pnone, 1, 2, 0}
};

/* D9 Opcode Map */
MAP_ENTRY itab_x87_opD9[0x8 * 0x8] = {
  {BT_Ifld, ST0, ST0, NOARG, Pnone, 1 ,1 ,1},
  {BT_Ifld, ST0, ST1, NOARG, Pnone, 1 ,1 ,1},
  {BT_Ifld, ST0, ST2, NOARG, Pnone, 1 ,1 ,1},
  {BT_Ifld, ST0, ST3, NOARG, Pnone, 1 ,1 ,1},
  {BT_Ifld, ST0, ST4, NOARG, Pnone, 1 ,1 ,1},
  {BT_Ifld, ST0, ST5, NOARG, Pnone, 1 ,1 ,1},
  {BT_Ifld, ST0, ST6, NOARG, Pnone, 1 ,1 ,1},
  {BT_Ifld, ST0, ST7, NOARG, Pnone, 1 ,1 ,1},
  {BT_Ifxch, ST0, ST0, NOARG, Pnone, 2 ,2, 0},
  {BT_Ifxch, ST0, ST1, NOARG, Pnone, 2 ,2, 0},
  {BT_Ifxch, ST0, ST2, NOARG, Pnone, 2 ,2, 0},
  {BT_Ifxch, ST0, ST3, NOARG, Pnone, 2 ,2, 0},
  {BT_Ifxch, ST0, ST4, NOARG, Pnone, 2 ,2, 0},
  {BT_Ifxch, ST0, ST5, NOARG, Pnone, 2 ,2, 0},
  {BT_Ifxch, ST0, ST6, NOARG, Pnone, 2 ,2, 0},
  {BT_Ifxch, ST0, ST7, NOARG, Pnone, 2, 2, 0},
  {BT_Ifnop, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Inone, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Inone, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Inone, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Inone, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Inone, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Inone, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Inone, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Inone, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Ifchs, ST0, NOARG, NOARG, Pnone, 1, 1, 0 },
  {BT_Ifabs, ST0, NOARG , NOARG, Pnone, 1, 1, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iftst, ST0, NOARG, NOARG, Pnone, 0, 1, 0},
  {BT_Ifxam, ST0, NOARG, NOARG, Pnone, 0, 1, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Ifld1, ST0, NOARG, NOARG, Pnone, 1, 0, INVAL},
  {BT_Ifldl2t, ST0, NOARG, NOARG, Pnone, 1, 0, INVAL },
  {BT_Ifldl2e, ST0, NOARG, NOARG, Pnone, 1, 0, INVAL },
  {BT_Ifldlpi, ST0, NOARG, NOARG, Pnone, 1, 0, INVAL },
  {BT_Ifldlg2, ST0, NOARG, NOARG, Pnone, 1, 0, INVAL },
  {BT_Ifldln2, ST0, NOARG, NOARG, Pnone, 1, 0, INVAL },
  {BT_Ifldz, ST0, NOARG, NOARG, Pnone, 1, 0, INVAL },
  {BT_Iinvalid, ST0, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_If2xm1, ST0, NOARG, NOARG, Pnone, 1, 1, 0},
  {BT_Ifyl2x, ST1, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifptan, ST0, I1, NOARG, Pnone, 1, 2, 0},
  {BT_Ifpatan, ST1, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifxtract, ST0, NOARG, NOARG, Pnone, 1, 1, 0},
  {BT_Ifprem1, ST0, ST1, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdecstp, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Ifincstp, ST0, NOARG, NOARG, Pnone, 1, 1, 0},
  {BT_Ifprem, ST0, ST1, NOARG, Pnone, 1, 2, 0},
  {BT_Ifyl2xp1, ST1, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsqrt, ST0, NOARG, NOARG, Pnone, 1, 1, 0},
  {BT_Ifsincos, ST0, NOARG, NOARG, Pnone, 1, 1, 0},
  {BT_Ifrndint, ST0, NOARG, NOARG, Pnone, 1, 1, 0},
  {BT_Ifscale, ST0, ST1, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsin, ST0, NOARG, NOARG, Pnone, 1, 1, 0},
  {BT_Ifcos, ST0, NOARG, NOARG, Pnone, 1, 1, 0}
};

/* DA Opcode Map */
MAP_ENTRY itab_x87_opDA[0x8 * 0x8] = {
  {BT_Ifcmovb, ST0, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovb, ST0, ST1, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovb, ST0, ST2, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovb, ST0, ST3, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovb, ST0, ST4, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovb, ST0, ST5, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovb, ST0, ST6, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovb, ST0, ST7, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmove, ST0, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmove, ST0, ST1, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmove, ST0, ST2, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmove, ST0, ST3, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmove, ST0, ST4, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmove, ST0, ST5, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmove, ST0, ST6, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmove, ST0, ST7, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovbe, ST0, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovbe, ST0, ST1, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovbe, ST0, ST2, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovbe, ST0, ST3, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovbe, ST0, ST4, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovbe, ST0, ST5, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovbe, ST0, ST6, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovbe, ST0, ST7, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovu, ST0, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovu, ST0, ST1, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovu, ST0, ST2, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovu, ST0, ST3, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovu, ST0, ST4, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovu, ST0, ST5, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovu, ST0, ST6, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovu, ST0, ST7, NOARG, Pnone, 1, 1, 1},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Ifucompp, ST0, ST1, NOARG, Pnone, 0, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL }
};

/* DB Opcode Map */
MAP_ENTRY itab_x87_opDB[0x8 * 0x8] = {
  {BT_Ifcmovnb, ST0, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnb, ST0, ST1, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnb, ST0, ST2, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnb, ST0, ST3, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnb, ST0, ST4, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnb, ST0, ST5, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnb, ST0, ST6, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnb, ST0, ST7, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovne, ST0, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovne, ST0, ST1, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovne, ST0, ST2, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovne, ST0, ST3, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovne, ST0, ST4, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovne, ST0, ST5, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovne, ST0, ST6, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovne, ST0, ST7, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnbe, ST0, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnbe, ST0, ST1, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnbe, ST0, ST2, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnbe, ST0, ST3, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnbe, ST0, ST4, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnbe, ST0, ST5, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnbe, ST0, ST6, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnbe, ST0, ST7, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnu, ST0, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnu, ST0, ST1, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnu, ST0, ST2, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnu, ST0, ST3, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnu, ST0, ST4, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnu, ST0, ST5, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnu, ST0, ST6, NOARG, Pnone, 1, 1, 1},
  {BT_Ifcmovnu, ST0, ST7, NOARG, Pnone, 1, 1, 1},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Ifclex, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Ifninit, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Ifucomi, ST0, ST0, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomi, ST0, ST1, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomi, ST0, ST2, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomi, ST0, ST3, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomi, ST0, ST4, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomi, ST0, ST5, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomi, ST0, ST6, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomi, ST0, ST7, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomi, ST0, ST0, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomi, ST0, ST1, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomi, ST0, ST2, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomi, ST0, ST3, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomi, ST0, ST4, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomi, ST0, ST5, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomi, ST0, ST6, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomi, ST0, ST7, NOARG, Pnone, 0, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL }
};

/* DC Opcode Map */
MAP_ENTRY itab_x87_opDC[0x8 * 0x8] = {
  {BT_Ifadd, ST0, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifadd, ST1, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifadd, ST2, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifadd, ST3, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifadd, ST4, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifadd, ST5, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifadd, ST6, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifadd, ST7, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmul, ST0, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmul, ST1, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmul, ST2, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmul, ST3, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmul, ST4, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmul, ST5, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmul, ST6, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmul, ST7, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Ifsubr, ST0, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubr, ST1, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubr, ST2, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubr, ST3, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubr, ST4, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubr, ST5, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubr, ST6, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubr, ST7, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsub, ST0, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsub, ST1, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsub, ST2, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsub, ST3, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsub, ST4, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsub, ST5, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsub, ST6, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsub, ST7, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivr, ST0, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivr, ST1, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivr, ST2, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivr, ST3, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivr, ST4, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivr, ST5, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivr, ST6, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivr, ST7, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdiv, ST0, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdiv, ST1, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdiv, ST2, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdiv, ST3, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdiv, ST4, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdiv, ST5, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdiv, ST6, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdiv, ST7, ST0, NOARG, Pnone, 1, 2, 0}
};

/* DD Opcode Map */
MAP_ENTRY itab_x87_opDD[0x8 * 0x8] = {
  {BT_Iffree, ST0, NOARG, NOARG, Pnone, INVAL, 1, 0},
  {BT_Iffree, ST1, NOARG, NOARG, Pnone, INVAL, 1, 0},
  {BT_Iffree, ST2, NOARG, NOARG, Pnone, INVAL, 1, 0},
  {BT_Iffree, ST3, NOARG, NOARG, Pnone, INVAL, 1, 0},
  {BT_Iffree, ST4, NOARG, NOARG, Pnone, INVAL, 1, 0},
  {BT_Iffree, ST5, NOARG, NOARG, Pnone, INVAL, 1, 0},
  {BT_Iffree, ST6, NOARG, NOARG, Pnone, INVAL, 1, 0},
  {BT_Iffree, ST7, NOARG, NOARG, Pnone, INVAL, 1, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Ifst, ST0, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifst, ST1, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifst, ST2, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifst, ST3, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifst, ST4, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifst, ST5, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifst, ST6, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifst, ST7, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifstp, ST0, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifstp, ST1, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifstp, ST2, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifstp, ST3, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifstp, ST4, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifstp, ST5, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifstp, ST6, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifstp, ST7, ST0, NOARG, Pnone, 1, 1, 1},
  {BT_Ifucom, ST0, ST0, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucom, ST0, ST1, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucom, ST0, ST2, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucom, ST0, ST3, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucom, ST0, ST4, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucom, ST0, ST5, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucom, ST0, ST6, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucom, ST0, ST7, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomp, ST0, ST0, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomp, ST0, ST1, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomp, ST0, ST2, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomp, ST0, ST3, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomp, ST0, ST4, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomp, ST0, ST5, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomp, ST0, ST6, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomp, ST0, ST7, NOARG, Pnone, 0, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL }
};

/* DE Opcode Map */
MAP_ENTRY itab_x87_opDE[0x8 * 0x8] = {
  {BT_Ifaddp, ST0, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifaddp, ST1, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifaddp, ST2, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifaddp, ST3, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifaddp, ST4, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifaddp, ST5, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifaddp, ST6, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifaddp, ST7, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmulp, ST0, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmulp, ST1, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmulp, ST2, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmulp, ST3, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmulp, ST4, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmulp, ST5, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmulp, ST6, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifmulp, ST7, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Ifcompp, ST0, ST1, NOARG, Pnone, 0, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Ifsubrp, ST0, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubrp, ST1, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubrp, ST2, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubrp, ST3, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubrp, ST4, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubrp, ST5, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubrp, ST6, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubrp, ST7, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubp, ST0, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubp, ST1, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubp, ST2, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubp, ST3, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubp, ST4, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubp, ST5, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubp, ST6, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifsubp, ST7, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivrp, ST0, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivrp, ST1, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivrp, ST2, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivrp, ST3, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivrp, ST4, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivrp, ST5, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivrp, ST6, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivrp, ST7, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivp, ST0, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivp, ST1, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivp, ST2, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivp, ST3, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivp, ST4, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivp, ST5, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivp, ST6, ST0, NOARG, Pnone, 1, 2, 0},
  {BT_Ifdivp, ST7, ST0, NOARG, Pnone, 1, 2, 0}
};

/* DF Opcode Map */
MAP_ENTRY itab_x87_opDF[0x8 * 0x8] = {
  {BT_Iffreep, ST0, NOARG, NOARG, Pnone, INVAL, 1, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },

{BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },

  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },

{BT_Ifnstsw, AX, NOARG, NOARG, Pnone, 1, 0, INVAL},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Ifucomip, ST0, ST0, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomip, ST0, ST1, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomip, ST0, ST2, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomip, ST0, ST3, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomip, ST0, ST4, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomip, ST0, ST5, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomip, ST0, ST6, NOARG, Pnone, 0, 2, 0},
  {BT_Ifucomip, ST0, ST7, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomip, ST0, ST0, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomip, ST0, ST1, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomip, ST0, ST2, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomip, ST0, ST3, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomip, ST0, ST4, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomip, ST0, ST5, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomip, ST0, ST6, NOARG, Pnone, 0, 2, 0},
  {BT_Ifcomip, ST0, ST7, NOARG, Pnone, 0, 2, 0},
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL },
  {BT_Iinvalid, NOARG, NOARG, NOARG, Pnone, INVAL, INVAL, INVAL }
};

MAP_ENTRY *itab_x87_reg[] = {
  itab_x87_opD8reg,
  itab_x87_opD9reg,
  itab_x87_opDAreg,
  itab_x87_opDBreg,
  itab_x87_opDCreg,
  itab_x87_opDDreg,
  itab_x87_opDEreg,
  itab_x87_opDFreg
};

MAP_ENTRY *itab_x87[] = {
  itab_x87_opD8,
  itab_x87_opD9,
  itab_x87_opDA,
  itab_x87_opDB,
  itab_x87_opDC,
  itab_x87_opDD,
  itab_x87_opDE,
  itab_x87_opDF
};

/* AMD 3DNow! Instructions */
MAP_ENTRY itab_3DNow = { BT_I3dnow, P, Q, NOARG };
MAP_ENTRY nop = { BT_Inop, NOARG, NOARG, NOARG, Pnone };
MAP_ENTRY pause_amd = { BT_Ipause, NOARG, NOARG, NOARG, Pnone };
MAP_ENTRY movsxd =
  { BT_Imovsxd, Gv, Ed, NOARG, Pc2 | Po32 | Pa32 | REX (_X | _W | _B | _R) };
MAP_ENTRY db = { BT_Idb, Ib, NOARG, NOARG, Pnone };
MAP_ENTRY invalid = { BT_Iinvalid, NOARG, NOARG, NOARG, Pnone };

MAP_ENTRY *bt_me_db ()
{
  return &db;
}

MAP_ENTRY *bt_me_invalid ()
{
  return &invalid;
}

/* 3D Now instructions with suffix */
extern OPCODE map_get_3dnow (UINT8 suffix)
{
  switch (suffix)
  {
    case 0x0C:
      return BT_Ipi2fw;
    case 0x0D:
      return BT_Ipi2fd;
    case 0x1C:
      return BT_Ipf2iw;
    case 0x1D:
      return BT_Ipf2id;
    case 0x8A:
      return BT_Ipfnacc;
    case 0x8E:
      return BT_Ipfpnacc;
    case 0x90:
      return BT_Ipfcmpge;
    case 0x94:
      return BT_Ipfmin;
    case 0x96:
      return BT_Ipfrcp;
    case 0x97:
      return BT_Ipfrsqrt;
    case 0x9A:
      return BT_Ipfsub;
    case 0x9E:
      return BT_Ipfadd;
    case 0xA0:
      return BT_Ipfcmpgt;
    case 0xA4:
      return BT_Ipfmax;
    case 0xA6:
      return BT_Ipfrcpit1;
    case 0xA7:
      return BT_Ipfrsqit1;
    case 0xAA:
      return BT_Ipfsubr;
    case 0xAE:
      return BT_Ipfacc;
    case 0xB0:
      return BT_Ipfcmpeq;
    case 0xB4:
      return BT_Ipfmul;
    case 0xB6:
      return BT_Ipfrcpit2;
    case 0xB7:
      return BT_Ipmulhrw;
    case 0xBB:
      return BT_Ipswapd;
    case 0xBF:
      return BT_Ipavgusb;
  }
  return (OPCODE) (0);
}

/* -----------------------------------------------------------------------------
   search_1byte_insn() - Searches for 1-byte instructions.
   ----------------------------------------------------------------------------- */
static void search_1byte_insn (register UD *u)
{
  u->mapen = &(itab_1byte[inp_curr (u)]);

  if (inp_curr (u) == 0x90)
  {
    if (!(u->dis_mode == 64 && P_REX_B (u->pfx_rex)))
    {
      if (u->pfx_rep)
      {
        u->mapen = &pause_amd;
        u->pfx_rep = 0;
      }
      else
        u->mapen = &nop;
    }
  }
  else if (u->dis_mode == 64 && (u->mapen)->mnemonic == BT_Iarpl)
    u->mapen = &movsxd;

  else if (u->mapen->mnemonic == BT_Igrp)
    u->mapen = &itab_groups[u->mapen->prefix].me_pfx_none[MODRM_REG (inp_peek (u))];

  else if ((u->mapen)->mnemonic == BT_Ix87)
  {
    if (inp_peek (u) <= 0xBF)
    {
      u->mapen = &itab_x87_reg[(inp_curr (u)) - 0xD8][MODRM_REG (inp_peek (u))];
    }
    else
    {
      u->mapen = &itab_x87[inp_curr (u) - 0xD8][inp_peek (u) - 0xC0];
      inp_next (u);
    }
  }
}

/* -----------------------------------------------------------------------------
   search_2byte_insn() - Searches for 2-byte instructions.
   ----------------------------------------------------------------------------- */
static void search_2byte_insn (register UD *u)
{
  UINT32 gindex;

  inp_next(u);

  if (u->pfx_insn == 0x66)
  {
    u->mapen = &itab_2byte_prefix66[inp_curr(u)];

    if(inp_curr(u)==(UINT8)0x38) {
        inp_next(u);
        u->mapen = &itab_3byte_prefix660f38[inp_curr(u)];
        if(inp_curr(u)>=0x50)
            u->mapen->mnemonic = BT_Iinvalid;
    }
    else if(inp_curr(u)==(UINT8)0x3a) {
        inp_next(u);
        u->mapen = &itab_3byte_prefix660f3a[inp_curr(u)];
        if(inp_curr(u)>=0x50)
            u->mapen->mnemonic = BT_Iinvalid;
    }

    if (u->mapen != NULL && u->mapen->mnemonic != BT_Ina)
        u->pfx_opr = 0;
  }
  else if (u->pfx_insn == 0xF2)
  {
    u->mapen = &itab_2byte_prefixF2[inp_curr(u)];
    if (u->mapen != NULL && u->mapen->mnemonic != BT_Ina)
      u->pfx_repne = 0;
  }
  else if (u->pfx_insn == 0xF3)
  {
    u->mapen = &itab_2byte_prefixF3[inp_curr(u)];
    if (u->mapen != NULL && u->mapen->mnemonic != BT_Ina)
      u->pfx_rep = 0;
  }

  if (u->mapen == NULL || u->mapen->mnemonic == BT_Ina)
    u->mapen = &itab_2byte[inp_curr(u)];

  if (u->mapen->mnemonic == BT_I3dnow)
    u->mapen = &itab_3DNow;

  if (u->mapen->mnemonic != BT_Igrp)
    return;

  /* If instruction is in a Group */
  gindex = u->mapen->prefix + ((u->vendor == BT_VENDOR_INTEL) ? ITAB_GROUPS_START_INTEL : 0);

  if (u->pfx_insn == 0x66 && itab_groups[gindex].me_pfx_66)
  {
    u->mapen = &itab_groups[gindex].me_pfx_66[MODRM_REG (inp_peek (u))];
    if (u->mapen != NULL && u->mapen->mnemonic != BT_Ina)
    {
      u->pfx_opr = 0;
      return;
    }
  }
  else if (u->pfx_insn == 0xF2 && itab_groups[gindex].me_pfx_f2)
  {
    u->mapen = &itab_groups[gindex].me_pfx_f2[MODRM_REG (inp_peek (u))];
    if (u->mapen != NULL && u->mapen->mnemonic != BT_Ina)
    {
      u->pfx_repne = 0;
      return;
    }
  }
  else if (u->pfx_insn == 0xF3 && itab_groups[gindex].me_pfx_f3)
  {
    u->mapen = &itab_groups[gindex].me_pfx_f3[MODRM_REG (inp_peek (u))];
    if (u->mapen != NULL && u->mapen->mnemonic != BT_Ina)
    {
      u->pfx_rep = 0;
      return;
    }
  }

  if (!u->pfx_insn || u->mapen->mnemonic == BT_Igrp)
    u->mapen = &itab_groups[gindex].me_pfx_none[MODRM_REG (inp_peek (u))];

  /* 0F01 - opcode extensions */
  if (inp_curr (u) == 0x01)
  {
    UINT8 reg = MODRM_REG (inp_peek (u));
    UINT8 mod = MODRM_MOD (inp_peek (u));
    UINT8 rm = MODRM_RM (inp_peek (u));

    if (u->vendor == BT_VENDOR_INTEL)
    {
      if (reg == 0 && mod == 3)
      {
        u->mapen = &itab_g7_op0F01_Reg0_intel[rm];
        inp_next (u);
      }
      else if (reg == 1 && mod == 3)
      {
        u->mapen = &itab_g7_op0F01_Reg1_intel[rm];
        inp_next (u);
      }
      else if (reg == 7 && mod == 3)
      {
        u->mapen = &itab_g7_op0F01_Reg7_intel[rm];
        inp_next (u);
      }
    }
    else
    {
      if (reg == 3 && mod == 3)
      {
        u->mapen = &itab_g7_op0F01_Reg3[rm];
        inp_next (u);
      }
      else if (reg == 7 && mod == 3)
      {
        u->mapen = &itab_g7_op0F01_Reg7[rm];
        inp_next (u);
      }
      else
        u->mapen = &itab_g7_op0F01[reg];
    }
  }
  /* 0FAE - opcode extensions */
  else if (inp_curr (u) == 0xAE)
  {
    UINT8 reg = MODRM_REG (inp_peek (u));
    UINT8 mod = MODRM_MOD (inp_peek (u));

    if (reg == 5 && mod == 3)
    {
      u->mapen = &itab_gF_op0FAE_Reg5;
      inp_next (u);
    }
    else if (reg == 6 && mod == 3)
    {
      u->mapen = &itab_gF_op0FAE_Reg6;
      inp_next (u);
    }
    else if (reg == 7 && mod == 3)
    {
      u->mapen = &itab_gF_op0FAE_Reg7;
      inp_next (u);
    }
    else
      u->mapen = &itab_gF_op0FAE[reg];
  }
}

/* ============================================================================= search_map() -
   Searches the x86 opcode table for the instruction corresponding to the opcode given by next byte 
   in the byte stream.
   ============================================================================= */
extern void search_map (UD *u)
{

  if (0x0F == inp_curr (u))
    search_2byte_insn (u);
  else
    search_1byte_insn (u);

  u->mnemonic = u->mapen->mnemonic;
  u->dest_opnd_number= u->mapen->dest_num;
  u->src_opnd_number= u->mapen->src_num;
  u->src_opnd_start= u->mapen->src_start;
}
