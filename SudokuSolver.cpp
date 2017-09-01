#include "SudokuSolver.h"
#include <vector>
#include "DancingLinkSolver.h"

SudokuSolver::SudokuSolver()
{
}


SudokuSolver::~SudokuSolver()
{
}

std::vector<int> genLine(int row, int column, int content) {
    std::vector<int> grid;
    int n_grid = row * 9 + column;
    int n_row_content = row * 9 + (content - 1) + 81;
    int n_column_content = column * 9 + (content - 1) + 162;
    int n_grid_content = ((row / 3) * 3 + column / 3)*9 + (content-1)+243;
    grid.push_back(n_grid);
    grid.push_back(n_row_content);
    grid.push_back(n_column_content);
    grid.push_back(n_grid_content);
    /*
    for (int i : grid) {
        printf("%d ",i);
    }
    printf("\n");
    */
    return grid;
}
bool SudokuSolver::SolveSudoku(int sudoku[9][9])
{
    std::vector<std::vector<int> > problem;
    for (int row = 0; row < 9; row++) {
        for (int column = 0; column < 9; column++) {

            if (sudoku[row][column] != 0) {
                int content = sudoku[row][column];
                problem.push_back(genLine(row,column,content));
            }
            else {
                for (int i = 1; i <= 9; i++) {
                    int content = i;
                    problem.push_back(genLine(row, column, content));
                }
            }

        }
    }
    DancingLinkSolver dls(problem,324);
    bool res=dls.Solve();
    if (!res) return false;
    //printf("%d\n", dls.Solve());
    std::vector<int> ans = dls.ans();
    //std::reverse(ans.begin(), ans.end());
    for (int i : ans) {
        std::vector<int> line = problem[i-1];
        //printf("%d %d %d %d\n",line[0],line[1],line[2],line[3]);
        int idx = line[0];
        int row = idx / 9;
        int column = idx % 9;
        int lowerbound = row * 9 +81;
        int result = line[1] - lowerbound;
        //printf("%d %d %d\n",row,column,result+1);
        sudoku[row][column] = result+1;
        return true;
    }
}
