CC=gcc
CFLAGS=-g -ansi -std=gnu99 -pedantic -Wall -Wextra -Wconversion
TARGETS=Client6 Server6

all: $(TARGETS) run

$(TARGETS):
	$(CC) -g -ansi -pedantic $(subst $@, $@.c,$@) -o $@

clean:
	$(RM) *.o *~ *.d $(TARGETS)

run:
	./Script.sh





