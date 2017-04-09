#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>
#include <pthread.h>
#include "utility.h"
#include "ir.h"
#include "mem_manage.h"
#include "perf_sample.h"

#define PauseMainThread()  {in_patching = 1; kill(gPid, SyncSignal);}
#define ResumeMainThread() {in_patching = 0;}

static pid_t gPid = 0;
UINT32 in_patching = 0;
UINT32 in_suspending = 0;

#ifdef _STATISTIC
void BtExit() {
    PrintStatistic();
    exit(0);
}
#endif

void SyncSigHandler(int sig){
    in_suspending = 1;
	while(in_patching) {
		usleep(10000);
	}
}

void* FileOptimize() {
    int ret_v, ifuninfo, i, j;
    FUNINDEX jfun, bfun;
    ADDR min, max, t_addr;
    ADDR32 fun_entry;
    ARRAY *hotfunc, *procedfunc;

  #ifdef _HELPER_THREAD
    sigset_t mask_set;
    sigemptyset(&mask_set);
    sigaddset(&mask_set, SyncSignal);
    sigprocmask(SIG_BLOCK, &mask_set, NULL);
    
    sleep(1);  //to skip the initial phase
    hotfunc = ArrayNew();
    procedfunc = ArrayNew();
    while(1) {
        ret_v = 0;
        while(ret_v==0) {
            if(unprocessed_sample)
                ret_v = AnalyzeSamples();
            else
                usleep(2000);
        }

        hotfunc->NumOfElem = 0;
        for(j=0; j<aFile._func_index; j++) {
           if(aFile._tot_sample_count < aFile._p_func_info[j]._sample_count*10)
               ArrayAdd(hotfunc, j);
        }

        i = 0;
        while(i<hotfunc->NumOfElem) {
            if(ArrayExist(procedfunc, hotfunc->ArrayBase[i])) {
                for(j=i; j<hotfunc->NumOfElem-1; j++)
                    hotfunc->ArrayBase[j] = hotfunc->ArrayBase[j+1];

                hotfunc->NumOfElem --;
            }
            else {
                ArrayAdd(procedfunc, hotfunc->ArrayBase[i]);
                i ++;
            }
        }

        if(hotfunc->NumOfElem) {
            min = aFile._text_end_addr;
            max = 0;
            for(i=0; i<hotfunc->NumOfElem; i++) {
                ifuninfo = hotfunc->ArrayBase[i];
                if(min > aFile._p_func_info[ifuninfo]._entry_addr)
                    min = aFile._p_func_info[ifuninfo]._entry_addr;
                if(max < aFile._p_func_info[ifuninfo]._entry_addr)
                    max = aFile._p_func_info[ifuninfo]._entry_addr;
            }
            min = min & 0x0fffff000;
            max = max + 5;

            PauseMainThread();
            mprotect((void *)min, max-min, PROT_READ | PROT_WRITE | PROT_EXEC);
            ProfileCallCount(hotfunc);
            mprotect((void *)min, max-min, PROT_READ | PROT_EXEC);
            ResumeMainThread();

            pfmon_start();

            ret_v = 0;
            while(ret_v==0) {
                if(unprocessed_sample)
                    ret_v = AnalyzeSamples();
                else
                    usleep(1000);
            }

            PauseMainThread();
            mprotect((void *)min, max-min, PROT_READ | PROT_WRITE | PROT_EXEC);

            //delete the instrumentation instruction
            for(i=0; i<hotfunc->NumOfElem; i++) {
                ifuninfo = hotfunc->ArrayBase[i];
                t_addr = (ADDR)(ADDR32)(aFile._p_func_info[ifuninfo]._entry_addr + *(UINT32 *)((ADDR)aFile._p_func_info[ifuninfo]._entry_addr+1) + 11);

                for(j=0; j<5; j++)
                    *(char *)((ADDR)aFile._p_func_info[ifuninfo]._entry_addr+j) = *(char *)(t_addr+j);
            }
            //ResumeMainThread();

            for(i=1; i<hotfunc->NumOfElem; i++) {
                ifuninfo = hotfunc->ArrayBase[i];
                for(j=i; j>0&&aFile._p_func_info[ifuninfo]._sample_count>aFile._p_func_info[hotfunc->ArrayBase[j-1]]._sample_count; j--)
                    hotfunc->ArrayBase[j] = hotfunc->ArrayBase[j-1];
                hotfunc->ArrayBase[j] = ifuninfo;
            }

            bfun = nFun;
            for(i=0; i<hotfunc->NumOfElem; i++) {
                ifuninfo = hotfunc->ArrayBase[i];
                if((aFile._tot_sample_count<aFile._p_func_info[ifuninfo]._sample_count*10 && aFile._p_func_info[ifuninfo]._sample_count*50>aFile._p_func_info[ifuninfo]._exec_count) ||\
                    (aFile._tot_sample_count<aFile._p_func_info[ifuninfo]._sample_count*5 && aFile._p_func_info[ifuninfo]._sample_count*200>aFile._p_func_info[ifuninfo]._exec_count)) {
                    fun_entry = aFile._p_func_info[ifuninfo]._entry_addr;
                    for(jfun=1; jfun<nFun; jfun++) {
                        if(aFun[jfun]._entry_addr==fun_entry) {
                            ifun = jfun;
                            break;
                        }
                    }

                    if(jfun==nFun) {
                        ifun = FunNew(fun_entry);
                        FunOptimize();
                    }
                }
            }

            //PauseMainThread(); 
            while(bfun < nFun) {
                fun_entry = aFun[bfun]._entry_addr;
                if((aFun[bfun]._flag&FUN_OPT_CANCLED)==0 && aFun[bfun]._opt_code_addr) {
                    *(char *)(ADDR)(aFun[bfun]._entry_addr) = 0xe9;
                    *(int *)(ADDR)(aFun[bfun]._entry_addr+1) = (int)(aFun[bfun]._opt_code_addr-aFun[bfun]._entry_addr)-5;
                }

                bfun ++;
            }

            mprotect((void *)min, max-min, PROT_READ | PROT_EXEC);

            ResumeMainThread();
        }
        sleep(10);
        pfmon_start();
    }
  #else
    hotfunc = ArrayNew();

    if(strstr(aFile._file_name, "bzip2")) {
        ArrayAdd(hotfunc, 0x804f780);
        ArrayAdd(hotfunc, 0x8054240);
    }
    else if(strstr(aFile._file_name, "mcf")) {
        ArrayAdd(hotfunc, 0x804a040);
        ArrayAdd(hotfunc, 0x8049920);
        ArrayAdd(hotfunc, 0x804a780);
    }
    else if(strstr(aFile._file_name, "hmmer")) {
        ArrayAdd(hotfunc, 0x805f9b0);
    }
    else if(strstr(aFile._file_name, "h264ref")) {
        ArrayAdd(hotfunc, 0x80a25b0);
        ArrayAdd(hotfunc, 0x8090fa0);
    }
    else if(strstr(aFile._file_name, "bwaves")) {
        ArrayAdd(hotfunc, 0x804ea80);
    }
    else if(strstr(aFile._file_name, "gamess")) {
        ArrayAdd(hotfunc, 0x8a54e6c);
        ArrayAdd(hotfunc, 0x879d874);
        //ArrayAdd(hotfunc, 0x8784cdc);
    }
    else if(strstr(aFile._file_name, "milc")) {
        //ArrayAdd(hotfunc, 0x80609c0);
        //ArrayAdd(hotfunc, 0x805daf0); 
        ArrayAdd(hotfunc, 0x8051600);
        //ArrayAdd(hotfunc, 0x80511a0);
    }
    else if(strstr(aFile._file_name, "zeusmp")) {
        ArrayAdd(hotfunc, 0x809be60); 
        ArrayAdd(hotfunc, 0x80931a0); 
        //ArrayAdd(hotfunc, 0x8057af0);
    }
    else if(strstr(aFile._file_name, "gromacs")) {
        ArrayAdd(hotfunc, 0x8095360);
    }
    else if(strstr(aFile._file_name, "cactusADM")) {
        ArrayAdd(hotfunc, 0x805af00);
    }
    else if(strstr(aFile._file_name, "leslie3d")) {
        ArrayAdd(hotfunc, 0x804e960); 
        ArrayAdd(hotfunc, 0x805e220); 
        ArrayAdd(hotfunc, 0x8053180); 
        ArrayAdd(hotfunc, 0x805c3d0); 
        ArrayAdd(hotfunc, 0x806dcc0); 
        ArrayAdd(hotfunc, 0x806f5f0); 
    }
    else if(strstr(aFile._file_name, "namd")) {
        ArrayAdd(hotfunc, 0x805b3f4); 
        ArrayAdd(hotfunc, 0x804d2a4); 
        ArrayAdd(hotfunc, 0x80971f0); 
        ArrayAdd(hotfunc, 0x80584b4); 
        ArrayAdd(hotfunc, 0x808c750); 
    }
    else if(strstr(aFile._file_name, "soplex")) {
        ArrayAdd(hotfunc, 0x809c3f0);
        ArrayAdd(hotfunc, 0x80681a0);  //first input
        ArrayAdd(hotfunc, 0x8093c10);
        ArrayAdd(hotfunc, 0x8093990);
        ArrayAdd(hotfunc, 0x8069410);
    }
    else if(strstr(aFile._file_name, "GemsFDTD")) {
        ArrayAdd(hotfunc, 0x805e710); 
        ArrayAdd(hotfunc, 0x8075a60); 
        ArrayAdd(hotfunc, 0x8053340);
        //ArrayAdd(hotfunc, 0x804fe50);
        ArrayAdd(hotfunc, 0x806e330); 
    }
    else if(strstr(aFile._file_name, "lbm")) {
        ArrayAdd(hotfunc, 0x80486c0);
    }
    else if(strstr(aFile._file_name, "sphinx")) {
        ArrayAdd(hotfunc, 0x8054740);
        //ArrayAdd(hotfunc, 0x80517b0);  //contain function call in hot loop
    }
    else if(strstr(aFile._file_name, "calculix")) {
        ArrayAdd(hotfunc, 0x80f7280);
        ArrayAdd(hotfunc, 0x805a440);
    }
    else if(strstr(aFile._file_name, "dealII")) {
        ArrayAdd(hotfunc, 0x8276460);
    }
    else if(strstr(aFile._file_name, "libquantum")) {
        ArrayAdd(hotfunc, 0x805ea70);
        ArrayAdd(hotfunc, 0x804a6a0);
    }
    else if(strstr(aFile._file_name, "astar")) {
        ArrayAdd(hotfunc, 0x804a840);
    }
   
    //ArrayAdd(hotfunc, 0x804ac20); //179.art
    //ArrayAdd(hotfunc, 0x8575dcc); //481.wrf

    if(hotfunc->NumOfElem==0)
        return;

    min = aFile._text_end_addr;
    max = 0;
    for(i=0; i<hotfunc->NumOfElem; i++) {
        fun_entry = hotfunc->ArrayBase[i];

        if(min > fun_entry)
            min = fun_entry;
        if(max < fun_entry)
            max = fun_entry;

        for(jfun=1; jfun<nFun; jfun++) {
            if(aFun[jfun]._entry_addr==fun_entry) {
                ifun = jfun;
                break;
            }
        }

        if(jfun==nFun) {
            ifun = FunNew(fun_entry);
            FunOptimize();
        }
    }

    min = min & 0x0fffff000;
    max = max + 5;
    mprotect((void *)min, max-min, PROT_READ | PROT_WRITE | PROT_EXEC);

    jfun = 1;
    while(jfun < nFun) {
        if((aFun[jfun]._flag&FUN_OPT_CANCLED)==0 && aFun[jfun]._opt_code_addr) {
            *(char *)(ADDR)(aFun[jfun]._entry_addr) = 0xe9;
            *(int *)(ADDR)(aFun[jfun]._entry_addr+1) = (int)(aFun[jfun]._opt_code_addr-aFun[jfun]._entry_addr)-5;
        }
        jfun ++;
    }

    mprotect((void *)min, max-min, PROT_READ | PROT_EXEC);
  #endif
}

void usage() {
    fprintf (stderr, "usage: drep [-h] [-s size] program [arguments...]\n"
            "-h                      Print this help\n"
            "-s<size>                Set the system stack size(bytes) (default = %ld)\n",
            vm_stack_size);
    exit(1);
}

int main(int argc, char *argv[], char **arge) {
    pthread_t opt_thread;
    int optind, t_size, t_num, i;
    char *t_string;
    void **t_env;
    
    dreplog = fopen("dreplog.debug", "w");
    MmInit();

    //Analysis the parameter
    if(argc<2) {
        OUTPUT(("The number of arguments is too few.\n"));
        usage();
    }

    optind =1;
    while(optind<argc && argv[optind] && argv[optind][0]=='-') {
        if(strcmp(argv[optind], "-h") == 0)
            usage();
        else if(strncmp(argv[optind], "-s", 2) == 0)
            sscanf (argv[optind], "-s%u", &vm_stack_size);
        else
            fprintf(stderr, "Illegal options for drep!\n");

        optind ++;
    }
    if (!argv[optind]) {
        fprintf(stderr, "Illegal options for drep!\n");
        return -1;
    }

    for (t_string=argv[optind], t_size=1; t_string!=NULL && *t_string!='\0'; t_string++, t_size++);
    t_string = (char *)MmAllocGlobalV(t_size);
    memcpy(t_string, argv[optind], t_size);
    aFile._file_name = t_string;

    aFile._para_num = argc - optind;
    if(aFile._para_num) {
        aFile._para_list = (char **)MmAllocGlobalV((aFile._para_num + 1)*sizeof(char *));
        for (i=optind; i<argc; i++) {
            for (t_string=argv[i], t_size=1; t_string!=NULL && *t_string!='\0'; t_string++, t_size++);
            aFile._para_list[i-optind] = (char *)MmAllocGlobalV(t_size);
            memcpy(aFile._para_list[i-optind], argv[i], t_size);
        }
    }

    for (t_env=(void **)(arge), t_num=0; t_env!=NULL && *t_env; t_env++, t_num++);
    aFile._env_num = t_num;
    aFile._env_list = (char **)MmAllocGlobalV((t_num+1)*sizeof(char *));
    for (i=0; i<t_num; i++) {
        for (t_string=arge[i], t_size=0; t_string!=NULL && *t_string!='\0'; t_string++, t_size++);
        t_size++;

        aFile._env_list[i] = (char *)MmAllocGlobalV(t_size);
        memcpy(aFile._env_list[i], arge[i], t_size);
    }

    if(strstr(aFile._file_name, "bwaves"))
        vm_stack_size = 1000000000;

    ReadElfHeaders();
    FileInit();
    FileLoadExe();
    
    StackInit();
    GenMmapSyscall();
    SignalInit();

#ifdef _HELPER_THREAD
    if(SIG_ERR == signal(SyncSignal, SyncSigHandler))
        fprintf(stderr, "Error while registering sync signal.\n");
    if (0 != pthread_create(&opt_thread, NULL, FileOptimize, NULL))
        fprintf(stderr, "Can not create helper thread.\n");

    pfmon_init();
#else
    FileOptimize();
#endif
    __asm__ __volatile__(
        "xor %%rsp, %%rsp\n\t" \
        "mov %0, %%esp\n\t" \
        "push $0x23\n\t" \
        "push %1\n\t" \
        "mov $0x2b, %%eax\n\t" \
        "mov %%eax, %%ds\n\t" \
        "mov %%eax, %%es\n\t" \
        "xor %%rax, %%rax\n\t" \
        "xor %%rbx, %%rbx\n\t" \
        "xor %%rcx, %%rcx\n\t" \
        "xor %%rdx, %%rdx\n\t" \
        "xor %%rsi, %%rsi\n\t" \
        "xor %%rdi, %%rdi\n\t" \
        "lretq \n\t"
        :
        :"m"(vm_stack_base), "m"(aFile._entry));

#ifdef _HELPER_THREAD
    pthread_join(opt_thread, NULL);
#endif
    return 0;
}


