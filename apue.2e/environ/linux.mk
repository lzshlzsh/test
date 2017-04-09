include ../Make.defines.linux

FILES= doatexit testjmp.opt testjmp getrlimit hello1 hello1.static

all:	$(FILES)

testjmp:	testjmp.c
		$(CC) $(CFLAGS) -o testjmp testjmp.c $(LDFLAGS) $(LDLIBS)

testjmp.opt:	testjmp.c
		$(CC) $(CFLAGS) -O -o testjmp.opt testjmp.c $(LDFLAGS) $(LDLIBS)

hello1.static: hello1.c
	$(CC) $(CFLAGS) -static -o $@ $^ $(LDFLAGS) $(LDLIBS)

clean:
		rm -f *.o $(FILES)
