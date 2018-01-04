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
TARGETS=Ping.out Pong.out
LIB_SRCS=
LIB_OBJS=$(LIB_SRCS:.c=.o)

LIB_FILE=$(LIB_DIR)/$(LIB_NAME)

# Dependencies
all: Ping.out Pong.out

Ping.out: Ping.o MessageQueue.o
	$(CC) $(CFLAGS) -o $@ $^

Pong.out: Pong.o MessageQueue.o
	$(CC) $(CFLAGS) -o $@ $^
	
MessageQueue.o:

Ping.out:

Pong.out:

commit: $(LIB_FILE)

$(LIB_FILE): $(LIB_OBJS)
	$(AR) cvr $@ $?

clean:
	$(RM) *.o $(TARGETS) depends

run:
	



