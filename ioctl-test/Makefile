CC := gcc
CXX := g++
#ARCH := -m32
CFLAGS := -g -Wall -msse3 -mfpmath=sse $(ARCH)
LDFLAGS := -lasound

CXXFLAGS := ${CFLAGS}

FILES := $(wildcard *.c)
TARGETS := $(patsubst %.c, %, ${FILES})
FILES := $(wildcard *.cpp)
TARGETS += $(patsubst %.cpp, %, ${FILES})

.PHONY: all clean

all: ${TARGETS}

clean:
	${RM} ${TARGETS}
