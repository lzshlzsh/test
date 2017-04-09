CC := g
CXX := g++
CFLAGS := -Wall -g -O3 #-mabi=n32 -march=loongson2f 
CXXFLAGS := $(CFLAGS) -std=c++0x
LDFLAGS := -static #-Wl,-T,x86.ld

HFILE := helper.h
NOTARGETS := helper.o


OBJS := $(patsubst %.c, %.o, $(wildcard *.c))
OBJS += $(patsubst %.cpp, %.o, $(wildcard *.cpp))

OBJS := $(filter-out $(NOTARGETS), $(OBJS))

TARGETS := $(patsubst %.o, %, $(OBJS))

.PHONY: all clean

all: $(TARGETS)
$(TARGETS) : $(NOTARGETS) $(HFILE)
$(NOTARGETS) : $(HFILE)

clean:
	$(RM) $(TARGETS) $(OBJS) $(NOTARGETS)


% : %.c 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

% : %.cpp 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


