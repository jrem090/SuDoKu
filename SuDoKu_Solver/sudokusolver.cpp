#include "sudokusolver.h"
#include <iostream>
#include <stdlib.h>
#include <QFile>
#include <QTextStream>

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

bool SudokuSolver::checkUserSolution()
{
    bool isSolved = true;
    for(int i = 0; i < 9 ; i++)
    {
        int checksum_row = 0;
        int checksum_col = 0;

        for(int j = 0; j < 9; j++)
        {
            std::cout << user[i][j] + " ";
            if(user[i][j]<0 || user[i][j] > 9)
            {
                //std::cout << "\n   FALSE \n";
                isSolved = false;
            }

            if(user[j][i]<0 || user[j][i] > 9)
            {
                isSolved = false;
                //std::cout << "\n   FALSE \n";
            }

            checksum_row += user[i][j];
            checksum_col += user[j][i];
        }
        std::cout << "\n";
        if(checksum_col != 45 || checksum_col != 45)
        {
            isSolved = false;
        }
    }

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            int checksum_box = 0;
            for(int k = 0; k < 3; k++)
            {
                for(int l = 0; l < 3; l++)
                {
                    checksum_box += user[k+ (i*3)][l + (j*3)];
                }
            }
            if(checksum_box != 45)
                isSolved = false;
        }
    }

    return isSolved;
}

void SudokuSolver::reset()
{
    for(int i = 0 ; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            input[i][j]    = 0;
            solution[i][j] = 0;
            user[i][j]     = 0;
        }
    }
}
 bool SudokuSolver::importSudokyFromFile(QString filename)
 {
     reset();
     QFile input_file(filename);
      bool read_correctly = true;
     if (input_file.open(QIODevice::ReadOnly | QIODevice::Text))
     {
         QTextStream in(&input_file);
         QString line = in.readLine();


         for(int i = 0; i < 9; i++)
         {
             if(line.isNull())
             {
                 read_correctly = false;
                 break;
             }
             if(line.length()<9)
             {
                 read_correctly = false;
                 break;
             }
             for(int j = 0; j < 9; j++)
             {
                 int value = line.at(j).digitValue();
                 if(value > 0 && value < 10)
                 {
                     input[i][j]    = value;
                     solution[i][j] = value;
                 }
                std::cout  << value << " ";
             }
             std::cout <<"\n";
             line = in.readLine();
         }
     }

     read_correctly = solve(0,0);
     for(int i = 0 ; i < 9; i++)
     {
         for(int j = 0; j < 9; j++)
         {
             solution[i][j] = 0;
         }
     }

     return read_correctly;
 }

void SudokuSolver::generatePuzzle()
{
    bool can_solve = false;
    while(!can_solve)
    {
        reset();
        //Very Brute force. Much gross
        for(int i = 0; i < 25; i++)
        {
            int box_col = rand() % 9;
            int box_row = rand() % 9;
            int box_val = rand() % 9 +1;

            //check cell is not already full. If not filled, fill with new value
            if(input[box_row][box_col]==0)
            {
                //cycle through values until solvable value is found
                while(!(checkBox(box_row,box_col,box_val) &&
                        checkHorizontal(box_row,box_col,box_val) &&
                        checkVertical(box_row,box_col,box_val)))
                {
                    box_val++;
                    box_val = box_val % 9;
                    if(box_val == 0)
                        box_val++;
                }

                input[box_row][box_col]    = box_val;
                solution[box_row][box_col] = box_val;
            }
        }
        can_solve = solve(0,0);
        for(int i = 0 ; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                solution[i][j]    = 0;
            }
        }

    }

}
