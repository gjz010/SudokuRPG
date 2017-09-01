#pragma once
#include <vector>
using std::vector;
/*
Dancing Link solver for sparse matrices like sudoku.

*/
class DancingLinkSolver
{
public:
	DancingLinkSolver(std::vector<std::vector<int> >,int);
	bool Solve();
	std::vector<int> ans();
	~DancingLinkSolver();
private:
	struct Internal;
	int maxcol;
	Internal* data;
	void coverColumn(int col);
	void uncoverColumn(int col);
};

