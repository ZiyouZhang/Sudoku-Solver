#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

  char board[9][9];

  // This section illustrates the use of the pre-supplied helper functions.
  cout << "============= Pre-supplied functions =============" << "\n\n";

  cout << "Calling load_board():" << '\n';
  load_board("puzzles/easy.dat", board);

  cout << '\n' << "Displaying Sudoku board with display_board():" << '\n';
  display_board(board);
  cout << "Done!" << "\n\n";

  cout << "=================== Question 1 ===================" << "\n\n";

  load_board("puzzles/easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << "\n\n";

  load_board("puzzles/easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << "\n\n";

  cout << "=================== Question 2 ===================" << "\n\n";

  load_board("puzzles/easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);
  cout << endl;

	// Test position out of range.
  cout << "Putting '1' into Z9 is ";
  if (!make_move("Z9", '1', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);
  cout << endl;

  // Test value out of range.
  cout << "Putting '0' into I8 is ";
  if (!make_move("I8", '0', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);
  cout << endl;

  // Test overwhrite existing value.
  cout << "Putting '3' into A4 is ";
  if (!make_move("A4", '3', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);
  cout << endl;

  // Test input an against-sudoku-rule value.
  cout << "Putting '4' into A1 is ";
  if (!make_move("A1", '4', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);
  cout << endl;

  cout << "=================== Question 3 ===================" << "\n\n";

  load_board("puzzles/easy.dat", board);
  if (save_board("puzzles/easy-copy.dat", board))
    cout << "Save board to 'easy-copy.dat' successful." << '\n';
  else
    cout << "Save board failed." << '\n';
  cout << '\n';

  cout << "=================== Question 4 ===================" << "\n\n";

  load_board("puzzles/easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << '\n';
    display_board(board);
  } else 
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  load_board("puzzles/medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << '\n';
    display_board(board);
  } else 
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  // Test an already filled sudoku.
  load_board("puzzles/easy-solution.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy-solution' board has a solution:" << '\n';
    display_board(board);
  } else 
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  // Test an empty sudoku.
  load_board("puzzles/empty.dat", board);
  if (solve_board(board)) {
    cout << "The 'empty' board has a solution:" << '\n';
    display_board(board);
  } else 
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  cout << "=================== Question 5 ===================" << "\n\n";

	// Test all 
  test_mystery("puzzles/easy.dat", board);
  test_mystery("puzzles/medium.dat", board);
  test_mystery("puzzles/mystery1.dat", board);
  test_mystery("puzzles/mystery2.dat", board);
  test_mystery("puzzles/mystery3.dat", board);

  return 0;
}
