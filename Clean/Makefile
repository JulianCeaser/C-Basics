# -*- MAKEFILE -*-
#  target: dependencies
#  	action

all: main genFloat heapsort

main: main.o
	gcc main.o -o main -l m

main.o: main.c getfloat.h mean.h
	gcc -c main.c

genFloat: genFloat.o
	gcc genFloat.o -o genFloat

genFloat.o: genFloat
	gcc -c genFloat.c

heapsort: heapsort.o
	gcc heapsort.o -o heapsort -l m

heapsort.o: heapsort.c getfloat.h
	gcc -c heapsort.c

clean:
	-rm -f *.0
	-rm -f main
	-rm -f genFloat
	-rm -f heapsort
	-rm -f output-array.txt
	-rm -f *.dat
	-rm -f input.txt
