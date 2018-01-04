# Global definitions
CC=gcc
CFLAGS=-g -ansi -std=gnu99 -pedantic -Wall -Wconversion
LDFLAGS=-g
# Directory structure
INC_DIR=../inc
CFLAGS += -I$(INC_DIR)
LIB_DIR=../lib
LIB_NAME=
# all contents of current directory
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
# Target and sources
TARGETS=SignalsA SignalsB
LIB_SRCS=
LIB_OBJS=$(LIB_SRCS:.c=.o)

LIB_FILE=$(LIB_DIR)/$(LIB_NAME)

# Dependencies
all: SignalsA SignalsB run

SignalsA: SignalsA.c

SignalsB: SignalsB.c


depends:
	$(CC) -MM -I$(INC_DIR) $(SRCS) > depends

commit: $(LIB_FILE)

$(LIB_FILE): $(LIB_OBJS)
	$(AR) cvr $@ $?

clean:
	$(RM) *.o $(TARGETS) depends

run:
	./SignalsA 300 9 9
	./SignalsB 300 9 9



