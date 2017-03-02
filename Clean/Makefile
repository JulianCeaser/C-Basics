# -*- MAKEFILE -*-
#  target: dependencies
#  	action

all: main genFloat

main: main.o
	gcc main.o -o main -l m

main.o: main.c getfloat.h mean.h
	gcc -c main.c

genFloat: genFloat.o
	gcc genFloat.o -o genFloat

genFloat.o: genFloat
	gcc -c genFloat.c

clean:
	-rm -f *.0
	-rm -f main
	-rm -f genFloat
	-rm -f output-array.txt
	-rm -f *.dat
	-rm -f input.txt
