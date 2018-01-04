#sudo apt-get install libmysqlclient-dev
CC=g++
CXXFLAGS=-g -ansi -pedantic -Wall -Wextra -std=c++03 -Wconversion -pthread `mysql_config --cxxflags`
#-Wall
LDFLAGS=-g -L$(LIB_DIR) -pthread
OUTPUT_OPTION=-MMD -MP -o $@
# all contents of current directory
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d)
# Directory structure
COMMON_DIR=../Common
INC_DIR=/usr/include/cppconn
CXXFLAGS+= -I$(COMMON_DIR) -I$(INC_DIR)
LIB_DIR=/usr/lib
LIB_NAME=#libMessageQueue.a
LDLIBS=-lmysqlcppconn
TARGETS=test


all: $(TARGETS) cleanup

$(TARGETS): $(OBJS) $(LIB_OBJS) ../Common/DataBase.o ../Common/Queries.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@ `mysql_config --libs`
	
-include $(DEPS)

../Common/DataBase.o:
	$(MAKE) -C ../Common

../Common/Queries.o:
	$(MAKE) -C ../Common

cleanup:
	$(RM) *.d

clean:
	$(RM) *.o *~ *.d $(TARGETS)

run:
	./testConfig 1234





