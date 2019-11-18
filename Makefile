TOPDIR := $(abspath $(dir $(lastword ${MAKEFILE_LIST})))

CXX_4_8_1 := /data/gcc-build-4.8.1/bin/g++
CXX := $(shell if [ -x ${CXX_4_8_1} ]; then echo ${CXX_4_8_1}; else echo g++; fi)
LDFLAGS += -static-libstdc++

CXXFLAGS := -Wall -g -std=c++11 #-Werror -msse3 -mfpmath=sse -g #-m32 #`pkg-config --cflags --libs gtk+-2.0`
LDFLAGS := #-lm -lpthread -lrt -ldl #-static

CXXFLAGS_LIBCO := -I/data/github/libco
LDFLAGS_LIBCO := -L/data/github/libco/lib -lcolib -pthread

FILES := $(wildcard *.c)
COBJ := $(patsubst %.c,%.o,${FILES})
CTARGETS := $(patsubst %.c,%,${FILES})

FILES := $(wildcard *.cpp)
CXXOBJ := $(patsubst %.cpp,%.o,${FILES})
CXXTARGETS += $(patsubst %.cpp,%,${FILES})

TARGETS := ${CTARGETS} ${CXXTARGETS}

SUBDIRS := $(abspath $(dir $(shell find . -mindepth 2 -maxdepth 2 -name ?akefile)))
FILTER_OUT_DIR := apue.2e ioctl-test igraph ld x86-32 helper multithread
FILTER_OUT_DIR += x86-64
SUBDIRS := $(filter-out $(addprefix ${TOPDIR}/,${FILTER_OUT_DIR}), ${SUBDIRS})

.PHONY: all clean subdirs_all subdirs_clean

all: subdirs_all ${TARGETS}

subdirs_all:
	@set -e; for i in ${SUBDIRS}; do \
		${MAKE} -C $$i all; \
		done

clean: subdirs_clean
	${RM} ${TARGETS}

subdirs_clean:
	@set -e; for i in ${SUBDIRS}; do \
		${MAKE} -C $$i clean; \
		done

${CXXTARGETS}: %: %.o
	$(CXX) ${CXXFLAGS} -o $@ $^ ${LDFLAGS}

${CTARGETS}: %: %.o
	$(CC) ${CXXFLAGS} -o $@ $^ ${LDFLAGS}

${CXXOBJ}: %.o: %.cpp
	$(CXX) ${CXXFLAGS} -c -o $@ $<

${COBJ}: %.o: %.c
	$(CC) ${CXXFLAGS} -c -o $@ $<

pthread_create: LDFLAGS += -pthread
sincos: LDFLAGS += -lm
tls: LDFLAGS += -pthread
ticket_spin_lock: LDFLAGS += -lm
sin: LDFLAGS += -lm
pi: LDFLAGS += -lm
no-reentrant: LDFLAGS += -lm
boost_thread: LDFLAGS += -lboost_system -lboost_thread
dlopen: LDFLAGS += -ldl
dlsym: CXXFLAGS += -I./test_dlsym
dlsym: LDFLAGS += -ldl -L./lib -L./test_dlsym -Wl,-dn -lmylib -ltest_dlsym -Wl,-dy
test_coroutine1: CXXFLAGS += ${CXXFLAGS_LIBCO}
test_coroutine1: LDFLAGS += ${LDFLAGS_LIBCO}
my-coroutine2: CXXFLAGS += ${CXXFLAGS_LIBCO}
my-coroutine2: LDFLAGS += ${LDFLAGS_LIBCO}
my-coroutine: CXXFLAGS += -I${HOME}/tencent/R2_proj/trunk/third_party_lib/libco
my-coroutine: LDFLAGS += -L${HOME}/tencent/R2_proj/trunk/third_party_lib/libco/lib -lcolib -pthread
shared_ptr: LDFLAGS += -lboost_system --std=c++0x
shared_ptr2: LDFLAGS += -lboost_system --std=c++0x
shared_ptr3: LDFLAGS += -lboost_system -lboost_thread --std=c++0x
shared_ptr4: LDFLAGS += -lboost_system -lboost_thread --std=c++0x
test_unordered_map: CXXFLAGS += -std=c++0x
nullptr: CXXFLAGS += -std=c++0x
unordered_map_erase: CXXFLAGS += -std=c++0x
constexpr: CXXFLAGS += -std=c++11
override_final: CXXFLAGS += -std=c++11
unordered_map_inc: CXXFLAGS += -std=c++0x
weakref: CXXFLAGS += -I./weakref_o #--verbose
#weakref: LDFLAGS += -L./weakref_o -Wl,-dn -lweakref_o -Wl,-dy
weakref: LDFLAGS += ./weakref_o/foo.o
test_http_parser: CXXFLAGS += -I/data/github/http-parser
test_http_parser: LDFLAGS += -L/data/github/http-parser -Wl,-dn -lhttp_parser -Wl,-dy
test_lexical_cast: LDFLAGS += -lboost_system -lboost_thread --std=c++0x
socket: LDFLAGS += -ldl
fork4: CXXFLAGS += -I/usr/local/boost/include -Wno-unused-local-typedefs
fork4: LDFLAGS += -L/usr/local/boost/lib -Wl,-dn -lboost_system -lboost_thread -Wl,-dy -pthread
stl_pack: CXXFLAGS += -I${HOME}/tencent/common_recommend_proj/trunk/lib/grocery_cpp_api/grocery_lib_cpp_api/inc
stl_pack: LDFLAGS += -L${HOME}/tencent/common_recommend_proj/trunk/lib/grocery_cpp_api/grocery_lib_cpp_api/lib -lgrocerycppapi
std_async: LDFLAGS += -pthread
hahaha: LDFLAGS += -static
