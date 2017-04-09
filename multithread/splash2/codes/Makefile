
SUBDIR := apps kernels

.PHONY: all clean

all:
	@for i in $(SUBDIR); do \
		$(MAKE) -C $$i; \
		done

clean:
	@for i in $(SUBDIR); do \
		$(MAKE) -C $$i clean; \
		done
