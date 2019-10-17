#include <iostream>
#include "sudoku.h"

using namespace std;

int main(){
  char board[9][9];
  load_board("easy.dat", board);
  display_board(board);
}
