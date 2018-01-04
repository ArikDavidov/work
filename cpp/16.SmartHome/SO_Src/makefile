# Global definitions
CC=g++
CXXFLAGS=-g -fPIC -ansi -pedantic -Wall -Wconversion
SFLAGS = -g -shared -Wl,-soname,
OUTPUT_OPTION=-MMD -MP -o $@
# all contents of current directory
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d)
# Directory structure
INC_DIR=../inc
CXXFLAGS+=-I$(INC_DIR)
LIB_DIR=../SO
LIB_NAME=DigitalCat.so
# Target and sources
TARGET=DigitalCat.o
LIB_SRCS=DigitalCat.cpp
LIB_OBJS=$(LIB_SRCS:.cpp=.o)


all: $(TARGET) commit

$(TARGET): $(SRCS)
	$(CC) $(CXXFLAGS) -c $^ -o $@
#	$(RM) *.d

-include $(DEPS)


commit: $(LIB_NAME).1.0

$(LIB_NAME).1.0: $(LIB_OBJS)
	$(CC) $(SFLAGS)$(LIB_NAME).1 -o $(LIB_NAME).1.0 $(LIB_OBJS)
	cp $(LIB_NAME).1.0 $(LIB_DIR)/

clean:
	$(RM) *.o *~ *.d $(TARGET) $(LIB_NAME).1.0 $(LIB_DIR)/$(LIB_NAME).1.0 


#g++ -g -fPIC -ansi -pedantic -Wall -Wconversion -I../inc -c DigitalCat.cpp -o DigitalCat.o
#g++ -shared DigitalCat.o -o DigitalCat.so
#g++ test.cpp -ldl -o test





