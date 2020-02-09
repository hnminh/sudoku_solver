#include <iostream>

#define DIMENSION 9
#define GRID_FULL make_pair(DIMENSION, DIMENSION)
#define BLANK 0

using namespace std;

void splashScreen(){
	cout << "Welcome to the Sudoku Solver" << endl;
	cout << "Please enter the grid you want to solve in this format" << endl;
	cout << "+-------+-------+-------+" << endl;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++)
			cout << "| x x x | x x x | x x x |" << endl;
		cout << "+-------+-------+-------+" << endl;
	}

	cout << "The blank space is declared as 0" << endl;
}

void printResult(int grid[DIMENSION][DIMENSION]){

	cout << "Result" << endl;

	for (int row = 0; row < DIMENSION; row++){
		if (row%3 == 0) cout << "+-------+-------+-------+" << endl;

		for (int col = 0; col < DIMENSION; col++){
			if (col%3 == 0) cout << "| ";
			cout << grid[row][col] << " ";
		}
		cout << "|" << endl;
	}
	cout << "+-------+-------+-------+" << endl;

}

bool usedInRow(int grid[DIMENSION][DIMENSION], int row, int value){

	for (int col = 0; col < DIMENSION; col++)
		if (grid[row][col] == value) return true;

	return false;

}

bool usedInColumn(int grid[DIMENSION][DIMENSION], int col, int value){

	for (int row = 0; row < DIMENSION; row++)
		if (grid[row][col] == value) return true;

	return false;

}

bool usedInBox(int grid[DIMENSION][DIMENSION], int startingRow, int startingCol, int value){

	for (int row = startingRow; row <= startingRow + 2; row++)
		for (int col = startingCol; col <= startingCol + 2; col++){
			if (grid[row][col] == value) return true;
		}

	return false;

}

pair<int, int> findNextBlank(int grid[DIMENSION][DIMENSION]){

	for (int row = 0; row < DIMENSION; row++)
		for (int col = 0; col < DIMENSION; col++)
			if (grid[row][col] == BLANK) return make_pair(row, col);

	// in case no blank is found
	return GRID_FULL;

}

bool solved(int grid[DIMENSION][DIMENSION]){

	pair<int, int> nextBlank = findNextBlank(grid);
	if (nextBlank == GRID_FULL) return true;
	else {

		// the row and column of the blank
		int row = nextBlank.first;
		int col = nextBlank.second;

		// try for that blank from 1 to 9
		for (int value = 1; value <= 9; value++)

			// if the value hasn't used in any row, column or box
			if (!usedInRow(grid, row, value) && !usedInColumn(grid, col, value) && !usedInBox(grid, row - row%3, col - col%3, value)){

				grid[row][col] = value;

				// attempt to the next one
				if (solved(grid))	// if the grid is full then this case is true
					return true;
				else	// the grid is unable to full, so this case is wrong
					grid[row][col] = BLANK;
			}
			// the wrong case
			return false;
	}

}

int main(){
	freopen("sudokuSolver.inp", "r", stdin); freopen("sudokuSolver.out", "w", stdout);

	splashScreen();

	// reading the grid
	int grid[DIMENSION][DIMENSION];
	for (int row = 0; row < DIMENSION; row++)
		for (int col = 0; col < DIMENSION; col++)
			cin >> grid[row][col];

	if (solved(grid)) printResult(grid);
	else cout << "Unable to solve this grid!" << endl;

}