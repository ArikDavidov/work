# Global definitions
CC=gcc
CFLAGS=-g -ansi -std=gnu99 -pedantic -Wall -Wconversion -m32 -pthread
#Extra flags to give to compilers when they are supposed to invoke the linker,
#‘ld’, such as -L. Libraries (-lfoo) should be added to the LDLIBS variable instead.
LDFLAGS=-g -L$(LIB_DIR) -m32 -pthread
OUTPUT_OPTION=-MMD -MP -o $@
ARFLAGS=cvr
#SHARED_LIBRARY_EXTENCION=dylib
#SARED_LIBRARY_FLAG=-dynamiclib
# all contents of current directory
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
DEPS=$(SRCS:.c=.d)
# Directory structure
INC_DIR=../../inc
INC_PROJ=../inc
CPPFLAGS=-I$(INC_DIR) -I$(INC_PROJ)
LIB_DIR=../../lib
LIB_NAME=#libMessageQueue.a
LDLIBS=-lMessageQueue
# Target and sources
TARGETS=UI
LIB_SRCS=../Processor/MsgTransport.c
LIB_OBJS=$(LIB_SRCS:.c=.o)


all: $(TARGETS)

$(TARGETS): $(OBJS) $(LIB_OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	$(RM) *.d
		
-include $(DEPS)


commit: $(LIB_FILE)

$(LIB_FILE): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?

clean:
	$(RM) *.o *~ *.d $(TARGETS)

run:
	






