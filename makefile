sudoku: main.o sudoku.o
	g++ -g -Wall main.o sudoku.o -o sudoku
main.o: main.cpp
	g++ -g -Wall -c main.cpp
sudoku.o: sudoku.cpp
	g++ -g -Wall -c sudoku.cpp
clean:
	rm -rf *.o sudoku
