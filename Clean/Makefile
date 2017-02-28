# -*- MAKEFILE -*-
#  target: dependencies
#  	action

main: main.o
	gcc main.o -o main -l m

main.o: main.c getfloat.h mean.h
	gcc -c main.c

clean:
	-rm -f *.0
	-rm -f main
	-rm -f output-array.txt
