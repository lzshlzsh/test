CXX := g++
CXXFLAGS := -Wall -g -O2 #-std=c++11 #-Werror -msse3 -mfpmath=sse -g #-m32 #`pkg-config --cflags --libs gtk+-2.0`
LDFLAGS := #-lm -lpthread -lrt -ldl #-static

FILE := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,${FILE})

TARGET := point

.PHONY: all clean

all: ${TARGET}

${TARGET}: %: ${OBJ}
	${CXX} ${CXXFLAGS} -o $@ $^ ${LDFLAGS}

clean:
	${RM} ${TARGET} ${OBJ}

${OBJ}: %.o: %.cpp
	$(CXX) -c ${CXXFLAGS} -o $@ $^
