CXX = g++
CXXFLAGS = -Wall -Wextra -g 
EXE = sudoku
OBJ = main.o sudoku.o

$(EXE): $(OBJ)
	$(CXX) $^ -o $@

%.o: %.cpp makefile
	$(CXX) $(CXXFLAGS) -c $<

.phony: clean
clean:
	rm -rf *.o sudoku
