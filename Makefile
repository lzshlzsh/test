TOPDIR := $(abspath $(dir $(lastword ${MAKEFILE_LIST})))

CXXFLAGS := -Wall -g #-O2 #-std=c++11 #-Werror -msse3 -mfpmath=sse -g #-m32 #`pkg-config --cflags --libs gtk+-2.0`
LDFLAGS := #-lm -lpthread -lrt -ldl #-static

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
test_coroutine1: CXXFLAGS += -I${HOME}/tencent/R2_proj/trunk/third_party_lib/libco
test_coroutine1: LDFLAGS += -L${HOME}/tencent/R2_proj/trunk/third_party_lib/libco/lib -lcolib -pthread
my-coroutine: CXXFLAGS += -I${HOME}/tencent/R2_proj/trunk/third_party_lib/libco
my-coroutine: LDFLAGS += -L${HOME}/tencent/R2_proj/trunk/third_party_lib/libco/lib -lcolib -pthread
shared_ptr: LDFLAGS += -lboost_system --std=c++0x
shared_ptr2: LDFLAGS += -lboost_system --std=c++0x
shared_ptr3: LDFLAGS += -lboost_system -lboost_thread --std=c++0x
test_unordered_map: CXXFLAGS += -std=c++0x
nullptr: CXXFLAGS += -std=c++0x
unordered_map_erase: CXXFLAGS += -std=c++0x
constexpr: CXXFLAGS += -std=c++11
override_final: CXXFLAGS += -std=c++11
unordered_map_inc: CXXFLAGS += -std=c++0x
weakref: CXXFLAGS += -I./weakref_o #--verbose
weakref: LDFLAGS += -L./weakref_o -Wl,-dn -lweakref_o -Wl,-dy