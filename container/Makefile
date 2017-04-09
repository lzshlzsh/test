CC := gcc
CXX := g++
CFLAGS := -Wall -g #-O2 #-std=c++11 #-Werror -msse3 -mfpmath=sse -g #-m32 #`pkg-config --cflags --libs gtk+-2.0`
LDFLAGS := #-lm -lpthread -lrt -ldl #-static

CXXFLAGS := ${CFLAGS}

FILES := $(wildcard *.c)
TARGETS := $(patsubst %.c, %, ${FILES})
FILES := $(wildcard *.cpp)
TARGETS += $(patsubst %.cpp, %, ${FILES})

.PHONY: all clean

all: ${TARGETS}

clean:
	${RM} ${TARGETS}


%: %.cpp
	$(CXX) ${CXXFLAGS} -o $@ $^ ${LDFLAGS}
%: %.c
	$(CC) ${CFLAGS} -o $@ $^ ${LDFLAGS}
