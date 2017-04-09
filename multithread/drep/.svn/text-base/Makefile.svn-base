
BIN=drep

CFLAGS = -I./utilities/ -I./disassemble/ -I./profiling/ -pthread -static -g3 -g
LIBS = -pthread /usr/local/lib/libpfm.a -lm
LINKOPT = -Xlinker -T ld.script
EXTRA_FLAGS = 
EXTRA_FLAGS += -D_DUMP_INSTR 
#EXTRA_FLAGS += -D_HELPER_THREAD
#EXTRA_FLAGS += -D_USE_MMX_REG
#EXTRA_FLAGS += -D_USE_XMM_HIGH
EXTRA_FLAGS += -D_DEBUG 
EXTRA_FLAGS += -D_PROMOTE_NON_STACK
#EXTRA_FLAGS += -D_MORE_REM
#EXTRA_FLAGS += -D_STATISTIC
#EXTRA_FLAGS += -D_ANOTHER_SELECT
EXTRA_FLAGS += -D_NO_STACK_SWITCH
#EXTRA_FLAGS += -D_NO_REGISTER_PROMOTION
#EXTRA_FLAGS += -D_NO_OPT_SIB
#EXTRA_FLAGS += -D_NO_OPTIMIZE
#EXTRA_FLAGS += -D_NO_MPROTECT

CC = gcc $(CFLAGS) $(EXTRA_FLAGS) 

MAIN_OBJECTS= 	main/bt_main.o 

DEC_OBJECTS =		disassemble/mnemonics.o \
			disassemble/opcmap.o \
			disassemble/decode.o \
			disassemble/disassemble.o \
			disassemble/dump.o 

CODEGEN_OBJECTS =	code_generator/assemble.o \
			code_generator/code_generation.o

UTILITY_OBJECTS = 	utilities/utility.o \
			utilities/mem_manage.o \
			utilities/ir.o \
			utilities/flow_analysis.o \
			utilities/optimization.o \
			utilities/exception.o 

PROFILING_OBJECTS =	profiling/perf_util.o \
			profiling/perf_sample.o \
			profiling/resolve_pfmon.o

DEC_HEADERS =		disassemble/dec_types.h \
			disassemble/input.h \
			disassemble/mnemonics.h \
			disassemble/opcmap.h

CODEGEN_HEADERS =	code_generator/assemble.h

UTILITY_HEADERS =	utilities/utility.h \
			utilities/common_types.h \
			utilities/ir.h \
			utilities/optimization.h \
			utilities/mem_manage.h \
			profiling/perf_util.h \
			profiling/perf_sample.h 


all:	$(MAIN_OBJECTS) $(UTILITY_OBJECTS) $(DEC_OBJECTS) $(PROFILING_OBJECTS) $(CODEGEN_OBJECTS)
	$(CC) -o $(BIN) $(MAIN_OBJECTS) $(UTILITY_OBJECTS) $(DEC_OBJECTS) $(PROFILING_OBJECTS) $(CODEGEN_OBJECTS) $(LIBS)

main/bt_main.o: main/bt_main.c $(DEC_HEADERS) $(UTILITY_HEADERS) 
	$(CC) -c main/bt_main.c
	mv bt_main.o main/

utilities/utility.o:utilities/utility.c  $(UTILITY_HEADERS)
	$(CC) -c utilities/utility.c
	mv utility.o utilities/

utilities/mem_manage.o:utilities/mem_manage.c $(DEC_HEADERS) $(UTILITY_HEADERS)
	$(CC) -c utilities/mem_manage.c -D_GNU_SOURCE
	mv mem_manage.o utilities/

utilities/ir.o:utilities/ir.c $(DEC_HEADERS) $(UTILITY_HEADERS) 
	$(CC) -c utilities/ir.c
	mv ir.o utilities/

utilities/flow_analysis.o:utilities/flow_analysis.c $(DEC_HEADERS) $(UTILITY_HEADERS) 
	$(CC) -c utilities/flow_analysis.c
	mv flow_analysis.o utilities/

utilities/optimization.o:utilities/optimization.c $(DEC_HEADERS) $(UTILITY_HEADERS)  
	$(CC) -c utilities/optimization.c
	mv optimization.o utilities/

utilities/exception.o:utilities/exception.c $(DEC_HEADERS) $(UTILITY_HEADERS) $(CODEGEN_HEADERS)
	$(CC) -I./code_generator/ -c utilities/exception.c
	mv exception.o utilities/

disassemble/mnemonics.o:disassemble/mnemonics.c $(DEC_HEADERS)
	$(CC) -c disassemble/mnemonics.c
	mv mnemonics.o disassemble/

disassemble/opcmap.o:disassemble/opcmap.c $(DEC_HEADERS) $(UTILITY_HEADERS)
	$(CC) -c disassemble/opcmap.c
	mv opcmap.o disassemble/

disassemble/decode.o:disassemble/decode.c $(DEC_HEADERS) $(UTILITY_HEADERS)
	$(CC) -c disassemble/decode.c
	mv decode.o disassemble/

disassemble/disassemble.o:disassemble/disassemble.c $(DEC_HEADERS) $(UTILITY_HEADERS)
	$(CC) -c disassemble/disassemble.c
	mv disassemble.o disassemble/

disassemble/dump.o:disassemble/dump.c $(DEC_HEADERS) $(UTILITY_HEADERS)
	$(CC) -c disassemble/dump.c
	mv dump.o disassemble/

profiling/perf_util.o:profiling/perf_util.c $(UTILITY_HEADERS)
	$(CC) -c profiling/perf_util.c
	mv perf_util.o profiling/

profiling/perf_sample.o:profiling/perf_sample.c $(UTILITY_HEADERS)
	$(CC) -I/usr/local/include -D_GNU_SOURCE -c profiling/perf_sample.c
	mv perf_sample.o profiling/
 
profiling/resolve_pfmon.o:profiling/resolve_pfmon.c $(DEC_HEADERS) $(UTILITY_HEADERS) 
	$(CC) -c profiling/resolve_pfmon.c
	mv resolve_pfmon.o profiling/

code_generator/assemble.o:code_generator/assemble.c  $(UTILITY_HEADERS) $(DEC_HEADERS) $(CODEGEN_HEADERS)
	$(CC) -c code_generator/assemble.c
	mv assemble.o code_generator/

code_generator/code_generation.o:code_generator/code_generation.c  $(UTILITY_HEADERS) $(DEC_HEADERS) $(CODEGEN_HEADERS)
	$(CC) -c code_generator/code_generation.c
	mv code_generation.o code_generator/
		
clean:
	rm -f $(MAIN_OBJECTS) $(UTILITY_OBJECTS) $(DEC_OBJECTS) $(PROFILING_OBJECTS) $(CODEGEN_OBJECTS) drep

