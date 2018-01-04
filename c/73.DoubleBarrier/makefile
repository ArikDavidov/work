# Global definitions
CC=gcc
CFLAGS=-g -ansi -std=gnu99 -pedantic -Wall -Wconversion
#Extra flags to give to compilers when they are supposed to invoke the linker,
#‘ld’, such as -L. Libraries (-lfoo) should be added to the LDLIBS variable instead.
LDFLAGS=-g -pthread
OUTPUT_OPTION=-MMD -MP -o $@
ARFLAGS=cvr
#SHARED_LIBRARY_EXTENCION=dylib
#SARED_LIBRARY_FLAG=-dynamiclib
# all contents of current directory
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
DEPS=$(SRCS:.c=.d)
# Directory structure
INC_DIR=../inc
CPPFLAGS= -I$(INC_DIR)
LIB_DIR=../lib
LIB_NAME=#libMessageQueue.a
#LDLIBS=-lm
# Target and sources
TARGETS=TestDoubleBarrier
LIB_SRCS=
LIB_OBJS=$(LIB_SRCS:.c=.o)
LIB_FILE=$(LIB_DIR)/$(LIB_NAME)


all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	$(RM) *.d

-include $(DEPS)


commit: $(LIB_FILE)

$(LIB_FILE): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?

clean:
	$(RM) *.o *.d $(TARGETS)

run:
	



