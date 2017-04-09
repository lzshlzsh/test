include ../Make.defines.linux
EXTRA=

PROGS := add2 add2stdio fifo1 myuclc pipe1 pipe2 pipe4 popen1 popen2 spipe4 tshm
PROGS += dev_zero_mmap pipe4-exerise

all:	${PROGS} tellwait.o

tellwait.o:	tellwait.c

dev_zero_mmap: dev_zero_mmap.o tellwait.o

clean:
	rm -f ${PROGS} ${TEMPFILES} *.o
