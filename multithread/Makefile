CC := gcc
CXX := g++
CFLAGS := -g -Wall -msse3 -mfpmath=sse -m32 #`pkg-config --cflags --libs gtk+-2.0`
LDFLAGS := -lm -ldl -lpthread -static

CXXFLAGS := ${CFLAGS}

FILES := $(wildcard *.c)
TARGETS := $(patsubst %.c, %, ${FILES})
FILES := $(wildcard *.cpp)
TARGETS += $(patsubst %.cpp, %, ${FILES})

.PHONY: all clean

all: ${TARGETS}

clean:
	${RM} ${TARGETS}


%: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
