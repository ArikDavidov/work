CC=gcc
CFLAGS=-g -ansi -pedantic -Wconversion -Wextra
#-Wall
TARGETS=Client

all: $(TARGETS)

Client:
	$(CC) $(CFLAGS) $(subst $@, $@.cpp, $@) -o $@
	mv $(TARGETS) ../





