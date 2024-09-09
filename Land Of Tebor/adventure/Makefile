# Define which compiler to use.
COMPILER = gcc

# Define which C standard to use.
CSTD = --std=c18

# Define include library path 
LIB = -Ilib

#define linking lib
THREADLIB =-lpthread

# Define the path to the file with the main function.
#MAIN = ../../CI/objects/pool/poolM.o

PREREQ= adventuretype.o array_list.o heap.o heroes.o locations.o main.o simulation.o


all:adventure

# Rule for search executable
adventure: $(PREREQ) $(MAIN)
	$(COMPILER) $(CSTD) $(LIB) $(MAIN) $(PREREQ) $(THREADLIB) -o adventure

adventuretype.o: adventuretype.c adventuretype.h
	$(COMPILER) $(CSTD) $(LIB) -c adventuretype.c

array_list.o: lib/array_list.c lib/array_list.h
	$(COMPILER) $(CSTD) $(LIB) -c lib/array_list.c -o array_list.o

     
heap.o: lib/heap.c lib/heap.h  lib/array_list.h
	$(COMPILER) $(CSTD) $(LIB) -c lib/heap.c -o heap.o

heroes.o: heroes.c heroes.h lib/array_list.h
	$(COMPILER) $(CSTD) $(LIB) -c heroes.c -o heroes.o

locations.o: locations.c locations.h lib/array_list.h
	$(COMPILER) $(CSTD) $(LIB) -c locations.c -o locations.o

main.o: main.c lib/array_list.h heroes.h locations.h simulation.h 
	$(COMPILER) $(CSTD) $(LIB) -c main.c -o main.o

simulation.o: simulation.c simulation.h lib/array_list.h lib/heap.h heroes.h locations.h
	$(COMPILER) $(CSTD) $(LIB) -c simulation.c -o simulation.o


clean:
	rm -f $(PREREQ) adventure 
