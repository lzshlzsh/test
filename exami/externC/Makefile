
EXE := include
OBJS := include1.o include.o
CC := gcc
CXX := g++

.PHONY: all clean

all: $(EXE)

include1.o: include1.c
	$(CC) -c -g -o $@ $<
include.o: include.cpp 
	$(CXX) -c -g -o $@ $<


$(EXE): $(OBJS)
	$(CXX) -o $@ $^



clean:
	$(RM) $(EXE) $(OBJS)
