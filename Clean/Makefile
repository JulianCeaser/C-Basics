# -*- MAKEFILE -*-
#  target: dependencies
#  	action

all: getfloat.o genFloat.o heapsort.o main

getfloat.o: getfloat.c
	gcc -c getfloat.c

genFloat.o: genFloat.c
	gcc -c genFloat.c

heapsort.o: heapsort.c
	gcc -o getfloat.o -c heapsort.c 

main: getfloat.h getfloat.o genFloat.h genFloat.o heapsort.h heapsort.o main.c
	gcc -o main getfloat.o genFloat.o heapsort.o main.c -D DEBUG_ENABLED -l m


run :
	extSort

clean:
	-rm -f *.0
	-rm -f main
	-rm -f genFloat
	-rm -f heapsort
	-rm -f output-array.txt
	-rm -f *.dat
	-rm -f input.txt
	-rm -f merged_output.txt 
