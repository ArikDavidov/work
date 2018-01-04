# Global definitions
CC=gcc
CFLAGS=-g -ansi -std=gnu99 -pedantic -Wall -Wconversion -m32 -pthread
#Extra flags to give to compilers when they are supposed to invoke the linker,
#‘ld’, such as -L. Libraries (-lfoo) should be added to the LDLIBS variable instead.
LDFLAGS=-g -L../lib -m32 -pthread
OUTPUT_OPTION=-MMD -MP -o $@
ARFLAGS=cvr
#SHARED_LIBRARY_EXTENCION=dylib
#SARED_LIBRARY_FLAG=-dynamiclib
# all contents of current directory
SRCS=Processor.c Operators.c OperatorTotals.c Subscribers.c SubscriberTotals.c MsgTransport.c #$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
DEPS=$(SRCS:.c=.d)
# Directory structure
INC_DIR=../inc
CPPFLAGS= -I$(INC_DIR)
LIB_DIR=../lib
LIB_NAME=#libMessageQueue.a
LDLIBS=-lHashMap -lMessageQueue -lList -lm
# Target and sources
TARGETS=Processor
LIB_SRCS=
LIB_OBJS=$(LIB_SRCS:.c=.o)
LIB_FILE=$(LIB_DIR)/$(LIB_NAME)


all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@ 
	$(RM) *.d

-include $(DEPS)

commit: $(LIB_FILE)

$(LIB_FILE): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?

clean:
	$(RM) *.o *.d $(TARGETS)

run:
	

CdrGenerator: CdrGenerator.c
	$(CC) -g -L../lib -ansi -std=gnu99 -pedantic -Wall -Wconversion -pthread -I../inc -o CdrGenerator CdrGenerator.c

Feeder: Feeder.c MsgTransport.c Parser.c -lMessageQueue
	$(CC) -g -L../lib -ansi -std=gnu99 -pedantic -Wall -Wconversion -pthread -I../inc -o Feeder Feeder.c MsgTransport.c Parser.c -lMessageQueue

Discoverer: Discoverer.c
	$(CC) -g -L../lib -ansi -std=gnu99 -pedantic -Wall -Wconversion -pthread -I../inc -o Discoverer Discoverer.c



