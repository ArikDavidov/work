CC=gcc
CFLAGS=-g -ansi -std=gnu99 -pedantic -Wconversion -Wextra -L$(LIB_DIR)
#-Wall
TARGETS=Client Server
# Directory structure
INC_DIR=../inc
CFLAGS+= -I$(INC_DIR)
LIB_DIR=../lib
LDLIBS=-lList

all: $(TARGETS) run
	
#$(TARGETS):
#	$(CC) $(CFLAGS) $(subst $@, $@.c,$@) -o $@

Client:
	$(MAKE) -C SarigClient
	#$(CC) $(CFLAGS) Client.c $(LDLIBS) -o $@

Server:
	$(CC) $(CFLAGS) testServer.c Server.c $(LDLIBS) -o $@

clean:
	$(RM) *.o *~ *.d $(TARGETS)

run:
	./Script.sh





