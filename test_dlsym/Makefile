
src := $(wildcard *.cpp *.c)
obj := $(patsubst %.c,%.o,$(filter-out %.cpp, ${src}))
obj += $(patsubst %.cpp,%.o,$(filter-out %.c, ${src}))

CXXFLAGS := -fPIC -shared

target := libtest_dlsym.a libtest_dlsym.so

.PHONY: all clean

all: ${target}

$(filter %.a,${target}): %.a: ${obj}
	${AR} ${ARFLAGS} $@ $^

$(filter %.so,${target}): %.so: ${obj}
	${CXX} ${CXXFLAGS} -o $@ $^

clean:
	${RM} ${target} ${obj}
