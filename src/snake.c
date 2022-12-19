#include "common.h"
#include "snake.h"
#include "ncurses.h"

#define HEIGHT 400
#define WIDTH 300
#define GAME_SCREEN_X 4
#define GAME_SCREEN_Y 4

void
game_loop(WINDOW *game_screen) {
	int user_input;

	mvwprintw(game_screen, 0, 0, "Game window!");

	wrefresh(game_screen);
	while ((user_input = wgetch(game_screen)) != KEY_F(1) ) {
		// TODO: Display menu to start, exit (options?) or about
		switch(user_input) {
			default:
				continue;
		}
	}

	if (user_input == KEY_F(1)) {
		fprintf(stdout, "User exited the game\n");
		printf("User exited the game\n");
	} 

	// Dealloc
	kill_screen(game_screen);
}

int main() {
	const char *to_exit_msg = "Press F1 to exit.";
	init_ncurses();

	// Store max height and max width of stdscr
	// in global variables
	getmaxyx(stdscr, stdscr_maxy, stdscr_maxx);
	int game_screen_height = stdscr_maxy / 1.5;
	int game_screen_width = stdscr_maxx / 3;

	mvwprintw(stdscr, 0, 0, to_exit_msg);

	WINDOW *game_screen = create_new_win(game_screen_height, game_screen_width,
			GAME_SCREEN_Y, GAME_SCREEN_X);

	refresh();
	game_loop(game_screen);

	// End ncurses
	int err = endwin();
	if (err) {
		fprintf(stderr, "Exited ncurses : %s\n", strerror(errno));
	} else {
		fprintf(stdout, "Exited ncurses : %s\n", strerror(errno));
	}
	return 0;
}
