#pragma once
#include <vector>

typedef std::vector<std::vector<int>> GRID;

struct Solver {
	bool is_valid(GRID& grid, int r, int c, int k);
	bool solve(GRID& cells, int r, int c);
};
