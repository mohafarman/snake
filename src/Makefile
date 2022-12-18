PROGRAM=snake
CC=gcc
CFLAGS=-Wall -ggdb -Wextra -pedantic -std=c11
LDLIBS=-lmenu -lncurses -lform 
COMPILE=$(CC) $(CFLAGS) $(LDLIBS)

PROGRAM: $(PROGRAM).c
	$(COMPILE) snake.c -o ../build/./a.out
	@../build/./a.out
