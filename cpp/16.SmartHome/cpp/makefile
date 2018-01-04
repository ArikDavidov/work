# Global definitions
CC=g++
CXXFLAGS=-g -ansi -pedantic -Wall -Wconversion -pthread
LDFLAGS=-g -pthread -rdynamic
OUTPUT_OPTION=-MMD -MP -o $@
# all contents of current directory
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d)
# Directory structure
TARGET=../testSmartHomeObj
INC_DIR=../inc
CXXFLAGS+=-I$(INC_DIR)
LDLIBS=-ldl

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	$(RM) *.d

-include $(DEPS)
	
clean:
	$(RM) *.o *~ *.d $(TARGET)


