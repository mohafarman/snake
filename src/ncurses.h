#ifndef __NCURSES_H__
#define __NCURSES_H__
#include "common.h"

// TODO: Implement linked list as a way of handling the
// growing (and shortening) snake

void
init_ncurses() {
	/*
	 * Initialize ncurses and set variables
	 */

	//void getmaxyx(WINDOW *win, int y, int x);

	initscr();
	start_color();
	raw();
	noecho();
	keypad(stdscr, true);
	curs_set(0);
}

void
kill_screen(WINDOW *local_win) {
	delwin(local_win);
}

void
die(WINDOW *local_win) {
	delwin(local_win);
	endwin();
	exit(EXIT_SUCCESS);
}

WINDOW
*create_new_win(int height, int width, int startx, int starty) {
	WINDOW *local_win = newwin(height, width, starty, startx);
	keypad(local_win, true);

	// TODO: Create a border around the window
	box(local_win, 0, 0);

	wrefresh(local_win);
	return local_win;
}

#endif //__NCURSES_H__
