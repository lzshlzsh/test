CC := gcc
CXX := g++
CFLAGS := -g -Wall -msse3 -mfpmath=sse -std=gnu++11 #-std=c++0x #`pkg-config --cflags --libs gtk+-2.0`
LDFLAGS := #-lm -ldl -lpthread #-static

CXXFLAGS := ${CFLAGS}

FILES := $(wildcard *.c)
TARGETS := $(patsubst %.c, %, ${FILES})
FILES := $(wildcard *.cpp)
TARGETS += $(patsubst %.cpp, %, ${FILES})

.PHONY: all clean

all: ${TARGETS}

clean:
	${RM} ${TARGETS}
