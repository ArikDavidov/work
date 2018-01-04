CC=g++
CXXFLAGS=-g -ansi -pedantic -Wextra -std=c++03 -Wconversion -pthread
#-Wall
LDFLAGS=-g -pthread
OUTPUT_OPTION=-MMD -MP -o $@
# all contents of current directory
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d)
TARGETS=Client Server #testMonitor
# Directory structure
INC_DIR=../inc
CFLAGS+= -I$(INC_DIR)

	
all: $(TARGETS) cleanup

Server: $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	#$(RM) *.d
	
-include $(DEPS)

Client:
	$(MAKE) -C testClient
    
#testMonitor:
#	$(MAKE) -C testMonitor

cleanup:
	$(RM) *.d

clean:
	$(RM) *.o *~ *.d $(TARGETS)

run:
	./Script.sh





