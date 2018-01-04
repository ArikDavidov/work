#sudo apt-get install libmysqlclient-dev
CC=g++
CXXFLAGS=-g -ansi -pedantic -Wall -Wextra -std=c++03 -Wconversion -pthread `mysql_config --cxxflags`
LDFLAGS=-g -L$(LIB_DIR) -pthread
OUTPUT_OPTION=-MMD -MP -o $@
# all contents of current directory
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d)
# Directory structure
INC_DIR=/usr/include/cppconn
CFLAGS+= -I$(INC_DIR)
LIB_DIR=/usr/lib
LIB_NAME=#libMessageQueue.a
LDLIBS=-lmysqlcppconn
TARGETS=Registrar


all: $(TARGETS) cleanup

$(TARGETS): $(OBJS) $(LIB_OBJS)
	
-include $(DEPS)

cleanup:
	$(RM) *.d

clean:
	$(RM) *.o *~ *.d $(TARGETS)





