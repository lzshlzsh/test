.PHONY: all clean

SRC := $(wildcard *.cpp)
TARGET := $(patsubst %.cpp,%.o,${SRC})

SRC := $(wildcard *.c)
TARGET += $(patsubst %.c,%.o,${SRC})

all: ${TARGET}
