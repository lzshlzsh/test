CC := gcc
CXX := g++
CFLAGS := -m32 -g3 -Wall -mfpmath=sse -march=pentium4 -static
#LDFLAGS := -static
CXXFLAGS := ${CFLAGS}

EXE := dependce

FILES := y_def.cpp x_def.cpp main.cpp
OBJS += $(patsubst %.cpp, %.o, ${FILES})

.PHONY: clean

${EXE}: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS}

clean:
	${RM} ${EXE} ${OBJS}
