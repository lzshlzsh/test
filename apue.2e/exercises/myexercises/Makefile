
WKDIR := /home/lzs/programming/test/apue.2e
CC := gcc
EXTRALIBS := -lpthread -lrt
LDDIR := -L$(WKDIR)/lib
LDLIBS := $(WKDIR)/lib/libapue.a $(EXTRALIBS)
CFLAGS := -g -I$(WKDIR)/include -Wall $(EXTRA) #-D_GNU_SOURCE
COMPILE.c := $(CC) $(CFLAGS) $(CPPFLAGS) -c
LINK.c := $(CC) $(CFLAGS) $(CPPFLAGS) $(LDDIR) $(LDFLAGS)


EXES := $(patsubst %.c, %, $(wildcard *.c))

.PHONY: all clean

all: $(EXES)


clean:
	$(RM) $(EXES)
