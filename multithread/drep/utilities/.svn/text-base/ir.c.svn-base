#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include "mem_manage.h"
#include "utility.h"
#include "optimization.h"

#define Hash(addr)   (int)((((addr) >> 16) + ((addr) & 0xffff)) % HASH_TABLE_SIZE)

#define MapGprToBit(greg)   (1<<(greg-BT_R_EAX))
#define MapXmmToBit(xmm)    (1<<(xmm-BT_R_XMM0+16))

EXEFILE     aFile;
FUNCTION    *aFun;
BLOCK       *aBb;
BBLINK      *aBblk;
INSTR       *aIns;

FUNINDEX    nFun = INVALID + 1;
BBINDEX     nBb = INVALID + 1;
BBLKINDEX   nBblk = INVALID + 1;
INSINDEX    nIns = INVALID + 1;

BBINDEX     *HashTable;
FUNINDEX    ifun;

INSINDEX InstrNew () {
    int i;
    ASSERT(nIns<MAXNINS, ("Instruction array is overflow.\n"));

    aIns[nIns]._addr = p_instr_c->_addr;
    aIns[nIns]._addr_next = p_instr_c->_next_instr_addr;
    aIns[nIns]._op = p_instr_c->_op;
    aIns[nIns]._opndnum = p_instr_c->_operandnumber;
    aIns[nIns]._src_opnd_num = p_instr_c->_src_opnd_number;
    aIns[nIns]._dest_opnd_num = p_instr_c->_dest_opnd_number;
    aIns[nIns]._src_opnd_start = p_instr_c->_src_opnd_start;

    for(i=0; i<3; i++) {
        aIns[nIns]._operand[i].type = p_instr_c->_operand[i].type;
        aIns[nIns]._operand[i].size = p_instr_c->_operand[i].size;
        aIns[nIns]._operand[i].lval.uqword = p_instr_c->_operand[i].lval.uqword;
        aIns[nIns]._operand[i].base = p_instr_c->_operand[i].base;
        aIns[nIns]._operand[i].index = p_instr_c->_operand[i].index;
        aIns[nIns]._operand[i].scale = p_instr_c->_operand[i].scale;
    }
    
    aIns[nIns]._prefix = p_instr_c->_prefix;

    return (nIns++);
}

BBLKINDEX BblkNew () {
    ASSERT(nBblk<MAXNBBLK, ("Block link array is overflow.\n"))
    return (nBblk++);
}

BBINDEX BbNew () {
    ASSERT(nBb<MAXNBB, ("Block array is overflow.\n"))
    return (nBb++);
}

void BbAddInstr (BBINDEX jbb, INSINDEX jins) {
    int i;
    char *instr_ptr;
    
    if(aBb[jbb]._ins_num == 0)
        aBb[jbb]._ins_first = aBb[jbb]._ins_last = jins;
    else
        aBb[jbb]._ins_last = jins;

    aBb[jbb]._ins_num ++;
    aIns[jins]._ibb = jbb;

    if(jins == aBb[jbb]._ins_first)
        aIns[jins]._prev = INVALID;
    else {
        aIns[jins]._prev = jins-1;
        aIns[jins-1]._succ = jins;
    }
    
    aIns[jins]._succ = INVALID;

    aIns[jins]._size = aIns[jins]._addr_next - aIns[jins]._addr;
    instr_ptr = (char *)(ADDR)aIns[jins]._addr;
    for(i=0; i<aIns[jins]._size; i++)
        aIns[jins]._binary[i] = instr_ptr[i];

    for(i=0; i<aIns[jins]._opndnum; i++) {
        if(aIns[jins]._op!=BT_Ilea && aIns[jins]._operand[i].type==BT_OP_MEM && aIns[jins]._operand[i].base==aFun[ifun]._rem_base\
            && aIns[jins]._operand[i].index==BT_NONE && aIns[jins]._operand[i].lval.sdword > aFun[ifun]._max_off)
            aFun[ifun]._max_off = aIns[jins]._operand[i].lval.sdword;

        if(aIns[jins]._operand[i].type == BT_OP_MEM) {
            aIns[jins]._use |= MapGprToBit(aIns[jins]._operand[i].base);
            if(aIns[jins]._operand[i].index != BT_NONE)
                aIns[jins]._use |= MapGprToBit(aIns[jins]._operand[i].index);
        }
        else if(aIns[jins]._operand[i].type == BT_OP_REG) {
            REGISTER_TYPE reg_type = aIns[jins]._operand[i].base;  //map %al, %ax to %eax
            if(reg_type <= BT_R_BL)
                reg_type = reg_type-BT_R_AL+BT_R_EAX;
            else if(reg_type <= BT_R_DIL)
                reg_type = reg_type-BT_R_AH+BT_R_EAX;
            else if(reg_type <= BT_R_DI && reg_type >= BT_R_AX)
                reg_type = reg_type-BT_R_AX+BT_R_EAX;

            if(i<aIns[jins]._dest_opnd_num)
                aIns[jins]._def |= MapGprToBit(reg_type);
            if(i>=aIns[jins]._src_opnd_start)
                aIns[jins]._use |= MapGprToBit(reg_type);
        }
        else if(aIns[jins]._operand[i].type == BT_OP_XMMREG) {
            if(i<aIns[jins]._dest_opnd_num)
                aIns[jins]._def |= MapXmmToBit(aIns[jins]._operand[i].base);
            if(i>=aIns[jins]._src_opnd_start)
                aIns[jins]._use |= MapXmmToBit(aIns[jins]._operand[i].base);
        }
    }
}

BBINDEX BbGetSucc (BBINDEX jbb, int n) {
    int i;
    if (n >= aBb[jbb]._succ_bb_num)
        return INVALID;
    BBLKINDEX jbblk = aBb[jbb]._succ_bb;
    for (i=0; i<n; i++) {
        jbblk = aBblk[jbblk]._next;
    }
    return aBblk[jbblk]._ibb;
}

void HashInsert (BBINDEX jbb) {
    int hash_value = Hash(aBb[jbb]._entry_addr);
    aBb[jbb]._next_hash = HashTable[hash_value];
    HashTable[hash_value] = jbb;
}

BBINDEX HashSearch (ADDR32 addr) {
    int hash_value = Hash(addr);
    BBINDEX jbb = HashTable[hash_value];
    
    while (jbb) {
        if(aBb[jbb]._entry_addr==addr)
            return jbb;
        jbb = aBb[jbb]._next_hash;
    }
    
    return INVALID;
}

FUNINDEX FunNew (ADDR32 entry_addr) {
    ASSERT(nFun<MAXNFUNC, ("Function array is overflow.\n"));
    aFun[nFun]._entry_addr = entry_addr;
    aFun[nFun]._func_size = FileGetFunSize(entry_addr);
    aFun[nFun]._rem_base = BT_R_ESP;
    if(strstr(aFile._file_name, "gromacs") || strstr(aFile._file_name, "cactusADM"))
        aFun[nFun]._rem_base = BT_R_EBP;
    return (nFun++);
}

BOOL FunOptimize() {
    OUTLPINDEX iOutLp;
    INNLPINDEX iInnLp;
    REGIONINDEX iregion;
    INSINDEX iins;

    OUTPUT(("Function 0x%lx\n", aFun[ifun]._entry_addr));
        
    if(aFun[ifun]._flag & FUN_HAS_OPTIMIZED)
        return TRUE;

    if(((*(UINT32 *)(ADDR)aFun[ifun]._entry_addr)&0x00ffffff)==0xec8b55) {
        aFun[ifun]._flag |= FUN_NO_RESTORE_ESP;
    }
    else if((*(UINT32 *)(ADDR)(aFun[ifun]._entry_addr)&0x00ffffff)==0xdc8b53) {
        aFun[ifun]._flag |= FUN_NO_RESTORE_ESP;
        //aFun[ifun]._rem_base = BT_R_EBP;
    }

    Disassemble();

    LoopRemInit();

    ControlFlowAnalysis();

    MapSamplesToFun();

    iOutLp = 1;
    while(iOutLp < nOutLp) {
        if(aOutLoop[iOutLp]._flag & LOOP_UNREDUCIBLE) {
            iInnLp = aOutLoop[iOutLp]._inner;
            while(iInnLp) {
                if(aInnLoop[iInnLp]._samples*5 > aOutLoop[iOutLp]._samples*4) {
                    ArrayFree(aOutLoop[iOutLp]._exit);
                    ArrayFree(aOutLoop[iOutLp]._member);

                    aOutLoop[iOutLp]._entry = aInnLoop[iInnLp]._entry;
                    aOutLoop[iOutLp]._flag = aInnLoop[iInnLp]._flag;
                    aOutLoop[iOutLp]._member = aInnLoop[iInnLp]._member;
                    aOutLoop[iOutLp]._exit = aInnLoop[iInnLp]._exit;
                    aOutLoop[iOutLp]._instr_num = aInnLoop[iInnLp]._instr_num;
                    aOutLoop[iOutLp]._call_num = aInnLoop[iInnLp]._call_num;
                    aOutLoop[iOutLp]._samples = aInnLoop[iInnLp]._samples;
                    aOutLoop[iOutLp]._inner = aInnLoop[iInnLp]._inner;
                    aOutLoop[iOutLp]._region = INVALID;

                    break;
                }
                iInnLp = aInnLoop[iInnLp]._next;
            }
        }
        iOutLp ++;
    }

  #ifdef _PROMOTE_NON_STACK
    if(strstr(aFile._file_name, "milc")) {
        PromoteNonStack();

        LoopRemFree();

    #ifdef _DUMP_INSTR
        DumpInstrCompare();
    #endif
        aFun[ifun]._flag |= FUN_HAS_OPTIMIZED;
        return TRUE;
    }
  #endif
    //ResolvePfmonStall();
    SelectOptTarget();
    if(aFun[ifun]._flag&FUN_OPT_CANCLED)
        return FALSE;
    
    DataFlowAnalysis();

    if(aFun[ifun]._opt_target!=FUNC) {
        iOutLp = 1;
        while(iOutLp < nOutLp) {
            if(aOutLoop[iOutLp]._flag&LOOP_OPT_CANCLED) {
                iOutLp ++;
                continue;
            }
            if(aOutLoop[iOutLp]._flag&LOOP_OPT_REGION) {
                iregion = aOutLoop[iOutLp]._region;
                while(iregion) {
                    aOutLoop[iOutLp]._rem_num += aRegion[iregion]._rem_num;
                    iregion = aRegion[iregion]._next;
                }
            }
            if(aOutLoop[iOutLp]._rem_num<3)
                aOutLoop[iOutLp]._flag |= LOOP_OPT_CANCLED;

            iOutLp ++;
        }

        iOutLp = 1;
        while(iOutLp < nOutLp) {
            if((aOutLoop[iOutLp]._flag&LOOP_OPT_CANCLED)==0)
                break;
            iOutLp ++;
        }
        if(iOutLp==nOutLp) {
            aFun[ifun]._flag |= FUN_OPT_CANCLED;
            return FALSE;
        }
    }
    else if(aOutLoop[1]._rem_num < 6) {
        aFun[ifun]._flag |= FUN_OPT_CANCLED;
        return FALSE;
    }

    curr_code_ptr = mm_pool._code_cache_info.p_cache_free;
    aFun[ifun]._opt_code_addr = (ADDR32)curr_code_ptr;

#ifdef _NO_OPTIMIZE
    {
      BBINDEX ibb;
      char *p_code_cache, *p_instr_code;
      int i, offset;

      ibb = aFun[ifun]._ibb_entry;
      while(ibb) {
        aBb[ibb]._opt_code_addr = (ADDR32)curr_code_ptr;
        aBb[ibb]._flag |= BB_OPTIMIZED;
        iins = aBb[ibb]._ins_first;

        while(iins < aBb[ibb]._ins_last) {
            p_code_cache = (char *)curr_code_ptr;
            p_instr_code = (char *)aIns[iins]._addr;
            for(i=0; i<aIns[iins]._size; i++)
                p_code_cache[i] = p_instr_code[i];

            curr_code_ptr += aIns[iins]._size;
            
            iins ++;
        }

        if(aIns[iins]._op==BT_Icall) {
            ASSERT(*(char *)aIns[iins]._addr == (char)0xe8, ("Find callin or lcall.\n"));
            offset = aIns[iins]._addr_next + aIns[iins]._operand[0].lval.sdword - (int)curr_code_ptr - 5;
            *(char *)curr_code_ptr = 0xe8;
            *(int *)(curr_code_ptr+1) = offset;

            curr_code_ptr += 5;
        }
        else {
            p_code_cache = (char *)curr_code_ptr;
            p_instr_code = (char *)aIns[iins]._addr;
            for(i=0; i<aIns[iins]._size; i++)
                p_code_cache[i] = p_instr_code[i];

            curr_code_ptr += aIns[iins]._size;
        }
        
        ibb = aBb[ibb]._next;
      }

      CodeCacheAlloc(curr_code_ptr-mm_pool._code_cache_info.p_cache_free);

      return TRUE;
    }
#endif

#ifndef _STATISTIC
    if(!(aFun[ifun]._flag&FUN_OPT_CANCLED)) {
        GenerateOptimizedCode();
    #ifdef _DUMP_INSTR
        DumpInstrCompare();
    #endif
    }
#else
    if(!(aFun[ifun]._flag&FUN_OPT_CANCLED)) {
        GenerateProfilingCode();
        //DumpInstrCompare();
    }
#endif

    CodeCacheAlloc(curr_code_ptr-mm_pool._code_cache_info.p_cache_free);
    LoopRemFree();

    aFun[ifun]._flag |= FUN_HAS_OPTIMIZED;

    return TRUE;
}

void ReadElfHeaders () {
    int i, str_size;
    int text_section_index, func_index;
    Elf32_Ehdr *p_ehdr;
    Elf32_Shdr *CurrentSec;
    int symt_num, nSectionAll, SymbolType;
    Elf32_Sym *p_symbol_table, *CurrentSymbol;
    char *p_string_table, *SecHdrStrTab, *SecName;
    
    aFile._fd = open(aFile._file_name, O_RDONLY);
    ASSERT(aFile._fd!=-1,("Error occurred when open file.\n"))

    struct stat stat_data;
    int fs = fstat(aFile._fd,&stat_data);
    ASSERT(fs==0, ("fstat error!\n"));
    void *file_base = mmap(0, stat_data.st_size, PROT_READ, MAP_SHARED, aFile._fd, 0);
    ASSERT(file_base!=(void*)-1, ("mmap exe file error!\n"));
    
    p_ehdr = (Elf32_Ehdr *) file_base;
    //if (p_ehdr->e_type != ET_EXEC || p_ehdr->e_machine != EM_386)
    Elf32_Shdr *SecHdr = (Elf32_Shdr *)(((char*)p_ehdr) + p_ehdr->e_shoff);
    Elf32_Phdr *PHdr = (Elf32_Phdr *)(((char*)p_ehdr) + p_ehdr->e_phoff);
    Elf32_Shdr *SecHdrStrSec = SecHdr +  p_ehdr->e_shstrndx;
    SecHdrStrTab = (char *)(((char *)p_ehdr) + SecHdrStrSec->sh_offset);
    nSectionAll = p_ehdr->e_shnum;

    aFile._entry = p_ehdr->e_entry;
    aFile._phent_size = p_ehdr->e_phentsize;
    aFile._phnum = p_ehdr->e_phnum;
    aFile._phdr_addr = 0x8048000 + p_ehdr->e_phoff;
    str_size = aFile._phent_size*aFile._phnum;
    aFile._p_phdr = (Elf32_Phdr *)MmAllocShMem(str_size);
    memcpy(aFile._p_phdr, PHdr, str_size);
    
    for (i=0; i<nSectionAll; ++i) {
        CurrentSec = SecHdr + i;
        SecName = SecHdrStrTab+CurrentSec->sh_name;
        
        if (strcmp(SecName, ".symtab")==0) {
            p_symbol_table = (Elf32_Sym *)(((char*)p_ehdr) + CurrentSec->sh_offset);
            symt_num = CurrentSec->sh_size/sizeof(Elf32_Sym);
        }
        else if (strcmp(SecName, ".text")==0) {
            text_section_index = i;
            aFile._text_start_addr = CurrentSec->sh_addr;
            aFile._text_end_addr = CurrentSec->sh_addr + CurrentSec->sh_size;
        }
        else if (strcmp(SecName, ".strtab")==0) {
            p_string_table = (char*) (((char*)p_ehdr) + CurrentSec->sh_offset);
        }
    }

    func_index = 0;

    MESSAGE(p_symbol_table==NULL,("No symbol table found.\n"));

    for (i=0; i<symt_num; ++i) {
        CurrentSymbol = p_symbol_table + i;
        SymbolType = ELF32_ST_TYPE(CurrentSymbol->st_info);

        if (SymbolType==STT_FUNC && CurrentSymbol->st_shndx==text_section_index)
            func_index++;
    }

    aFile._p_func_info = (FUNC_INFO *)MmAllocShMem(sizeof(FUNC_INFO)*func_index);
    func_index = 0;
    
    for (i=0; i<symt_num; ++i) {
        CurrentSymbol = p_symbol_table + i;
        SymbolType = ELF32_ST_TYPE(CurrentSymbol->st_info);
        if (SymbolType==STT_FUNC && CurrentSymbol->st_shndx==text_section_index) {
            if(strcmp(p_string_table+CurrentSymbol->st_name, "main")==0)
                aFile._main_entry = CurrentSymbol->st_value;
            else if(strcmp(p_string_table+CurrentSymbol->st_name, "__mmap")==0)
                aFile._mmap_sc_addr = CurrentSymbol->st_value + 0x2c;
            else if(strcmp(p_string_table+CurrentSymbol->st_name, "__mmap64")==0)
                aFile._mmap64_sc_addr = CurrentSymbol->st_value + 0x33;
            else if(strcmp(p_string_table+CurrentSymbol->st_name, "__mremap")==0)
                aFile._mremap_sc_addr = CurrentSymbol->st_value + 0x17;
            else if(strcmp(p_string_table+CurrentSymbol->st_name, "__munmap")==0)
                aFile._munmap_sc_addr = CurrentSymbol->st_value + 0xa;
            else if(strcmp(p_string_table+CurrentSymbol->st_name, "_exit")==0)
                aFile._exit_sc_addr = CurrentSymbol->st_value;
            
            aFile._p_func_info[func_index]._entry_addr = CurrentSymbol->st_value;
            aFile._p_func_info[func_index]._end_addr = CurrentSymbol->st_value + CurrentSymbol->st_size;
            aFile._p_func_info[func_index]._sample_count = 0;
            aFile._p_func_info[func_index]._exec_count = 0;

            func_index++;
        }
    }

    aFile._func_index = func_index;

    munmap(file_base, stat_data.st_size);
}

void FileInit () {
    HashTable = (BBINDEX *)MmAllocShMem(HASH_TABLE_SIZE*sizeof(BBINDEX));
    p_instr_c = (INSTR_CUT *)MmAllocShMem(sizeof(INSTR_CUT));
    reg_spill_addr = (ADDR32)MmAllocGlobalV(16);
    fpsave_addr = (ADDR32)MmAllocGlobalV(112);
    aMmapHistory = (UINT32 *)MmAllocGlobalV(8*MAX_MMAP_HIS_NUM);
}

int FileGetFunSize(ADDR32 callee_entry) {
    int i;
    for(i=0; i<aFile._func_index; i++) {
        if(aFile._p_func_info[i]._entry_addr==callee_entry)
            return aFile._p_func_info[i]._end_addr - aFile._p_func_info[i]._entry_addr;
    }
    return 0;
}

int FileGetFunIndex(ADDR32 fun_entry) {
    int i;
    for(i=0; i<aFile._func_index; i++) {
        if(aFile._p_func_info[i]._entry_addr==fun_entry)
            return i;
    }
    return -1;
}

void FileLoadExe() {
    ADDR map_start, mapped_addr;
    UINT32 map_size;
    int i, prot, page_off, file_off;
    int zero_fd = open("/dev/zero", O_RDONLY);

    for(i=0; i<aFile._phnum; i++) {
        if(aFile._p_phdr[i].p_type != PT_LOAD)
            continue;
        prot = 0;
        page_off = aFile._p_phdr[i].p_vaddr & ((UINT32)aFile._p_phdr[i].p_align - 1);
        map_start = aFile._p_phdr[i].p_vaddr & ~((UINT32)aFile._p_phdr[i].p_align - 1);
        map_size = aFile._p_phdr[i].p_memsz + page_off;
        file_off = aFile._p_phdr[i].p_offset - page_off;

        if(aFile._p_phdr[i].p_flags & PF_R)
            prot |= PROT_READ;
        if(aFile._p_phdr[i].p_flags & PF_W)
            prot |= PROT_WRITE;
        if(aFile._p_phdr[i].p_flags & PF_X)
            prot |= PROT_EXEC;

        if(aFile._p_phdr[i].p_memsz!=aFile._p_phdr[i].p_filesz && (prot&PROT_WRITE)) {
            mapped_addr = (ADDR)mmap((void *)map_start, map_size, prot, MAP_FIXED | MAP_PRIVATE, zero_fd, 0);
            lseek(aFile._fd, aFile._p_phdr[i].p_offset, SEEK_SET);
            read(aFile._fd, (void *)(ADDR)aFile._p_phdr[i].p_vaddr, aFile._p_phdr[i].p_filesz);
        }
        else {
            mapped_addr = (ADDR)mmap((void *)map_start, map_size, prot, MAP_FIXED | MAP_PRIVATE, aFile._fd, file_off);
            ASSERT(mapped_addr!=-1, ("map failed!\n"))
        }
    }

    close(zero_fd);
    close(aFile._fd);
}


#ifdef _STATISTIC
void PrintStatistic() {
    int i;
    for(i=0; i<nFun; i++) {
        if((aFun[ifun]._flag&FUN_HAS_OPTIMIZED) && aFun[ifun]._opt_code_addr) {
            fprintf(dreplog, "Function Entry: 0x%x\n\texec count: %u\n", aFun[ifun]._entry_addr, aFun[ifun]._exec_count);
            fprintf(dreplog, "\tstatic instr num: %u  static opt num: %u\n", aFun[ifun]._static_instr_num, aFun[ifun]._static_opt_num);
            fprintf(dreplog, "\tdynamic instr num: %lld  dynamic opt num: %lld\n", aFun[ifun]._dyn_instr_num, aFun[ifun]._dyn_opt_num);
            fprintf(dreplog, "\tcall count: %u\n", aFun[ifun]._call_count);
        }
    }

    fprintf(dreplog, "---------------------------------------------------------------------------\n");
}
#endif

