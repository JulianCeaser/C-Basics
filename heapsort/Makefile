# -*- MakeFile -*-

#target: dependencies
#	action

main: main.o heapsort.o 
	gcc main.o heapsort.o -o main

main.o: main.c functions.h
	gcc -c main.c

heapsort.o: heapsort.c
	gcc -c heapsort.c

clean:
	-rm -f *.o
	-rm -f main
