# Global definitions
CC=g++
CXXFLAGS=-g -ansi -pedantic -Wall -Wconversion -m32
LDFLAGS=-g -m32
OUTPUT_OPTION=-MMD -MP -o $@
ARFLAGS=cvr
# all contents of current directory
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d)
# Directory structure
INC_DIR=../inc
CXXFLAGS+=-I$(INC_DIR)
LIB_DIR=../lib
LIB_NAME=
LDLIBS=
# Target and sources
TARGETS=testString_t InteractiveTestString_t
LIB_SRCS=
LIB_OBJS=$(LIB_SRCS:.c=.o)


all: $(TARGETS) run

testString_t: testString_t.o String_t.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	$(RM) *.d

InteractiveTestString_t: InteractiveTestString_t.o  String_t.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	$(RM) *.d

	
-include $(DEPS)


commit: $(LIB_FILE)

$(LIB_FILE): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?

clean:
	$(RM) *.o *~ *.d $(TARGETS)

run:
	./testString_t










