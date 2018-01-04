# Global definitions
CC=g++
CXXFLAGS=-g -ansi -pedantic -Wextra -std=c++03 -Wconversion -pthread
LDFLAGS=-g -pthread
OUTPUT_OPTION=-MMD -MP -o $@
ARFLAGS=cvr
# all contents of current directory
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d)
# Directory structure
INC_DIR=../../inc
CXXFLAGS+=-I$(INC_DIR)
LIB_DIR=../lib
LIB_NAME=
LDLIBS=
# Target and sources
TARGET=test
LIB_SRCS=
LIB_OBJS=$(LIB_SRCS:.c=.o)


all: $(TARGET) run

$(TARGET): $(OBJS)
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









