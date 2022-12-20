PROGRAM=snake
CC=gcc
CFLAGS=-Wall -ggdb -Wextra -pedantic -std=c11
LDLIBS=-lmenu -lncurses -lform 
COMPILE=$(CC) $(CFLAGS) $(LDLIBS)

PROGRAM: $(PROGRAM).c
	@mkdir ../build
	$(COMPILE) $(PROGRAM).c -o ../build/./$(PROGRAM)
	@../build/./$(PROGRAM)
