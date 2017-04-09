
SUBDIR := $(wildcard *)
SUBDIR := $(shell \
	for i in $(SUBDIR); do \
		if [ -d $$i ]; then \
			echo $$i; \
		fi \
	done \
		)

.PHONY: all clean

all:
	@for i in $(SUBDIR); \
		do $(MAKE) -C $$i; \
		done
clean:
	@for i in $(SUBDIR); \
		do $(MAKE) -C $$i clean; \
		done
