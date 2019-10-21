#ifndef SUDOKU_H_
#define SUDOKU_H_

void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);
bool is_complete(char board[9][9]);
bool make_move(char position[2], char digit, char board[9][9]);
bool save_board(const char* filename, char board[9][9]);
bool solve_board(char board[9][9]);
bool is_valid(char board[9][9], int row_index, int column_index, char digit);
bool find_first_empty_slot(char board[9][9], int& row_index, int& column_index);
bool solve_board(char board[9][9], int& recursion_count);
void test_mistery(const char* filename, char board[9][9]);

#endif // SUDOKU_H_