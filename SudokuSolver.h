#pragma once
class SudokuSolver
{
public:
	SudokuSolver();
	~SudokuSolver();
    static bool SolveSudoku(int sudoku[9][9]);
};

