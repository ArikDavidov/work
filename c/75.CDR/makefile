SUBDIRS=Processor Discoverer Feeder UI CDRGenerators

.PHONY: all $(SUBDIRS)
all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f makefile $@; \
	done

