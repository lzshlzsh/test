
srcs := $(wildcard *.scala)
objs := $(patsubst %.scala, %.class, $(srcs))
class_path = classes

__mkdir := $(shell for i in $(class_path); do \
	[ -e $$i ] || mkdir -p $$i; \
	done)

SCALAC := fsc
#SCALAC := scalac
SCALAFLAGS := -d $(class_path) -classpath $(class_path)
RM := rm -rf

.PHONY: all clean

all: $(objs)

$(objs): %.class: %.scala
	$(SCALAC) $(SCALAFLAGS) $<

Summer.class: ChecksumAccumulator.class

clean:
	$(RM) $(class_path)

vpath %.class $(class_path)
