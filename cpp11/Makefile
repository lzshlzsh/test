.PHONY: all clean

TARGET := $(patsubst %.cpp,%,$(wildcard *.cpp))

CXXFLAGS := -std=c++11

all: ${TARGET}

clean:
	${RM} ${TARGET}
