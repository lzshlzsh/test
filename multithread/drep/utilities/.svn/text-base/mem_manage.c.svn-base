/*******************************************************************************
* PROJECT:  Dynamic registerization of Stack variables 
* File Name:    instr_cache_manage.h    
* Author:       Jianjun Li
* Abstract: 
            Definition of the types which are used in the Instr Cache Management and 
            Declare the interface functions
* Date:     
            10/19/2008
* Copy Right: 
            ACT. ICT
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <pthread.h>
#include "mem_manage.h"
#include "utility.h"
#include "ir.h"

MEM_MANAGER mm_pool;
ADDR curr_code_ptr;

STACK_FRAME *opt_stack;
INT32 alias_mem_offset;
ADDR vm_stack_base;
UINT32 vm_stack_size = 0xa00000;    //10M

static pthread_mutex_t MallocLock = PTHREAD_MUTEX_INITIALIZER;

void MmInit() {
    ADDR ir_base;
    
    mm_pool._code_cache_info.p_cache_start = (ADDR)mmap((void *)CODE_CACHE_START,
            INSTR_CACHE_SIZE + GLOBAL_V_SIZE,
            PROT_READ | PROT_EXEC | PROT_WRITE,
            MAP_PRIVATE | MAP_FIXED |MAP_ANONYMOUS,
            -1,
            0);

    FATAL(mm_pool._code_cache_info.p_cache_start==(ADDR)MAP_FAILED,("Map code cache failed.\n"));

    mm_pool._code_cache_info.p_cache_free = mm_pool._code_cache_info.p_cache_start;
    mm_pool._code_cache_info.cache_free_size = INSTR_CACHE_SIZE;

    mm_pool._global_mem = mm_pool._code_cache_info.p_cache_start + INSTR_CACHE_SIZE;

    mm_pool._share_mem.base_addr = (ADDR)mmap((void *)SHARE_MEM_START, 
            SHMEM_POOL_SIZE + MAXNBB*sizeof(BLOCK) + MAXNBBLK*sizeof(BBLINK) + MAXNINS*sizeof(INSTR),
            PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_FIXED | MAP_ANONYMOUS,
            -1,
            0);
    FATAL(mm_pool._share_mem.base_addr==(ADDR)MAP_FAILED,("Map shared memory failed.\n"));
    mm_pool._share_mem.size = SHMEM_POOL_SIZE - MAXNFUNC*sizeof(FUNCTION);
    mm_pool._share_mem.free_list = (POOL_TAG *)(mm_pool._share_mem.base_addr);
    mm_pool._share_mem.free_list->size = mm_pool._share_mem.size - SIZE_OF_TAG;
    mm_pool._share_mem.free_list->next = 0;

    ir_base = mm_pool._share_mem.base_addr + mm_pool._share_mem.size;
    aFun = (FUNCTION *)ir_base;
    ir_base += MAXNFUNC*sizeof(FUNCTION);
    aBb = (BLOCK *)ir_base;
    ir_base += MAXNBB*sizeof(BLOCK);
    aBblk = (BBLINK *)ir_base;
    ir_base += MAXNBBLK*sizeof(BBLINK);
    aIns = (INSTR *)ir_base;
}

void MmRelease() {
    int ret_val = munmap ( (void *)(mm_pool._share_mem.base_addr), \
        SHMEM_POOL_SIZE + MAXNBB*sizeof(BLOCK) + MAXNBBLK*sizeof(BBLINK) + MAXNINS*sizeof(INSTR));
    ASSERT(ret_val==0,("Unmap shared memory failed.\n"));
}

void CodeCacheAlloc(UINT32 size) {
    if (mm_pool._code_cache_info.cache_free_size >= size)
    {
        mm_pool._code_cache_info.p_cache_free += size;
        mm_pool._code_cache_info.cache_free_size -= size;
    }
    else
        ERROR(("There is not enough space to store the optimized code!\n"));
}

ADDR MmAllocGlobalV(int size) {
    ADDR ret_addr;

    ASSERT(mm_pool._global_mem+size<CODE_CACHE_START+INSTR_CACHE_SIZE+GLOBAL_V_SIZE, ("The global memory pool is overflow.\n"));

    ret_addr = mm_pool._global_mem;
    mm_pool._global_mem += ((size+7)/8)*8;

    return ret_addr;
}
ADDR MmAllocShMem (int size) {
    ADDR ret_addr;
    POOL_TAG *current, *prior, *new_header;

#ifdef _HELPER_THREAD
    pthread_mutex_lock(&MallocLock);
#endif
    ASSERT(size!=0, ("The size of MmAlloc is 0.\n"))
    current = mm_pool._share_mem.free_list;
    prior = NULL;

    while(current) {
        if(current->size >= size) {
            if(current->size - size >=  4*SIZE_OF_TAG) {
                ret_addr = (ADDR)current + SIZE_OF_TAG;
                new_header = (POOL_TAG *) (ret_addr + size);
                new_header->size = current->size - size - SIZE_OF_TAG;
                new_header->next = current->next;
                if(prior)
                    prior->next = (ADDR32)(ADDR)new_header;
                else
                    mm_pool._share_mem.free_list = new_header;

                current->size = size;
                current->next = 0;
            }
            else {
                ret_addr = (ADDR)current + SIZE_OF_TAG;
                if(prior)
                    prior->next = current->next;
                else
                    mm_pool._share_mem.free_list = (POOL_TAG *)(ADDR)(current->next);

                current->next = 0;
            }

            break;
        }
        else {
            prior = current;
            current = (POOL_TAG *)(ADDR)(current->next);
        }
    }
#ifdef _HELPER_THREAD
     pthread_mutex_unlock(&MallocLock);
#endif

    MESSAGE(DebugLevel&MEMPOOL_DEBUG,("SHARE MEMORY POOL ALLOCATOR: addr = 0x%lx, size = 0x%x\n", ret_addr, size));
    FATAL(!current,("The share memory pool is overflow.\n"));

    return ret_addr;
}

void MmFreeShMem (ADDR base_addr) {
    POOL_TAG *current, *post, *prior;

    MESSAGE(DebugLevel&MEMPOOL_DEBUG,("SHARE MEMORY POOL FREE: addr = 0x%lx\n", base_addr));

    current = (POOL_TAG *)(base_addr - SIZE_OF_TAG);
    
    if(base_addr > mm_pool._share_mem.base_addr && base_addr < mm_pool._share_mem.base_addr + SHMEM_POOL_SIZE)
    {
        post = mm_pool._share_mem.free_list;
        prior = NULL;

        while(post)
        {
            if((ADDR)post == base_addr)
                return;
            if((ADDR)post > base_addr)
                break;
            else
            {
                prior = post;
                post = (POOL_TAG *)(ADDR)post->next;
            }
        }

        if(prior == NULL)
        {
            mm_pool._share_mem.free_list = current;
            if(post && ((base_addr + current->size) == ((ADDR)post - SIZE_OF_TAG)))
            {
                current->size = current->size + post->size + SIZE_OF_TAG;
                current->next = post->next;
            }
            else
                current->next = (ADDR32)(ADDR)post;
        }
        else
        {
            prior->next = (ADDR32)(ADDR)current;

            //combine the current and post
            if(post && ((base_addr + current->size) == ((ADDR)post - SIZE_OF_TAG)))
            {
                current->size = current->size + post->size + SIZE_OF_TAG;
                current->next = post->next;
            }
            else
                current->next = (ADDR32)(ADDR)post;

            if(((ADDR)prior+prior->size+SIZE_OF_TAG) == (base_addr - SIZE_OF_TAG))
            {
                prior->size = prior->size + current->size + SIZE_OF_TAG;
                prior->next = current->next;
            }
            
        }
    }
    else if(base_addr == 0)
    {
        WARNING(("The free address is NULL.\n"));
    }
    else
        ERROR(("The free address 0x%lx is not in the pool range.\n", base_addr));
    
}


void StackInit() {
    static char u_platform[] = "i686";
    //static char random_instr[]="1?T(ии\tT?\002_?x\\J:.i686";
    void **temp;
    int size, i;
    
    vm_stack_base = (ADDR)mmap((void *)STACK_AREA_START, vm_stack_size+PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    mprotect((void *)vm_stack_base, PAGE_SIZE, PROT_NONE);
    vm_stack_base = vm_stack_base + vm_stack_size + PAGE_SIZE;

  #ifndef _NO_STACK_SWITCH
    opt_stack = (STACK_FRAME *)MmAllocGlobalV(sizeof(STACK_FRAME));
    size = IMAGE_STACK_SIZE + PROTECT_STACK_SIZE;
    //the code to read the /proc/%u/maps, and init the base address of stack
    opt_stack->_image_stack_base = (ADDR)mmap((void *)(ADDR)(STACK_AREA_START+vm_stack_size+0x100000), \
    size, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_SHARED, 0, 0);

    //alias the stack memory using mremap
    opt_stack->_shadow_stack_base = (ADDR)mremap((void *)(opt_stack->_image_stack_base), 0, \
    size, MREMAP_MAYMOVE|MREMAP_FIXED, (void *)(opt_stack->_image_stack_base+size));
    
    mprotect((void *)(opt_stack->_image_stack_base), size, PROT_NONE);

    opt_stack->_image_stack_base += IMAGE_STACK_SIZE;
    opt_stack->_shadow_stack_base += IMAGE_STACK_SIZE;

    mprotect((void *)(opt_stack->_shadow_stack_base), PROTECT_STACK_SIZE, PROT_NONE);

    alias_mem_offset = (int)(opt_stack->_shadow_stack_base - opt_stack->_image_stack_base);

    opt_stack->_image_stack_base -= 0x10;
    opt_stack->_shadow_stack_base -= 0x10;

    MESSAGE(DebugLevel&CODEGEN_DEBUG,("IMAGE STACK BASE: 0x%lx\nALIAS STACK BASE: 0x%lx\n", opt_stack->_image_stack_base, \
        opt_stack->_shadow_stack_base));
  #endif
  
#define AUX_PUSH(id, val)  \
    do { \
        vm_stack_base = vm_stack_base - 4; \
        *(UINT32 *)vm_stack_base = val; \
        vm_stack_base = vm_stack_base - 4; \
        *(UINT32 *)vm_stack_base = id; \
        }while(0)

#define ARG_PUSH(val)  \
    do { \
        vm_stack_base = vm_stack_base - 4; \
        *(UINT32 *)vm_stack_base = val; \
        }while(0)
        
    AUX_PUSH(AT_NULL, 0);
    AUX_PUSH(AT_PLATFORM, (UINT32)(UINT64)u_platform);
    //AUX_PUSH(AT_EXECFN, (UINT32)(UINT64)(aFile._file_name));
    //AUX_PUSH(AT_RANDOM, (UINT32)(UINT64)random_instr);
    //AUX_PUSH(AT_SECURE, 0);
    AUX_PUSH(AT_EGID, getegid());
    AUX_PUSH(AT_GID, getgid());
    AUX_PUSH(AT_EUID, geteuid());
    AUX_PUSH(AT_UID, getuid());
    AUX_PUSH(AT_ENTRY, aFile._entry);
    AUX_PUSH(AT_FLAGS, 0);
    AUX_PUSH(AT_BASE, 0);
    AUX_PUSH(AT_PHNUM, aFile._phnum);
    AUX_PUSH(AT_PHENT, aFile._phent_size);
    AUX_PUSH(AT_PHDR, aFile._phdr_addr);
    AUX_PUSH(AT_CLKTCK, 0x64);
    AUX_PUSH(AT_PAGESZ, 0x1000);
    AUX_PUSH(AT_HWCAP, 0xbfebfbff);
    //AUX_PUSH(AT_SYSINFO_EHDR, );
    //AUX_PUSH(AT_SYSINFO, );

    /* push the enviroment variables into virtual stack in reverse order,use 0 as natural boundary */
    ARG_PUSH(0);
    for (i = aFile._env_num-1; i >= 0; i--)
        ARG_PUSH((UINT32)(UINT64)(aFile._env_list[i]));
    /* push the command-list parameter variables into virtual stack in reverse order,use 0 as
       natural boundary */
    if (aFile._para_num) {
        ARG_PUSH(0);
        for (i=aFile._para_num-1; i>=0; i--)
            ARG_PUSH((UINT32)(UINT64) aFile._para_list[i]);

        ARG_PUSH(aFile._para_num);
    }
#undef ARG_PUSH
#undef AUX_PUSH
}


