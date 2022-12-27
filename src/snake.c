#include "common.h"
#include "snake.h"
#include "ncurses.h"

enum Difficulty {
	Easy = 1,
	Medium_D = 2,
	Hard = 3,
};

enum Speed {
	Slow = 1,
	Medium_S = 2,
	Fast = 3,
};

enum Map_Size {
	Small = 1,
	Medium_M = 2,
	Big = 3,
};

typedef struct snake_segment_s {
	int pos_y, pos_x;
	char shape;
	struct snake_segment_s *next_segment;
} snake_segment_s;

typedef struct game_options_s {
	enum Difficulty difficulty;
	enum Speed speed;
	enum Map_Size map_size;
} game_options_s;

void
main_menu() {
	int user_input;
	int game_finished;
	int num_choices = ARRAY_SIZE(main_menu_choices[0]);

	// Allocate memory for the main menu
	menu_s *main = malloc(sizeof(menu_s));

	if (main == NULL) {
		fprintf(stderr, "Memory allocation error for main menu : %s", strerror(errno));
	}

	main = init_menu(main, main_menu_choices, num_choices);
	wrefresh(main->window);

	while ((user_input = wgetch(main->window)) != KEY_F(1)) {
		switch(user_input) 
		{
			case KEY_DOWN:
				menu_driver(main->menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(main->menu, REQ_UP_ITEM);
				break;
				// VIM keybindings
			case 'j':
				menu_driver(main->menu, REQ_DOWN_ITEM);
				break;
			case 'k':
				menu_driver(main->menu, REQ_UP_ITEM);
				break;
			case 10:	// Return
				// If user selected Start Game
				if (strcmp(item_name(current_item(main->menu)), main_menu_choices[0]) == 0) 
				{
					mvwprintw(stdscr, 1, 0, item_name(current_item(main->menu)));
					refresh();

					wclear(main->window);
					// Start the game loop
					game_finished = game_loop();

					if (game_finished) {
						// Save score
					}
				}
				// If user selected Game Options
				else if (strcmp(item_name(current_item(main->menu)), main_menu_choices[1]) == 0) 
				{
					mvwprintw(stdscr, 2, 0, item_name(current_item(main->menu)));
					refresh();

				}
				else if (strcmp(item_name(current_item(main->menu)), main_menu_choices[2]) == 0) 
				{
					mvwprintw(stdscr, 3, 0, item_name(current_item(main->menu)));
					refresh();
					// Show about page
				}
				else 
				{
					goto exit_game;
				}
				break;
		}
	}

	if ( user_input == KEY_F(1) ) {
		goto exit_game;
	}

exit_game:
	free(main);
}

int
game_loop() {
	/*
	 * 1. Main Window
	 * 2. Scoreboard Window
	 * 3. Clear borders
	 * 4. Initialize game based on parameters (can be set in Options menu)
	 *	4.1. Size of window, speed of the game
	 * 5. Draw snake to the screen (shape? Circles? O)
	 * 6. Take user input
	 * 7. Collision detection
	 */

	int user_input;
	bool play = true, pause = false;
	WINDOW *game_win = NULL, *score_win = NULL, *howto_win = NULL;
	int game_win_height = stdscr_maxy / 1.5;
	int	game_win_width = stdscr_maxx / 1.5;
	int score_win_height = 8;
	int	score_win_width = 20;
	int howto_win_height = 12;
	int	howto_win_width = 20;

	game_win = create_new_win(game_win_height, game_win_width,
			GAME_WIN_Y, GAME_WIN_X);

	score_win = create_new_win(score_win_height, score_win_width,
			game_win_width + 6, GAME_WIN_X);

	howto_win = create_new_win(howto_win_height, howto_win_width,
			game_win_width + 6, GAME_WIN_X + score_win_height);

	wattron(score_win, A_BOLD);
	mvwprintw(score_win, 1, 1, "Top Score: ");
	mvwprintw(score_win, 4, 1, "Current Score: ");
	wattroff(score_win, A_BOLD);

	//wattron(howto_win);
	mvwprintw(howto_win, 1, 1, "'p' to pause");
	mvwprintw(howto_win, 2, 1, "arrows to move");
	mvwprintw(howto_win, 3, 1, "vim keybindings to move");
	//wattroff(howto_win);

	wrefresh(score_win);
	wrefresh(game_win);
	wrefresh(howto_win);

	int curr_y = 2, curr_x = 2;

	while (play) {
		/* 
		 * Input
		 * Update
		 * Render
		 */

		user_input = wgetch(game_win);

		// Input
		switch(user_input) 
		{
			// Update
			case KEY_DOWN:
				curr_y++;
				break;
			case KEY_UP:
				curr_y--;
				break;
			case KEY_RIGHT:
				curr_x++;
				break;
			case KEY_LEFT:
				curr_x--;
				break;
				// VIM keybindings
			case 'j':
				break;
			case 'k':
				break;
			case KEY_F(1):	// Return
				play = false;
				goto exit_game;
				break;
		}

		// Render
		wclear(game_win);
		box(game_win, 0, 0);
		mvwprintw(game_win, curr_y, curr_x, "Testing!!");
		wrefresh(game_win);
	}

	if ( user_input == KEY_F(1) ) {
		goto exit_game;
	}

exit_game:
	wclear(game_win);
	wclear(score_win);
	wclear(howto_win);
	wrefresh(game_win);
	wrefresh(score_win);
	wrefresh(howto_win);
	return 1;
}

WINDOW
*game_title() {
	WINDOW *title_win = NULL;
	int title_height = stdscr_maxy / 1.5;
	int	title_width = stdscr_maxx / 1.5;

	title_win = newwin(title_height, title_width, 4, 10);

	wattron(title_win, A_BOLD);
	mvwprintw(title_win, 1, 1, "Snake Game");
	wattroff(title_win, A_BOLD);

	wrefresh(title_win);
	return title_win;
}

int main() {
	const char *to_exit_msg = "Press F1 to exit.";
	init_ncurses();
	getmaxyx(stdscr, stdscr_maxy, stdscr_maxx);

	mvwprintw(stdscr, 0, 0, to_exit_msg);
	refresh();

	WINDOW *title = game_title();
	main_menu();


	kill_win(title);
	// End ncurses
	int err = endwin();
	if (err) {
		fprintf(stderr, "Exited ncurses : %s\n", strerror(errno));
	} else {
		fprintf(stdout, "Exited ncurses : %s\n", strerror(errno));
	}

	return 0;
}
