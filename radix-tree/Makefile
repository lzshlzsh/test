CC := gcc
CFLAGS := -g -Wall -Werror

target := main
objs := $(patsubst %.c, %.o, $(wildcard *.c))

.PHONY: all clean

all: $(target)

$(target): $(objs)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(target) $(objs)
