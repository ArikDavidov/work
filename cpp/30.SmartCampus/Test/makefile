#sudo apt-get install libmysqlclient-dev
CC=g++
CXXFLAGS=-g -ansi -pedantic -Wextra -std=c++03 -Wconversion -pthread `mysql_config --cxxflags`
#-Wall
LDFLAGS=-g -L$(LIB_DIR) -pthread
OUTPUT_OPTION=-MMD -MP -o $@
# all contents of current directory
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d)
# Directory structure
INC_DIR=../inc /usr/include/cppconn
CFLAGS+= -I$(INC_DIR)
LIB_DIR=/usr/lib
LIB_NAME=#libMessageQueue.a
LDLIBS=-lmysqlcppconn
TARGETS=testSimpleQuery #Client Server testMonitor
#testSimpleQuery
#sqltest

all: $(TARGETS) cleanup run

testMySQL: $(OBJS) $(LIB_OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@ `mysql_config --libs`
	
-include $(DEPS)
    
#testMonitor:
#	$(MAKE) -C testMonitor

cleanup:
	$(RM) *.d

clean:
	$(RM) *.o *~ *.d $(TARGETS)

run:
	./testMySQL





