#ifndef PERF_SAMPLE_H
#define PERF_SAMPLE_H

#define PAGE_SIZE  0x1000
#define SMPL_PERIOD	266000ULL
#define N_WAKEUP_EVENTS 1000
#define BUFFER_PAGES    8 /* size of buffer payload (must be power of 2)*/

#define N_SMPL_HASH_TABLE   2000
#define MAXNSMPL  6000

#ifndef F_SETOWN_EX
#define F_SETOWN_EX	15
#define F_GETOWN_EX	16

#define F_OWNER_TID	0
#define F_OWNER_PID	1
#define F_OWNER_PGRP	2

struct f_owner_ex {
	int	type;
	pid_t	pid;
};
#endif

typedef struct {
    ADDR32  _ip;
    UINT32  _count;
    SMPLINDEX   _next;
}SAMPLE;

extern volatile UINT32 unprocessed_sample;

extern void pfmon_init();
extern void pfmon_fini();
extern void pfmon_start();
extern void pfmon_stop();
extern int AnalyzeSamples();

#endif

