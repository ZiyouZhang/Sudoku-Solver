#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
    for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

// Check if all board positions are occupied.
// i.e. All dots are replaced by valid digits.
bool is_complete(char board[9][9]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (board[i][j] < '1' || board[i][j] > '9')
        return false;
    }
  }
  return true;
}

// Check if the move is valid (the position is in range and the slot is unoccupied).
// If not, leave the board unmodified. If valid, make the move.
bool make_move(const char position[], char digit, char board[9][9]) {
  
  // Work out corresponding index.
  int row_index = position[0] - 'A';
  int column_index = position[1] - '1';

  // Check the validity of the digit.
  if (digit < '1' || digit > '9')
    return false;

  // Check the validity of row_index and column_index range.
  if (row_index < 0 || row_index > 8 || column_index < 0 || column_index > 8)
    return false;

  // Check if the position is occupied.
  if (isdigit(board[row_index][column_index]))
    return false;

  // Check if the move follows the sudoku rule.
  if (!is_valid(board, row_index, column_index, digit))
    return false;

  // Place the digit and return true.
  board[row_index][column_index] = digit;
  return true;
}

// Check if setting the slot board[row_index][column_index] to digit is valid or not.
bool is_valid(char board[9][9], int row_index, int column_index, char digit) {
  
  // Check if there is repetition in the column.
  for (int i = 0; i < 9; i++) {
    if (board[i][column_index] == digit)
      return false;
  }

  // Check if there is repetition in the row.
  for (int j = 0; j < 9; j++) {
    if (board[row_index][j] == digit)
      return false;
  }

  // Check if there is repetition in the 3x3 subframe.
  for (int a = 3 * (row_index / 3); a < 3 * (row_index / 3) + 3; a++) {
    for (int b = 3 * (column_index / 3); b < 3 * (column_index / 3) + 3; b++) {
      if (board[a][b] == digit)
        return false;
    }
  }

  return true;
}

// Save the board to a file.
bool save_board(const char* filename, char board[9][9]) {
  
  ofstream out_stream;
  out_stream.open(filename);

  // Write digits to the output file. Handle error using try-catch to return false.
  for (int i = 0; i < 9; i ++) {
    for (int j = 0; j < 9; j++) {
      try {
        out_stream.put(board[i][j]);
      }
      catch (exception& e) {
        return false;
      }
    }
    // Write '\n' to the ooutput file. Handle error using try-catch to return false.
    try {
      out_stream.put('\n');
    }
    catch (exception& e) {
      return false;
    }
  }

  out_stream.close();
  return true;
}

// Recursive approach for solving the sudoku.
bool solve_board(char board[9][9]) {
  
  int row_index = 0;
  int column_index = 0;

  // Termination condition: all filled and no empty slot left.
  // If there is empty slot, the function will modify row_index and column_index to that slot.
  if (!find_first_empty_slot(board, row_index, column_index))
    return true;
  
  // Recursion: try 1 to 9 in current empty slot.
  // If the move is valid, go to next iteration and try to solve next empty slot.
  // If all numbers are tried and none is valid, return false (back to previous stack).
  // If it is not a valid move, reset the value.
  for (char i = '1'; i <= '9'; i++) {
    if (is_valid(board, row_index, column_index, i)) {
      board[row_index][column_index] = i;
      // Check the following iteration.
      if (solve_board(board))
        return true;
      // This value will not produce a valid result. Reset the value.
      board[row_index][column_index] = '.';
    }
  }
  return false;
}

// Find the first empty slot for recursion analysis.
// If all slots are filled, return false.
bool find_first_empty_slot(char board[9][9], int& row_index, int& column_index) {
  for (row_index = 0; row_index < 9; row_index++) {
    for (column_index = 0 ; column_index < 9; column_index++) {
      if (board[row_index][column_index] == '.')
        return true;
    } 
  }
  return false;
}

// Recursive approach for solving the sudoku with recursion count.
bool solve_board(char board[9][9], int& recursion_count) {
  
  // Increment recursion count by 1 at the beginning of the function.
  recursion_count++;
  int row_index = 0;
  int column_index = 0;

  // Termination condition: all filled and no empty slot left.
  // If there is empty slot, the function will modify row_index and column_index to that slot.
  if (!find_first_empty_slot(board, row_index, column_index))
    return true;

  // Recursion: try 1 to 9 in current empty slot.
  // If the move is valid, go to next iteration and try to solve next empty slot.
  // If all numbers are tried and none is valid, return false (back to previous stack).
  // If it is not a valid move, reset the value.
  for (char i = '1'; i <= '9'; i++) {
    if (is_valid(board, row_index, column_index, i)) {
      board[row_index][column_index] = i;
      // Check the following iteration.
      if (solve_board(board, recursion_count))
        return true;
      // This value will not produce a valid result. Reset the value.
      board[row_index][column_index] = '.';
    }
  }
  return false;
}

// Test the mystery file and output recursion time on the screen.
void test_mystery(const char* filename, char board[9][9]) {
  int recursion_count = 0;
  load_board(filename, board);
  if (solve_board(board, recursion_count)) {
    cout << "The board in \'" << filename << "\' has a solution:" << endl;
  } else {
    cout << "A solution cannot be found for mystery." << endl;
  }
  cout << "The recursion count is: " << recursion_count << endl;
  cout << endl;
}

