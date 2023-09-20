#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "mem_manage.h"
#include "utility.h"
#include "optimization.h"

#if 0
void ResolvePfmonOut() {
    FILE *fp = fopen("../../exe/pfmon-out", "r");
    int counts, i, j;
    ADDR32 code_addr;
    float percent, cumulation;
    char buf[256];
    FUNC_INFO temp_fi;
    BBINDEX ibb;
    OUTLPINDEX iOutLp;
    INNLPINDEX iInnLp, jInnLp;

    FATAL(fp==NULL,("Error while open file pfmon-out.\n"));
    fgets(buf, 256, fp);
    while(!feof(fp)) {
        if(buf[0]!='#') {
            sscanf(buf, "%d %f%% %f%% 0x%x", &counts, &percent, &cumulation, &code_addr);
            for(i=0; i<aFile._func_index; i++) {
                if(code_addr>=aFile._p_func_info[i]._entry_addr && code_addr<aFile._p_func_info[i]._end_addr) {
                    aFile._p_func_info[i]._sample_count += counts;
                    break;
                }
            }
        }
        else if(strstr(buf, "total samples")){
            sscanf(buf, "# total samples          : %d", &counts);
            aFile._tot_sample_count += counts;
        }
        
        fgets(buf, 256, fp);
    }

    fclose(fp);

    for(i=1; i<aFile._func_index; i++) {
       temp_fi = aFile._p_func_info[i];
       for(j=i; j>0&&temp_fi._sample_count>aFile._p_func_info[j-1]._sample_count; j--)
           aFile._p_func_info[j] = aFile._p_func_info[j-1];
       aFile._p_func_info[j] = temp_fi;
    }

    OUTPUT(("#total sample counts: %d\nindex\tstart    \tend      \tsize\tpercent\tsample count\n", aFile._tot_sample_count));

    for(i=0; i<aFile._func_index; i++) {
        if(aFile._p_func_info[i]._sample_count*20>aFile._tot_sample_count) {
            OUTPUT(("[%d]:\t0x%lx\t0x%lx\t%d\t%d\%\t%d\n", i, aFile._p_func_info[i]._entry_addr, aFile._p_func_info[i]._end_addr,\
            aFile._p_func_info[i]._end_addr-aFile._p_func_info[i]._entry_addr, aFile._p_func_info[i]._sample_count*100/aFile._tot_sample_count, aFile._p_func_info[i]._sample_count));
        
            ifun = FunNew(aFile._p_func_info[i]._entry_addr);
            Disassemble();
            LoopRemInit();
            ControlFlowAnalysis();

            fp = fopen("../../exe/pfmon-out", "r");
            fgets(buf, 256, fp);
            while(!feof(fp)) {
                if(buf[0]!='#') {
                    sscanf(buf, "%d %f%% %f%% 0x%x", &counts, &percent, &cumulation, &code_addr);
                    if(code_addr>=aFun[ifun]._entry_addr && code_addr<aFun[ifun]._entry_addr+aFun[ifun]._func_size) {
                        ibb = aFun[ifun]._ibb_head;
                        while(ibb) {
                            if(code_addr>=aBb[ibb]._entry_addr && code_addr<=aBb[ibb]._end_addr) {
                                aBb[ibb]._samples += counts;
                                iOutLp = 1;
                                while(iOutLp<nOutLp) {
                                    if(ArrayExist(aOutLoop[iOutLp]._member, ibb)) {
                                        aOutLoop[iOutLp]._samples += counts;
                                        iInnLp = aOutLoop[iOutLp]._inner;
                                        break;
                                    }

                                    iOutLp += 1;
                                }
                                break;
                            }
                            ibb = aBb[ibb]._next;
                        }
                    }
                }
                
                fgets(buf, 256, fp);
            }

            iOutLp = 1;
            while(iOutLp<nOutLp) {
                OUTPUT(("\tLoop %d:\t%d\t%d\%\n", iOutLp, aOutLoop[iOutLp]._samples, aOutLoop[iOutLp]._samples*100/aFile._p_func_info[i]._sample_count));
                OUTPUT(("\tLoop member: "));
                for(j=0; j<aOutLoop[iOutLp]._member->NumOfElem; j++) {
                    if(j%5==0)
                        OUTPUT(("\n\t"));
                    OUTPUT(("\t0x%lx %d%% ", aBb[aOutLoop[iOutLp]._member->ArrayBase[j]]._entry_addr, aBb[aOutLoop[iOutLp]._member->ArrayBase[j]]._samples*100/aFile._p_func_info[i]._sample_count));
                }

                OUTPUT(("\n"));

                iOutLp ++;
            }

            fclose(fp);

            LoopRemFree();
        }
    }

   #if 0
    OUTPUT(("#total sample counts: %d\nindex\tstart    \tend      \tsize\tpercent\tsample count\n", aFile._tot_sample_count));
    for(i=0; i<aFile._func_index; i++)
        OUTPUT(("[%d]:\t0x%lx\t0x%lx\t%d\t%d\%\t%d\n", i, aFile._p_func_info[i]._entry_addr, aFile._p_func_info[i]._end_addr,\
        aFile._p_func_info[i]._end_addr-aFile._p_func_info[i]._entry_addr, aFile._p_func_info[i]._sample_count*100/aFile._tot_sample_count, aFile._p_func_info[i]._sample_count))
   #endif

   exit(1);
}
#endif

void PrintOptFunInfo() {
    int i;
    OUTPUT(("#total sample counts: %d\nindex\tstart    \tend      \tsize\tpercent\tsample count\texec count\tsamples/call\n", aFile._tot_sample_count));
    for(i=0; i<aFile._func_index; i++) {
        if(aFile._p_func_info[i]._sample_count > aFile._tot_sample_count/20) {
            if(aFile._p_func_info[i]._exec_count && aFile._p_func_info[i]._sample_count>aFile._p_func_info[i]._exec_count)
            OUTPUT(("[%d]:\t0x%lx\t0x%lx\t%d\t%.2f\%\t%12d\t%10d\t%12.5f\n", i, aFile._p_func_info[i]._entry_addr, aFile._p_func_info[i]._end_addr,\
        aFile._p_func_info[i]._end_addr-aFile._p_func_info[i]._entry_addr, aFile._p_func_info[i]._sample_count*100/aFile._tot_sample_count, \
        aFile._p_func_info[i]._sample_count, aFile._p_func_info[i]._exec_count, aFile._p_func_info[i]._sample_count/aFile._p_func_info[i]._exec_count))
        }
        else
            break;
    }
}

void ProfileCallCount(ARRAY *hotfunc) {
    ADDR new_pc;
    ADDR min, max;
    char *code_cache_ptr;
    int i, j, ifuninfo;

    for(i=0; i<hotfunc->NumOfElem; i++) {
        ifuninfo = hotfunc->ArrayBase[i];
        new_pc = aFile._p_func_info[ifuninfo]._entry_addr;
        while(new_pc-aFile._p_func_info[ifuninfo]._entry_addr<5) {
            p_instr_c->_addr = new_pc;
            new_pc = (ADDR)decode (p_instr_c, 32);
        }
        
        code_cache_ptr = (char *)mm_pool._code_cache_info.p_cache_free;

        //inc exec_count
        code_cache_ptr[0] = 0xff;
        code_cache_ptr[1] = 0x05;
        *(UINT32 *)((ADDR)code_cache_ptr+2) = (UINT32)(ADDR)(&(aFile._p_func_info[ifuninfo]._exec_count));

        //copy original instructions
        for(j=0; j<new_pc-aFile._p_func_info[ifuninfo]._entry_addr; j++)
            code_cache_ptr[j+6] = *(char *)((ADDR)aFile._p_func_info[ifuninfo]._entry_addr+j);

        //patch code
        *(char *)((ADDR)aFile._p_func_info[ifuninfo]._entry_addr) = (char)0xe9;
        *(int *)((ADDR)aFile._p_func_info[ifuninfo]._entry_addr+1) = (int)((ADDR)code_cache_ptr - aFile._p_func_info[ifuninfo]._entry_addr) -5;

        code_cache_ptr[j+6] = 0xe9;
        *(int *)((ADDR)code_cache_ptr+j+7) = (int)(new_pc-(ADDR)code_cache_ptr) - j - 11;

        CodeCacheAlloc(j+11);
    }
}

#ifndef _HELPER_THREAD
void MapSamplesToFun() {
    FILE *fp;
    int counts, i, j;
    ADDR32 code_addr;
    float percent, cumulation;
    char buf[256];
    BBINDEX ibb;
    OUTLPINDEX iOutLp;
    INNLPINDEX iInnLp;
    
    fp = fopen("../../exe/pfmon-out", "r");
    FATAL(fp==NULL,("Error while open file pfmon-out.\n"));
    fgets(buf, 256, fp);
    while(!feof(fp)) {
        if(buf[0]!='#') {
            sscanf(buf, "%d %f%% %f%% 0x%x", &counts, &percent, &cumulation, &code_addr);
            if(code_addr>=aFun[ifun]._entry_addr && code_addr<aFun[ifun]._entry_addr+aFun[ifun]._func_size) {
                aFun[ifun]._samples += counts;
                ibb = aFun[ifun]._ibb_head;
                while(ibb) {
                    if(code_addr>=aBb[ibb]._entry_addr && code_addr<=aBb[ibb]._end_addr) {
                        aBb[ibb]._samples += counts;
                        iOutLp = 1;
                        while(iOutLp<nOutLp) {
                            if(ArrayExist(aOutLoop[iOutLp]._member, ibb)) {
                                aOutLoop[iOutLp]._samples += counts;
                                iInnLp = aOutLoop[iOutLp]._inner;
                                while(iInnLp) {
                                    if(ArrayExist(aInnLoop[iInnLp]._member, ibb)) {
                                        aInnLoop[iInnLp]._samples += counts;
                                        break;
                                    }
                                    iInnLp = aInnLoop[iInnLp]._next;
                                }
                                break;
                            }

                            iOutLp += 1;
                        }
                        break;
                    }
                    ibb = aBb[ibb]._next;
                }
            }
        }
        
        fgets(buf, 256, fp);
    }
    fclose(fp);
}
#endif

