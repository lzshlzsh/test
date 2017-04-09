CC := gcc
CXX := g++
CFLAGS := -Wall -Werror -msse3 -mfpmath=sse -g #`pkg-config --cflags --libs gtk+-2.0`
LDFLAGS := #-lm -ldl #-lpthread -static

CXXFLAGS := ${CFLAGS}

FILES := $(wildcard *.c)
TARGETS := $(patsubst %.c, %, ${FILES})
FILES := $(wildcard *.cpp)
TARGETS += $(patsubst %.cpp, %, ${FILES})

.PHONY: all clean

all: ${TARGETS}

clean:
	${RM} ${TARGETS}
