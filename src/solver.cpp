#include "../Headers/solver.h"
#include <iostream>
#include <unordered_set>
#include <set>

// Conditions for getting the right solution
bool Solver::is_valid(GRID& grid, int r, int c, int k)
{
	// Checking every row
	for (int i = 0; i < 9; ++i) {
		if (grid[r][i] == k)
			return false;
	}

	// Checking every column
	for (int i = 0; i < 9; ++i) {
		if (grid[i][c] == k)
			return false;
	}

	// Checking every subgrid 3x3
	int SubRowStart{ r / 3 * 3 }; 
	int SubColStart{ c / 3 * 3 }; 

	for (int i = SubRowStart; i < SubRowStart + 3; ++i) {
		for (int j = SubColStart; j < SubColStart + 3; ++j) {
			if (grid[i][j] == k)
				return false; 
		}
	}

	return true; 
}


// Backtracking Algorithm for trying every possible value in each cell that could generate the correct final solution
bool Solver::solve(GRID& cells, int r = 0 , int c = 0)
{
	// Sudoku Solved
	if (r == 9)
		return true;

	// Finished a Row 
	if (c == 9)
		return solve(cells, r + 1, 0); 

	// Skip filled cells
	if (cells[r][c] != 0)
		return solve(cells, r, c + 1);

	for (int k = 1; k <= 9; k++) {
		if (is_valid(cells, r, c, k)) {
			cells[r][c] = k; 
			if (solve(cells, r, c + 1)) {
				return true; 
			}
			cells[r][c] = 0; // Backtrack
		}
		else if (k == 9 && !is_valid(cells, r, c, 9)) {
			return false;
		}
	}
	return false; // No Correct solution found
}


