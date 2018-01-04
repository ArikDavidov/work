SUBDIRS=Registrar SmartHome Common Test


.PHONY: all $(SUBDIRS)
all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

	
clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f makefile $@; \
	done
	

