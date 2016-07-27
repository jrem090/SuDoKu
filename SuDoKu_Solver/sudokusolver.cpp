#include "sudokusolver.h"
#include <iostream>

SudokuSolver::SudokuSolver()
{

}

bool SudokuSolver::checkBox(int row, int col, int test_int)
{
    int row_offset = ((int)(row / 3)) * 3;
    int col_offset = ((int)(col / 3)) * 3;

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j <3; j++)
        {
            if(i + row_offset != row ||
                    j + col_offset != col)
            {
                if(solution[i+row_offset][j+col_offset] == test_int)
                    return false;
            }
        }
    }

    return true;

}

bool SudokuSolver::checkHorizontal(int row, int col, int test_int)
{
    for(int i = 0; i < 9; i++)
    {
        if(i!=col)
        {
            if(solution[row][i]==test_int)
            {
                return false;
            }
        }
    }
    return true;
}

bool SudokuSolver::checkVertical(int row, int col, int test_int)
{
    for(int i = 0; i < 9; i++)
    {
        if(i!=row)
        {
            if(solution[i][col]==test_int)
            {
                return false;
            }
        }
    }
    return true;
}

bool SudokuSolver::solve(int row, int col)
{
    if (input[row][col] != 0)
    {
        solution[row][col] = input[row][col];
        if(col == 8)
        {
            if(row == 8)
            {
                for(int i = 0; i < 9; i ++)
                {
                    for(int j = 0; j<9; j++)
                    {
                        std::cout << solution[i][j] << " ";
                    }
                     std::cout << std::endl;
                }
                return true;
            }
            else
            {
                if(solve(row+1,0))
                    return true;
            }
        }
        else
        {
            if(solve(row,col+1))
                    return true;
        }
    }
    else
    {
        for(int i = 1; i < 10; i++)
        {
            if(checkBox(row,col,i) &&
                    checkHorizontal(row,col,i) &&
                    checkVertical(row,col,i))
            {
                if(col == 8)
                {
                    if(row == 8)
                    {
                        solution[row][col] = i;
                        return true;
                    }
                    else
                    {
                        solution[row][col] = i;
                       if(solve(row+1,0))
                           return true;
                    }
                }
                else
                {
                    solution[row][col] = i;
                    if(solve(row,col+1))
                            return true;
                }
            }

        }
        solution[row][col] = 0;
        return false;
    }
   return false;
}

void SudokuSolver::reset()
{
    for(int i = 0 ; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            input[i][j]    = 0;
            solution[i][j] = 0;
        }
    }

}
