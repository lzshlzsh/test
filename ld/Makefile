CC := gcc
CXX := g++
CFLAGS := -g -m32 -Wall -msse3  #-mfpmath=sse
LDFLAGS := -Wl,-T,myld.ld

CXXFLAGS := ${CFLAGS}

FILES := $(wildcard *.c)
TARGETS := $(patsubst %.c, %, ${FILES})
FILES := $(wildcard *.cpp)
TARGETS += $(patsubst %.cpp, %, ${FILES})

.PHONY: all clean

all: ${TARGETS}

clean:
	${RM} ${TARGETS}
