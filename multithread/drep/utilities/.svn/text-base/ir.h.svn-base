#ifndef _IR_H
#define _IR_H

#include <elf.h>
#include "dec_types.h"
#include "utility.h"

#define HASH_TABLE_SIZE 2000   //the size of the block hash table

#define FUN_HAS_DISASEM     0x1
#define FUN_HAS_OPTIMIZED   0x2
#define FUN_NO_RESTORE_ESP  0x4
#define FUN_OPT_CANCLED     0x20

#define BB_ENTRY_FLAG    0x1   // Is BB an entry?
#define BB_EXIT_FLAG     0x2   //Is bb an exit?
#define BB_INS_SCHEDULED 0x4
#define BB_OPTIMIZED     0x8

#define MAXNFUNC    (16)
#define MAXNBB      (1024*15)
#define MAXNBBLK    (1024*60)
#define MAXNINS     (1024*75)

typedef enum {
  T_COMMON,
  T_ENTRY,
  T_CALLIN,
  T_CALL_RELATIVE,
  T_CALL_FAR,
  T_BRANCH,     /* Loop instruction belongs to BRANCH type */
  T_JUMPIN,
  T_JUMP_RELATIVE,
  T_JUMP_FAR,
  T_RET,
  T_HALT,
  T_CALLBACK_RET,
} INSTR_TYPE;

typedef struct {
    ADDR32  _addr;
    ADDR32  _addr_next;
    OPCODE  _op;
    INT8    _opndnum;
    INT8    _src_opnd_num;
    INT8    _dest_opnd_num;
    INT8    _src_opnd_start;
    OPERAND _operand[3];
    PREFIX  _prefix;
    BBINDEX _ibb;

    ADDR32  _opt_addr;

    char    _binary[16];
    INT32   _size;

    UINT32  _use;
    UINT32  _def;

    INSINDEX _prev;
    INSINDEX _succ;
}INSTR;


typedef struct {
    BBINDEX _ibb;
    BBLKINDEX  _next;
}BBLINK;


typedef struct
{
    ADDR32    _entry_addr;        /*block's entry virtual address */
    ADDR32    _end_addr;          /*vaddr of next instruction of the block end */
    UINT32  _flag;              /* flag */
    UINT32  _ins_num;           /*the number of instructions */
    INSTR_TYPE  _last_instr_type;    /*type of this block's real last instruction */
    INSINDEX    _ins_first;     /*address of the first ir1 instruction */
    INSINDEX    _ins_last;      /*address of the last ir1 instruction */
    ADDR32    _opt_code_addr;     /*where does this block put in native code buf */
    INT32   _pred_bb_num;       /*the number of predecessor blocks */
    BBLKINDEX   _pred_bb;       /*predecessor blocks, */
    INT32   _succ_bb_num;       /*the number of successor blocks */
    BBLKINDEX   _succ_bb;       /* successor blocks */
    BBINDEX _next;              /*next block of this unit */
    BBINDEX _next_hash;         /*next block of the same hash value */

    INT32   _dfn_pre;
    INT32   _cfg_llink;
    BBINDEX _idom_bb;
    UINT32  _samples;
#ifdef _STATISTIC
    UINT32  _opt_ins_num;
#endif
    FUNINDEX _ifun;
}BLOCK;                              //end of the class C_TU


typedef struct {
    INSTR_TYPE _type;       /*instruction type */
    ADDR32  _next_ins_addr;    /*next instr addr of the last instr addr in the block */
    ADDR32  _target_addr;      /*the target addr of last instr */
    BBINDEX _current_bb; /*current block index */
}BT_INFO;

typedef enum {LOOP, FUNC}OPTIMIZE_TARGET;

typedef struct {
    ADDR32  _entry_addr;
    INT32   _func_size;
    UINT32  _flag;
    BBINDEX _ibb_head;        //the head pointer of the current function's block list
    BBINDEX _ibb_entry;

    ADDR32  _opt_code_addr;   //the start address for the optimized function
    ADDR32  _old_esp;
    INT32   _max_off;         //the offset of the function's arguments
    INT32   _caller_off;
    INT32   _callee_arg_off;
    INT32   _push_num;

    OPTIMIZE_TARGET _opt_target;
    REGISTER_TYPE _rem_base;

    UINT32  _samples;

  #ifdef _STATISTIC
    UINT32  _exec_count;
    UINT32  _static_instr_num;
    UINT32  _static_opt_num;
    UINT32  _call_count;
    UINT64 _dyn_instr_num;
    UINT64 _dyn_opt_num;
 #endif
}FUNCTION;

typedef struct {
    ADDR32  _entry_addr;
    ADDR32  _end_addr;
    UINT32  _sample_count;
    UINT32  _exec_count;
}FUNC_INFO;

typedef struct {
    char    *_file_name;
    INT32   _fd;
    ADDR32  _entry;
    ADDR32  _main_entry;

    UINT32  _mmap_sc_addr;
    UINT32  _mmap64_sc_addr;
    UINT32  _mremap_sc_addr;
    UINT32  _munmap_sc_addr;

    UINT32  _exit_sc_addr;

    UINT32  _phent_size;
    UINT32  _phnum;
    UINT32  _phdr_addr;
    Elf32_Phdr *_p_phdr;

    INT32   _para_num;
    INT32   _env_num;
    char    **_para_list;
    char    **_env_list;

    INT32   _func_index;
    FUNC_INFO *_p_func_info;
    UINT64  _tot_sample_count;

    UINT32  _text_start_addr;
    UINT32  _text_end_addr;

    ARRAY   *_opt_func;
}EXEFILE;

extern EXEFILE     aFile;
extern FUNCTION    *aFun;
extern BLOCK       *aBb;
extern BBLINK      *aBblk;
extern INSTR       *aIns;

extern FUNINDEX    nFun;
extern BBINDEX     nBb;
extern BBLKINDEX   nBblk;
extern INSINDEX    nIns;

extern BBINDEX     *HashTable;
extern FUNINDEX    ifun;


extern void Disassemble ();
extern void GetCalleeArgNum(ADDR32 entry_addr);
#ifdef _DUMP_INSTR
extern void DumpInstrCompare();
#endif
#ifdef _DEBUG
extern void DumpInstr(ADDR32 start, int mode, int n);
#endif

extern void ControlFlowAnalysis();
extern void DataFlowAnalysis();

extern void GenMmapSyscall();
extern void SelectOptTarget();
extern void GenerateOptimizedCode();
extern void GenerateProfilingCode();

extern void ReadElfHeaders();
extern void ProfileCallCount(ARRAY *hotfunc);
extern void MapSamplesToFun();

#ifdef _STATISTIC
extern void PrintStatistic();
#endif

extern void BtExit();

#ifdef _PROMOTE_NON_STACK
extern void PromoteNonStack();
#endif

#endif

