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
    cout << "Failed!" << '\n';
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

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << '\n';
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

// Check if all board positions are occupied.
// i.e. All dots are replaced by digits.
bool is_complete(char board[9][9]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (board[i][j] == '.')
        return false;
    }
  }
  return true;
}

// Check if the move is valid (the position is in range and the slot is unoccupied).
// If not, leave the board unmodified. If valid, make the move.
bool make_move(char position[], char digit, char board[9][9]) {
  assert(isupper(position[0]));
  assert(isdigit(position[1]));
  assert(digit >= '1' && digit <= '9');
  int row = position[0] - 'A';
  int column = position[1] - '1';
  if (row < 0 || row > 8 || column < 0 || column > 8)
    return false;
  if (isdigit(board[row][column]))
    return false;
  board[row][column] = digit;
  return true;
}

// Save the board to a file. ERROR HANDLING TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool save_board(const char* filename, char board[9][9]) {
  ofstream out_stream;
  out_stream.open(filename);
  for (int i = 0; i < 9; i ++) {
    for (int j = 0; j < 9; j++) {
      try {
        out_stream.put(board[i][j]);
      }
      catch (exception& e) {
        return false;
      }
    }
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

bool solve_board(char board[9][9]) {
  return true;
}
