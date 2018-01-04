# Global definitions
CC=gcc
CFLAGS=-g -ansi -pedantic -Wall -Wconversion
LDFLAGS=-g
# Directory structure
INC_DIR=../inc
CFLAGS += -I$(INC_DIR)
LIB_DIR=../lib
LIB_NAME=libVector.a
# all contents of current directory
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
# Target and sources
TARGET=testGV
LIB_SRCS=Vector.c
LIB_OBJS=$(LIB_SRCS:.c=.o)

LIB_FILE=$(LIB_DIR)/$(LIB_NAME)

# Dependencies
all: $(TARGET) run commit

$(TARGET): $(OBJS)

include depends

depends:
	$(CC) -MM -I$(INC_DIR) $(SRCS) > depends


commit: $(LIB_FILE)

$(LIB_FILE): $(LIB_OBJS)
	$(AR) cvr $@ $?


clean:
	rm -f *.o $(TARGET) depends

run:
	./$(TARGET)




