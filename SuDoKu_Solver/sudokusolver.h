#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H


class SudokuSolver
{
public:
    SudokuSolver();

    int input[9][9];
    int solution[9][9];
    int user[9][9];

    bool checkBox(int row, int col, int test_int);
    bool checkHorizontal(int row, int col, int test_int);
    bool checkVertical(int row, int col, int test_int);

    void setInput(int row, int col, int value);

    bool solve(int row, int col);

    void reset();

    bool checkUserSolution();
};

inline void SudokuSolver::setInput(int row, int col, int value)
{
    input[row][col]    = value;
    solution[row][col] = value;
}

#endif // SUDOKUSOLVER_H
