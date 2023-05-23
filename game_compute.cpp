#include <iostream>
#include <stdlib.h>
#include "game_compute.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

// validate command line arg
void check_args_from_user(int val) {

	if (val > 4) {
		printf("Too many arguments entered\nUsage connectn.out num_rows num_columns\nnumber_of_pieces_in_a_row_needed_to_win\n");
		exit(0);
	} else if (val < 4) {
		printf("Not enough arguments entered\nUsage connectn.out num_rows num_columns\nnumber_of_pieces_in_a_row_needed_to_win\n");
		exit(0);
	}

}

// pointer to allocate space for an empty 2d array
char** create_empty_board(int num_rows, int num_cols) {
	char** board_empty = NULL;
	int b = 0;

  num_rows += 2;
  num_cols += 2;

	board_empty = (char**)malloc(sizeof(int*) * num_rows);

	for (b = 0; b < num_rows; ++b) {
		board_empty[b] = (char*)malloc(sizeof(int) * num_cols);
	}

	return board_empty;

}

// set up board with grid and '*'
void fill_board(char** board, int num_rows, int num_cols) {
	int a = 0;
	int b = 0;

	for(a = 0; a <= num_rows + 1; ++a) {
		for(b = 0; b <= num_cols + 1; ++b) {
      if (a < num_rows && b == 0) {
				board[a][b] = num_rows - (a + 1);
			} else if (a == num_rows && b == 0) {
        		board[a][b] = ' ';
    		} else if (a == num_rows && b > 0) {
				board[a][b] = b - 1;
			} else if (a != num_rows && b > 0) {
				board[a][b] = '*';
      }

		}

	}

}

// "Delete board" = free up the board and set it to NULL
void delete_board(char*** board, int num_rows, int num_cols) {
	// for loop variables
	int a = 0;

	// deleting array
	for (a = 0; a < num_rows + 1; ++a) {
		free((*board)[a]);
	}

	free(*board);

	*board = NULL;

}

// function to print updated or current board
void print_board(char** board, int num_rows, int num_cols) {

	int a = 0;
	int b = 0;

	for (a = 0; a < num_rows + 1; ++a) {
		for (b = 0; b < num_cols + 1; ++b) {
      if ((a < num_rows && b == 0) || (a == num_rows && b > 0)) {
        printf("%d ", board[a][b]);
      } else if ((a != num_rows && b > 0) || (a == num_rows && b == 0)) {
        printf("%c ", board[a][b]);
      }
		}
		printf("\n");
	}
}

// validate user input
bool check_user_input(char** board, int num_cols, int num_rows, int user_input) {
	int i = 0;

	if (user_input < 0) {
		return false;
	} else if (user_input > num_cols - 1) {
		return false;
	} else if ((user_input <= num_cols) && (user_input >= 0)) {
		// checks whether column is too full or not
		for (i = (num_rows - 1); i >= 0; i -= 1) {
			if (board[i][user_input + 1] == '*') {
				return true;
			} else if ((board[i][user_input] == 'X') || (board[i][user_input] == 'O')) {

				continue;
			}
		}
	}

	return false;

}

// function to place checker X on board player 1 specified
void place_on_board_1(char** board, int num_cols, int num_rows, int user_input) {
	int i = 0;

	for (i = (num_rows); i >= 0; i -= 1) {
			if (board[i][user_input + 1] == '*') {
				board[i][user_input + 1] = 'X';
				break;
			} else if ((board[i][user_input + 1] == 'X') || (board[i][user_input + 1] == 'O')) {
				continue;
			}
	}
}

// function to place checker O on board player 2 specified
void place_on_board_2(char** board, int num_cols, int num_rows, int user_input) {
	int i = 0;

	for (i = (num_rows); i >= 0; i -= 1) {
			if (board[i][user_input + 1] == '*') {
				board[i][user_input + 1] = 'O';
				break;
			} else if ((board[i][user_input + 1] == 'X') || (board[i][user_input + 1] == 'O')) {
				continue;
			}
	}

}

// function scans board to determine tie
bool game_tie_check(char** board, int num_rows, int num_cols) {
	int a = 0;
	int b = 0;

	// for loop to scan if '*' is present within the 2d array.
	for (a = 0; a < num_rows + 1; ++a) {
		for (b = 0; b < num_cols + 1; ++b) {
    		if (board[a][b] == '*') {
        		return false;
    		} else if ((board[a][b] == 'X') || (board[a][b] == 'O')) {
        		continue;
    		}
		}
	}

	return true;
}

// Scan for a vertical win
int check_vert(char** board, int num_rows, int num_cols, int num_to_win) {
	int counter1st = 0;
	int counter2nd = 0;
	int a = 0;
	int b = 0;
	int c = 0;


	for (a = 0; a < num_rows + 1; ++a) {
		for (b = 0; b < num_cols + 1; ++b) {
    		if (board[a][b] == 'X') {
        		for (c = 0; c <= num_to_win; ++c) { // player 1 win scan
        			if (board[a + c][b] == 'X') {
        				counter1st += 1;
        				if (counter1st == num_to_win) {
        					return 1;
        				} else {
        					continue;
        				}
        			} else if (board[a + c][b] == 'O' || board[a + c][b] == '*') {
        				break; // if not consecutive then stop
        			}
        		}

        		counter1st = 0;
    		} else if(board[a][b] == 'O') {
    			for (c = 0; c <= num_to_win; ++c) {
        			if (board[a + c][b] == 'O') { // player 2 win scan
        				counter2nd += 1;
        				if (counter2nd == num_to_win) {
        					return 2;
        				} else {
        					continue;
        				}
        			} else if (board[a + c][b] == 'X' || board[a + c][b] == '*') {
        				break; // if not consecutive then stop
        			}
        		}

        		counter2nd = 0;
    		} else if (board[a][b] == '*') {
        		continue;
    		}
		}
	}

	return 0;
}

//Scan for a horizontal win
int check_horz(char** board, int num_rows, int num_cols, int num_to_win) {
	int counter1st = 0;
	int counter2nd = 0;
	int a = 0;
	int b = 0;
	int c = 0;

	for (a = 0; a < num_rows + 1; ++a) {
		for (b = 0; b < num_cols + 1; ++b) {
    		if (board[a][b] == 'X') {
        		for (c = 0; c <= num_to_win; ++c) { // player 1 win scan
        			if (board[a][b + c] == 'X') {
        				counter1st += 1;
        				if (counter1st == num_to_win) {
        					return 1;
        				} else {
        					continue;
        				}
        			} else if (board[a][b + c] == 'O' || board[a][b + c] == '*') {
        				break; // if not consecutive then stop
        			}
        		}

        		counter1st = 0;
    		} else if(board[a][b] == 'O') {
    			for (c = 0; c <= num_to_win; ++c) { // player 2 win scan
        			if (board[a][b + c] == 'O') {
        				counter2nd += 1;
        				if (counter2nd == num_to_win) {
        					return 2;
        				} else {
        					continue;
        				}
        			} else if (board[a][b + c] == 'X' || board[a][b + c] == '*') {
        				break; // if not consecutive then stop
        			}
        		}

        		counter2nd = 0;

    		} else if (board[a][b] == '*') {
        		continue;
    		}
		}
	}

	return 0;
}

// Scan for a right diagonal win
int check_right_diag(char** board, int num_rows, int num_cols, int num_to_win) {
	int counter1st = 0;
	int counter2nd = 0;
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int same_row_count_X = 0;
	int same_row_count_O = 0;

	for (a = 0; a < num_rows + 1; ++a) {
		for (b = 0; b < num_cols + 1; ++b) {
    		if (board[a][b] == 'X') {
        		for (c = 0; c <= num_to_win; ++c) { // player 1 win scan
        			d = a - c;
        			if (d < 0) {
        				d = 0;
        				if (same_row_count_X == 1) {
        					break; // stop loop if we reach pass end of board bc no chance for a diagonal win
        				}
        				same_row_count_X += 1;
        			}
        			if (board[d][b + c] == 'X') {
        				counter1st += 1;
        				if (counter1st == num_to_win) {
        					return 1;
        				} else {
        					continue;
        				}
        			} else if (board[d][b + c] == 'O' || board[d][b + c] == '*') {
        				break; // if not consecutive then stop
        			}
        		}

        		counter1st = 0;
    		} else if(board[a][b] == 'O') {
    			for (c = 0; c <= num_to_win; ++c) { // player 2 win scan
    				d = a - c;
    				if (d < 0) {
        				d = 0;
        				if (same_row_count_O == 1) {
        					break; // stop loop if we reach pass end of board bc no chance for a diagonal win
        				}

        				same_row_count_X += 1;
        			}
        			if (board[d][b + c] == 'O') {
        				counter2nd += 1;
        				if (counter2nd == num_to_win) {
        					return 2;
        				} else {
        					continue;
        				}
        			} else if (board[d][b + c] == 'X' || board[d][b + c] == '*') {
        				break; // if not consecutive then stop
        			}
        		}

        		counter2nd = 0;

    		} else if (board[a][b] == '*') {
        		continue;
    		}
		}
	}

	return 0;

}

// Scan for a left diagonal
int check_left_diag(char** board, int num_rows, int num_cols, int num_to_win) {
	int counter1st = 0;
	int counter2nd = 0;
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int same_row_count_X = 0;
	int same_row_count_O = 0;
	int same_column_count_X = 0;
	int same_column_count_O = 0;
	int e = 0;

	for (a = 0; a < num_rows + 1; ++a) {
		for (b = 0; b < num_cols + 1; ++b) {
    		if (board[a][b] == 'X') {
        		for (c = 0; c <= num_to_win; ++c) { // player 1 win scan
        			d = a - c;
        			e = b - c;
        			if (d < 0) {
        				d = 0;
        				if (same_row_count_X == 1) {
        					break; // stop loop if we reach pass end of board bc no chance for a diagonal win
        				}
        				same_row_count_X += 1;
        			} else if (e < 0) {
        				e = 0;
        				if (same_column_count_X == 1) {
        					break; // stop loop if we reach pass end of board bc no chance for a diagonal win
        				}
        				same_column_count_X += 1;

        			}
        			if (board[d][e] == 'X') {
        				counter1st += 1;
        				if (counter1st == num_to_win) {
        					return 1;
        				} else {
        					continue;
        				}
        			} else if (board[d][e] == 'O' || board[d][e] == '*')
        				{
        				break; // if not consecutive then stop
        			}
        		}

        		counter1st = 0;
    		} else if(board[a][b] == 'O') {
    			for (c = 0; c <= num_to_win; ++c) { // player 2 win scan
    				d = a - c;
    				e = b - c;
    				if (d < 0) {
        				d = 0;
        				if (same_row_count_O == 1) {
        					break; // stop loop if we reach pass end of board bc no chance for a diagonal win
        				}
        				same_row_count_O += 1;
        			} else if (e < 0) {
        				e = 0;
        				if (same_column_count_O == 1) {
        					break; // stop loop if we reach pass end of board bc no chance for a diagonal win
        				}
        				same_column_count_O +=1;
        			}

        			if (board[d][e] == 'O') {
        				counter2nd += 1;
        				if (counter2nd == num_to_win) {
        					return 2;
        				} else {
        					continue;
        				}
        			} else if (board[d][e] == 'X' || board[d][e] == '*') {
        				break; // if not consecutive then stop
        			}
        		}

        		counter2nd = 0;

    		} else if (board[a][b] == '*') {
        		continue;
    		}
		}
	}

	return 0;

}

// function that will call each win check function
int game_win_check(char** board, int num_rows, int num_cols, int num_to_win) {

	// check vertical win
	if (check_vert(board, num_rows, num_cols, num_to_win) == 1) {
		print_board(board, num_rows, num_cols); // show winning board
		printf("Player 1 Won!\n");
		// free up board
		delete_board(&board, num_rows, num_cols);
		// exit program since winner is decided
		exit(0);
	} else if (check_vert(board, num_rows, num_cols, num_to_win) == 2) {
		print_board(board, num_rows, num_cols);
		printf("Player 2 Won!\n");
		delete_board(&board, num_rows, num_cols);
		exit(0);
	}

	// check horizontal win
	if (check_horz(board, num_rows, num_cols, num_to_win) == 1) {
		print_board(board, num_rows, num_cols);
		printf("Player 1 Won!\n");
		delete_board(&board, num_rows, num_cols);
		exit(0);
	} else if (check_horz(board, num_rows, num_cols, num_to_win) == 2) {
		print_board(board, num_rows, num_cols);
		printf("Player 2 Won!\n");
		delete_board(&board, num_rows, num_cols);
		exit(0);
	}

	// check right diagonal win
	if (check_right_diag(board, num_rows, num_cols, num_to_win) == 1) {
		print_board(board, num_rows, num_cols);
		printf("Player 1 Won!\n");
		delete_board(&board, num_rows, num_cols);
		exit(0);
	} else if (check_right_diag(board, num_rows, num_cols, num_to_win) == 2) {
		print_board(board, num_rows, num_cols);
		printf("Player 2 Won!\n");
		delete_board(&board, num_rows, num_cols);
		exit(0);
	}

	// check check_left_diag
	if (check_left_diag(board, num_rows, num_cols, num_to_win) == 1) {
		print_board(board, num_rows, num_cols);
		printf("Player 1 Won!\n");
		delete_board(&board, num_rows, num_cols);
		exit(0);
	} else if (check_left_diag(board, num_rows, num_cols, num_to_win) == 2) {
		print_board(board, num_rows, num_cols);
		printf("Player 2 Won!\n");
		delete_board(&board, num_rows, num_cols);
		exit(0);
	}

	return false;

}

// function for computing player 1 actions
void player_1_compute(char** board, int num_to_win, int num_cols, int num_rows) {

	int user_input = 0;


	printf("Enter a column between 0 and %d to play in: ", (num_cols - 1));
	scanf("%d", &user_input);
	// while check waits for correct user input
	while(check_user_input(board, num_cols, num_rows, user_input) != true) {
		printf("Enter a column between 0 and %d to play in: ", (num_cols - 1));
		scanf("%d", &user_input);
	}

	place_on_board_1(board, num_cols, num_rows, user_input);
	game_win_check(board, num_rows, num_cols, num_to_win); // check if the user has won
	if (game_tie_check(board, num_rows, num_cols) == true) { // !win then check tie
		print_board(board, num_rows, num_cols);
		printf("Tie game!\n");
		exit(0);
	}
	print_board(board, num_rows, num_cols); // print current board
	player_2_compute(board, num_to_win, num_cols, num_rows); // function calls to other player until win/tie
}

// function for computing player 2 actions
void player_2_compute(char** board, int num_to_win, int num_cols, int num_rows) {

	int user_input = 0;

	printf("Enter a column between 0 and %d to play in: ", (num_cols - 1));
	scanf("%d", &user_input);
	// while check waits for correct user inpput
	while(check_user_input(board, num_cols, num_rows, user_input) != true) {
		printf("Enter a column between 0 and %d to play in: ", (num_cols - 1));
		scanf("%d", &user_input);
	}

	place_on_board_2(board, num_cols, num_rows, user_input); // place marker location
	game_win_check(board, num_rows, num_cols, num_to_win); // check if the user has won
	if (game_tie_check(board, num_rows, num_cols) == true) { // !win then check tie
		print_board(board, num_rows, num_cols);
		printf("Tie game!\n");
		exit(0);
	}
	print_board(board, num_rows, num_cols); // print current board
	player_1_compute(board, num_to_win, num_cols, num_rows); //function calls to other player until win/tie
}
