SUB_DIRS := $(dir $(shell find . -mindepth 2 -maxdepth 2 -name "?akefile"))
PHONYS := all clean 

.PHONY: ${PHONYS}

${PHONYS}:
	@for i in ${SUB_DIRS}; do \
		${MAKE} -C $$i $@ || exit -1 ; \
		done
