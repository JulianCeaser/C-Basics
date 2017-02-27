# -*- MakeFile -*-

#target: dependencies
#	action

main: main.o heapsort.o downheap.o max.o
	gcc main.o heapsort.o downheap.o max.o -o main

main.o: main.c functions.h
	gcc -c main.c

heapsort.o: heapsort.c
	gcc -c heapsort.c

downheap.o: downheap.c
	gcc -c downheap.c

max.o: max.c
	gcc -c max.c

clean:
	-rm -f *.o
