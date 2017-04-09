CC := g++
CXXFLAGS := -g -I/usr/local/include/igraph
CFLAGS := ${CXXFLAGS}
LDFLAGS := -ligraph

.PHONY: all clean

TARGET := $(patsubst %.cpp,%,$(wildcard *.cpp))
TARGET += $(patsubst %.c,%,$(wildcard *.c))

all: ${TARGET}

clean:
	${RM} ${TARGET}
