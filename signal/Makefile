CC := gcc
CXX := g++
CFLAGS := -g -Wall -msse3 -mfpmath=sse #-D__USE_GNU
LDFLAGS := #-lm -ldl -lpthread

CXXFLAGS := ${CFLAGS}

FILES := $(wildcard *.c)
TARGETS := $(patsubst %.c, %, ${FILES})
FILES := $(wildcard *.cpp)
TARGETS += $(patsubst %.cpp, %, ${FILES})

.PHONY: all clean

all: ${TARGETS}

clean:
	${RM} ${TARGETS}
