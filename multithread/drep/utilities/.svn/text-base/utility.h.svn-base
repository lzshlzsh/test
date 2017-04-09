#ifndef UTILITY_H
#define UTILITY_H
#include "common_types.h"

#define USELESS 0

#define MONITOR_DEBUG   0x0001
#define DISASSEM_DBUG   0x0002
#define FLOWALS_DEBUG   0x0004
#define MEMPOOL_DEBUG   0x0008
#define CODEGEN_DEBUG   0x0010

extern int DebugLevel;
extern int SyncSignal;
extern FILE *dreplog;

extern UINT32 in_monitoring;

extern ADDR32 reg_spill_addr;
extern ADDR32 fpsave_addr;

#define MAX_MMAP_HIS_NUM  2000
extern UINT32 iMapHist;
extern UINT32 *aMmapHistory;

extern void Abort_Location (const char * file_name, int  line_number );
extern void EmitMessage (const char *fmt, ... );

#define RED "31"
#define GREEN "32" 
#define YELLOW "33"

extern void SetColor (char * color);
extern void UnsetColor ();

#define INVALID 0
#define Error_File dreplog

#define PROLOGUE(m) EmitMessage(m ": ")

#define __clflush(x)  __asm__ __volatile__("clflush %0\n\t" ::"m"(x))


#ifdef _DEBUG
#define FATAL(cond,mess)   {if (cond) {PROLOGUE("FATAL"); Abort_Location ( __FILE__, __LINE__ ); EmitMessage mess; exit(-1);}}
#define ERROR(mess)     {PROLOGUE("ERROR"); Abort_Location ( __FILE__, __LINE__ ); EmitMessage mess; exit(-1);}
#define ASSERT(cond,mess)  {if (!(cond)) {PROLOGUE("ASSERT"); Abort_Location ( __FILE__, __LINE__ ); EmitMessage mess; asm("int $3");}}
#define WARNING(mess)  {PROLOGUE("WARNING"); Abort_Location ( __FILE__, __LINE__ ); EmitMessage mess;}
#define MESSAGE(cond,mess) {if (cond) {EmitMessage mess;}}
#define OUTPUT(mess)    {EmitMessage mess;}
#else
#define FATAL(cond,mess)
#define ERROR(mess)
#define ASSERT(cond,mess)
#define WARNING(mess)
#define MESSAGE(cond,mess)
#define OUTPUT(mess)
#endif

#define IS_MOV_ESP_EBP(instr_code)  ((*(UINT16 *)(instr_code))==(UINT16)0xe589 || (*(UINT16 *)(instr_code))==(UINT16)0xec8b)
#define IS_SUB_IMM_ESP(instr_code)  (((*(UINT16 *)(instr_code)) & (UINT16)0xfffd)==(UINT16)0xec81)
#define IS_ADD_IMM_ESP(instr_code)  (((*(UINT16 *)(instr_code)) & (UINT16)0xfffd)==(UINT16)0xc481)
#define IS_JUMPIN_REG(instr_code)   (((*(UINT16 *)(instr_code)) & (UINT16)0xf8ff)==(UINT16)0xe0ff)

#define IS_TRANSFER_INS(t_op)    (t_op==BT_Imov || (t_op>=BT_Imovq&&t_op<=BT_Imovsd_sse) || (t_op>=BT_Imovapd&&t_op<=BT_Imovups) || (t_op==BT_Imovd) || (t_op==BT_Imovss))
#define IS_LONGLATENCY_INS(t_op)   ((t_op>=BT_Idivsd && t_op<=BT_Isqrtsd) || (t_op>=BT_Idivss && t_op<=BT_Isqrtss) || (t_op>=BT_Idiv && t_op<=BT_Iimul) || (t_op>=BT_Idivpd && t_op<=BT_Imulps))

#define ARRAY_INIT_SIZE  10
#define QUEUE_INIT_SIZE  10
#define STACK_INIT_SIZE  10

typedef struct{
    ELEM_TYPE  *ArrayBase;
    INT32   Capcity;
    INT32   NumOfElem;
}ARRAY;

typedef struct{
    ELEM_TYPE  *QueueBase;
    INT32   Capcity;
    INT32   NumOfElem;
    INT32   FrontIndex;
    INT32   BelowIndex;
    ARRAY   *Deleted;
}QUEUE;

typedef struct{
    ELEM_TYPE  *StackBase;
    INT32   Capcity;
    INT32   NumOfElem;
}STACK;

extern ARRAY *t_array;

extern ARRAY *ArrayNew();
extern void ArrayAdd(ARRAY *a, ELEM_TYPE element);
extern void ArrayDel(ARRAY *a, ELEM_TYPE element);
extern INDEX ArrayElemIndex(ARRAY *a, ELEM_TYPE element);
extern void ArraySort(ARRAY *a);
extern BOOL ArrayExist(ARRAY *a, ELEM_TYPE element);
extern BOOL ArraySExist(ARRAY *a, ELEM_TYPE element);
extern void ArraySetAdd(ARRAY *a, ELEM_TYPE element);
extern void ArrayAppend(ARRAY *a, ARRAY *b);
extern void ArrayFree (ARRAY *a);
extern QUEUE *QueueNew();
extern BOOL QueueExist (QUEUE *q, ELEM_TYPE elem);
extern BOOL QueueExisted (QUEUE *q, ELEM_TYPE elem);
extern void QueuePushFast (QUEUE *q, ELEM_TYPE elem);
extern void QueuePush (QUEUE *q, ELEM_TYPE elem);
extern ELEM_TYPE QueuePopFast (QUEUE *q);
extern ELEM_TYPE QueuePop (QUEUE *q);
extern void QueueSort (QUEUE *q);
extern void QueueFree (QUEUE *q);
extern STACK *StackNew();
extern BOOL StackExist (STACK *s, ELEM_TYPE elem);
extern void StackPush (STACK *s, ELEM_TYPE elem);
extern ELEM_TYPE StackPop (STACK *s);
extern void StackFree (STACK *s);

#ifdef _DUMP_INSTR
extern void Instr_Dump_ATT();
#endif
#ifdef _DEBUG
extern void PrintLoopMember(ARRAY *t_array);
#endif
extern void SignalInit();

#endif

