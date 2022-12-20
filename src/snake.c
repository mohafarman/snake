#include "common.h"
#include "snake.h"
#include "ncurses.h"

#define HEIGHT 400
#define WIDTH 300
#define MAIN_MENU_WIN_X 6
#define MAIN_MENU_WIN_Y 6

void
main_menu_loop() {
	int user_input;
	ITEM **main_menu_items = NULL;
	ITEM *selected_item;
	WINDOW *main_menu_win = NULL;
	int num_choices = ARRAY_SIZE(main_menu_choices[0]);
	int main_menu_win_height, main_menu_win_width;

	MENU *main_menu = populate_menu(main_menu_choices,
			num_choices,
			main_menu_items);

	main_menu_win = create_new_win(stdscr_maxy / 2, stdscr_maxx / 2,
			MAIN_MENU_WIN_Y, MAIN_MENU_WIN_X);
	getmaxyx(main_menu_win, main_menu_win_height, main_menu_win_width);

	set_menu_win(main_menu, main_menu_win);
	set_menu_sub(main_menu, derwin(main_menu_win, 6, 38, 2, 1));

	set_menu_mark(main_menu, " * ");

	box(main_menu_win, 0, 0);

	post_menu(main_menu);
	wrefresh(main_menu_win);

	// TODO: Use goto to throw exit and dealloc memory

	while ((user_input = wgetch(main_menu_win)) != KEY_F(1)) {
		// TODO: Display menu to start, exit (options?) or about
		switch(user_input) 
		{
			case KEY_DOWN:
				menu_driver(main_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(main_menu, REQ_UP_ITEM);
				break;
			case 10:	// Return
				// If user selected Start Game
				if (strcmp(item_name(current_item(main_menu)), main_menu_choices[0]) == 0) 
				{
					// Start the game loop
				}
				// If user selected About
				else if (strcmp(item_name(current_item(main_menu)), main_menu_choices[1]) == 0) 
				{
					// Show about page
				}
				else 
				{
					die(main_menu_win);
				}
				break;
		}
	}

	if (user_input == KEY_F(1)) {
		fprintf(stdout, "User exited the game\n");
		printf("User exited the game\n");
		die(main_menu_win);
	} 
}

int main() {
	const char *to_exit_msg = "Press F1 to exit.";
	init_ncurses();
	getmaxyx(stdscr, stdscr_maxy, stdscr_maxx);

	mvwprintw(stdscr, 0, 0, to_exit_msg);
	refresh();

	main_menu_loop();

	// End ncurses
	int err = endwin();
	if (err) {
		fprintf(stderr, "Exited ncurses : %s\n", strerror(errno));
	} else {
		fprintf(stdout, "Exited ncurses : %s\n", strerror(errno));
	}
	return 0;
}
