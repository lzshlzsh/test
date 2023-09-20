/*******************************************************************************
* PROJECT:Dynamic registerization of Stack variables 
* File Name:mem_manage.h    
* Author:Jianjun Li
* Abstract:Definition of the types which are used in the mem Management and 
          Declare the interface functions
* Date:10/19/2008
* Copy Right: ACT. ICT
********************************************************************************/

#ifndef _MEM_MANAGE_H_
#define _MEM_MANAGE_H_

#include "common_types.h"

#define CODE_CACHE_START    0x7000000
#define MMAP_AREA_START     0x50000000
#define STACK_AREA_START    0xa0000000
#define SHARE_MEM_START     0xf0000000

#define INSTR_CACHE_SIZE (5*1024*1024-65536)
#define GLOBAL_V_SIZE    (65536)
#define SHMEM_POOL_SIZE  (3*1024*1024)

#define SIZE_OF_TAG  8

typedef struct {
    ADDR p_cache_start;    //start address of the whole native-code cache
    ADDR p_cache_free;    //start address of the current available space
    ADDR cache_free_size;    //size of the current available space
} CODE_CACHE;

typedef struct {
    ADDR base_addr;
    int magic_num;
    int current_index;
}MALLOC_POOL;

typedef struct pool_tag {
    int size;
    ADDR32 next;
}POOL_TAG;

typedef struct {
    ADDR base_addr;
    int size;
    POOL_TAG *free_list;
}CALLOC_POOL;


typedef struct {
    ADDR base_addr;
    int size;
    POOL_TAG *free_list;
}SHMEM_POOL;

typedef struct {
    CODE_CACHE _code_cache_info;
    ADDR _global_mem;
    SHMEM_POOL _share_mem;
}MEM_MANAGER;

#define PAGE_SIZE 0x1000

#define IMAGE_STACK_SIZE        0x400000    //4M
#define PROTECT_STACK_SIZE      0x40000     //256K

typedef struct {
    ADDR _image_stack_base;
    ADDR _shadow_stack_base;
}STACK_FRAME;

extern STACK_FRAME *opt_stack;
extern INT32 alias_mem_offset;
extern ADDR vm_stack_base;
extern UINT32 vm_stack_size;

extern MEM_MANAGER mm_pool;
extern ADDR curr_code_ptr;

extern void MmInit();
extern void MmRelease();
extern void CodeCacheAlloc(UINT32 size);
extern ADDR MmAllocGlobalV(int size);
extern ADDR MmAllocShMem (int size);
extern void MmFreeShMem(ADDR base_addr);
extern void StackInit();
#endif

