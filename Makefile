# ~/MyWork/JdR2, 3 Dec 24 .. 5 Dec 24

SHELL = /bin/sh

GCC = gcc -std=c99 -pedantic -Wall -O3

covers: covers.c exact.c util.c
	$(GCC) -o covers covers.c exact.c util.c

tiles: tiles.c
	$(GCC) -o tiles tiles.c

clean:
	rm -f *~ *~.* 



