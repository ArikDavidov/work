#comment

#CFLAGS= -g -pedantic -ansi -std=c++03 -Wall
#CFLAGS= -g -ansi -fpermissive -std=c++03 -Wall
CFLAGS= -g -pedantic -ansi -std=c++03 -Wall -pthread
COMPILE= gcc

All: out

out: *.cpp
	$(COMPILE) $(CFLAGS) *.cpp

clean:
	rm *.out
