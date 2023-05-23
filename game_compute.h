#ifndef GAME_COMPUTE_H
#define GAME_COMPUTE_H
#include <stdbool.h>

// connects function calling from main.c to game_compute.c
	void check_args_from_user(int val);
	char** create_empty_board(int num_rows, int num_cols);
	void fill_board(char** board, int num_rows, int num_cols);
	void print_board(char** board, int num_rows, int num_cols);
	void game_play(char** board, int num_to_win, int num_cols, int num_rows);
	void player_1_compute(char** board, int num_to_win, int num_cols, int num_rows);
	void player_2_compute(char** board, int num_to_win, int num_cols, int num_rows);
	bool check_user_input(char** board, int num_cols, int num_rows, int user_input);
	int place_on_board(char** board, int num_cols, int num_rows, int user_input);
#endif
