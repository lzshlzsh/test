CC := gcc
CXX := g++
CFLAGS := -Wall -msse3 -mfpmath=sse -g
CFLAGS += -std=c++0x
LDFLAGS := -lm -ldl -lpthread #-static
LDFLAGS += -fopenmp

CXXFLAGS := ${CFLAGS}

FILES := $(wildcard *.c)
TARGETS := $(patsubst %.c, %, ${FILES})
FILES := $(wildcard *.cpp)
TARGETS += $(patsubst %.cpp, %, ${FILES})

.PHONY: all clean

all: ${TARGETS}

clean:
	${RM} ${TARGETS}
