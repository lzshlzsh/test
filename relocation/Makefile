CC := gcc
CFLAGS := -g 
SOFLAGS := -shared -fPIC

EXE := main
SOS := foo.so goo.so

.PHONY: all clean

all: main

main: main.c header.h foo.so goo.so
	$(CC) -o $@  $(CFLAGS) $^

%.so: %.c
	$(CC) -o $@ $(CFLAGS) $(SOFLAGS) $^


clean:
	$(RM) $(EXE) $(SOS)

