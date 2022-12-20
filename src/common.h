#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>
#include <menu.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

int stdscr_maxy, stdscr_maxx;


char *main_menu_choices[] = {
	"Start Game",
	"About",
	"Quit",
};

int stdscr_maxy, stdscr_maxx;

void
prnt(const char *string) {
	printf("from common: %s\n", string);
}

#endif 
