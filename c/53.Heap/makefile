FLAGS = -g -ansi -pedantic -Wall -Wconversion -I$(INC_PATH)
INC_PATH = ../inc
LIB_PATH = ../lib
VECTOR_PATH = ../48.GenericVector

testHeap.out: Vector testHeap.c $(LIB_PATH)/libHeap.a
	gcc $(FLAGS) -o testHeap.out testHeap.c $(LIB_PATH)/libHeap.a $(LIB_PATH)/libVector.a

Vector: 
	make -C $(VECTOR_PATH)
	
$(LIB_PATH)/libHeap.a: Heap.o
	ar -cvq libHeap.a Heap.o
	mv libHeap.a $(LIB_PATH)

Heap.o: Heap.c $(INC_PATH)/Heap.h
	gcc $(FLAGS) -c Heap.c

clean:
	make -C $(VECTOR_PATH) clean
	rm   testHeap.out $(LIB_PATH)/libHeap.a Heap.o
	
	
	
