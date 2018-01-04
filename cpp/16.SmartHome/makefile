SUBDIRS=SO_Src cpp

.PHONY: all $(SUBDIRS)
all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@
	
clean:
	$(RM) *.o *~ *.d $(TARGET)
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f makefile $@; \
	done
	

