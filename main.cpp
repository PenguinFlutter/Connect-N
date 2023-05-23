#include <iostream>
#include <stdlib.h>
#include "game_compute.h"
#include <stdbool.h>

//main function
int main(int argc, char** argv) { // manipulate to take command line args
	int num_rows = 0;
	int num_cols = 0;
	int num_to_win = 0;
	//pointer for board
	char** board;

	//send argc to function to determine for valid
	check_args_from_user(argc);

	//converts arg to intergers  for  use
	sscanf(argv[1], "%d", &num_rows);
	sscanf(argv[2], "%d", &num_cols);
	sscanf(argv[3], "%d", &num_to_win);

	// create empty 2d array
	board = create_empty_board(num_rows, num_cols);

	// fill board with char
	fill_board(board, num_rows, num_cols);

	// show user the board
	print_board(board, num_rows, num_cols);

	// begin game with player 1 starting
	player_1_compute(board, num_to_win, num_cols, num_rows);

	return 0;
}
