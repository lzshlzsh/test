#ifndef _OPTIMIZATION_H
#define _OPTIMIZATION_H

#include "ir.h"

#define AVAIL_REG_NUM  32

#define LOOP_UNREDUCIBLE    0x1 
#define LOOP_CONTAIN_JUMPIN 0x2
#define LOOP_OPT_CANCLED    0x4
#define LOOP_OPT_REGION     0x8

#define MAXNOUTLP   150
#define MAXNINNLP   300
#define MAXNREGION  20

#define MAXNREM     1000
#define MAXNREMINS  6000

#define REM_TYPE_NUM   40
extern int rem_weight[REM_TYPE_NUM];

typedef enum {SB_R_EBP, SB_R_ESP}STACK_BASE;
typedef enum {
    REM_NONE,
    TRAN_DEST, TRAN_SRC,
    TRAN_SRC_D02, TRAN_SRC_D01, TRAN_SRC_D0,
    TRAN_SRC_D1, TRAN_SRC_D2, TRAN_SRC_D3, TRAN_SRC_D4,
    TRAN_SRC_D5,
    TRAN_XMM_DEST, TRAN_XMM_SRC,
    TRAN_XMM_SRC_D02, TRAN_XMM_SRC_D01, TRAN_XMM_SRC_D0,
    TRAN_XMM_SRC_D1, TRAN_XMM_SRC_D2, TRAN_XMM_SRC_D3, TRAN_XMM_SRC_D4,
    TRAN_XMM_SRC_D5,
    LOAR_DEST, LOAR_SRC,
    LOAR_SRC_D0, LOAR_SRC_D1, LOAR_SRC_D2, LOAR_SRC_D3, LOAR_SRC_D4,
    LOAR_SRC_D5,
    XMM_DEST, XMM_SRC,
    XMM_SRC_D0, XMM_SRC_D1, XMM_SRC_D2, XMM_SRC_D3, XMM_SRC_D4,
    XMM_SRC_D5,
    MMX_OPER, FR_OPER,
    REM_MAX
}REM_TYPE;


typedef enum {
    EX_NONE,
    
    EX_R8, EX_R9, EX_R10, EX_R11, 
    EX_R12, EX_R13, EX_R14, EX_R15,
    
    EX_XMM8, EX_XMM9, EX_XMM10, EX_XMM11, 
    EX_XMM12, EX_XMM13, EX_XMM14, EX_XMM15, 
    
    EX_MM0, EX_MM1, EX_MM2, EX_MM3, 
    EX_MM4, EX_MM5, EX_MM6, EX_MM7,

    EX_XMM0, EX_XMM1, EX_XMM2, EX_XMM3, 
    EX_XMM4, EX_XMM5, EX_XMM6, EX_XMM7, 

    EX_ALIAS_MEM
}AVAIL_REGS;

typedef struct {
    INSINDEX    _iins;
    REM_TYPE    _rem_type;
    INT16       _weight;
    INT16       _operand_no;
}REM_INS;


typedef struct {
    INT32       _offset;
    ARRAY      *_rem_instr;
    AVAIL_REGS  _allotted_reg;
    UINT8       _xmm_order;
    UINT8       _rem_size;
    INT16       _gpr_num;
    INT16       _xmm_num;
    INT16       _trans_num;
    INT16       _trans_xmm_num;
    INT16       _fr_num;
    INT32       _weight;
    INT32       _need_sync;

    REMINDEX    _next;
}REM;

typedef struct {
    BBINDEX     _ibb;
    REMINDEX    _rem_list;
    UINT32      _rem_num;
    REGIONINDEX _next;
}REGION;

typedef struct {
  BBINDEX       _entry;
  UINT32        _flag;
  ARRAY        *_member;
  ARRAY        *_exit;

  UINT32        _instr_num;
  UINT32        _call_num;
  UINT32        _samples;

  INNLPINDEX    _inner;
  INNLPINDEX    _next;
}INNER_LOOP;

typedef struct {
    BBINDEX     _entry;
    UINT32      _flag;
    ARRAY       *_member;
    ARRAY       *_exit;

    REMINDEX    _rem_list;
    UINT32      _rem_num;

    UINT32      _instr_num;
    UINT32      _call_num;
    UINT32      _samples;

    INNLPINDEX  _inner;
    REGIONINDEX      _region;
}OUTER_LOOP;

extern OUTER_LOOP  *aOutLoop;
extern INNER_LOOP  *aInnLoop;
extern REGION      *aRegion;
extern REM         *aRem;
extern REM_INS     *aRemIns;

extern OUTLPINDEX  nOutLp;
extern INNLPINDEX  nInnLp;
extern REGIONINDEX nRegion;
extern REMINDEX    nRem;
extern RMINSINDEX  nRemIns;


extern void LoopRemInit();
extern void LoopRemFree();
extern RMINSINDEX RemInsNew();
extern REMINDEX RemNew();
extern void RemCalWeight(REMINDEX irem);
extern REMINDEX RemSearch(REMINDEX irem, int offset);
extern void RemListSort(OUTLPINDEX iloop);
extern void RemListSortRegion(OUTLPINDEX iloop);
extern INNLPINDEX InnLoopNew();
extern OUTLPINDEX OutLoopNew();

#endif
