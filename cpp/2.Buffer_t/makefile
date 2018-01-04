# Global definitions
CC=g++
CXXFLAGS=-g -ansi -pedantic -Wall -Wconversion -m32
LDFLAGS=-g -m32
OUTPUT_OPTION=-MMD -MP -o $@
ARFLAGS=cvr
# all contents of current directory
SRCS=String_t.cpp Buffer_t.cpp testString_t.cpp #$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d)
# Directory structure
INC_DIR=../inc
CXXFLAGS+=-I$(INC_DIR)
LIB_DIR=../lib
LIB_NAME=
LDLIBS=
# Target and sources
TARGET=testString_t
LIB_SRCS=
LIB_OBJS=$(LIB_SRCS:.c=.o)


all: $(TARGET) run

TARGET: $(OBJS) $(LIB_OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	$(RM) *.d


	
-include $(DEPS)


commit: $(LIB_FILE)

$(LIB_FILE): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?

clean:
	$(RM) *.o *~ *.d $(TARGET)

run:
	./$(TARGET)










