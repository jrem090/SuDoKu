#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <QObject>

/**
 * @brief The SudokuSolver class This method is responsible for managing the details
 * and methods of Sudoku
 */
class SudokuSolver
{

public:
    SudokuSolver();
    
    ///Grid representing Hints/starting points
    int input[9][9];
    ///Grid holding solved values
    int solution[9][9];
    ///Grid holding user generated guesses
    int user[9][9];

    /**
     * @brief checkBox This method tests that there are no other copies of
     * test_int in the 3x3 box surrounding (row,col)
     * @param row
     * @param col
     * @param test_int
     * @return returns true if test_int fuffils check box rules
     */
    bool checkBox(int row, int col, int test_int);

    /**
     * @brief checkHorizontal This method checks that there are no instances of
     * test_int in the specified row, ignoring the col position
     * @param row
     * @param col
     * @param test_int
     * @return returns true that test_int satisfies the horizontal Sudoku rule
     */
    bool checkHorizontal(int row, int col, int test_int);

    /**
     * @brief checkVertical This method checks that there are no instances of
     * test_int in the specified column(col), ignoring the row position
     * @param row
     * @param col
     * @param test_int
     * @return returns true that test_int satisfies the vertical Sudoku rule
     */
    bool checkVertical(int row, int col, int test_int);

    /**
     * @brief setInput This method sets the the value at row,col for all arrays
     *  to the specified value
     * @param row
     * @param col
     * @param value
     */
    void setInput(int row, int col, int value);

    /**
     * @brief solve This method uses a recursive algorithm to solve a Sudoku
     * problem given valid inputs
     * @param row
     * @param col
     * @return returns true if the solution is valid
     */
    bool solve(int row, int col);

    /**
     * @brief reset This method resets all arrays
     */
    void reset();

    /**
     * @brief generatePuzzle This method generates a Sudoku Puzzle in an
     * EXTREMELY brute force manner
     */
    void generatePuzzle();

    /**
     * @brief checkUserSolution This method checks if the user solution is a
     * valid solution
     * @return returns true if the user solution is valid/correct
     */
    bool checkUserSolution();

    /**
     * @brief importSudokuFromFile This method parses a file containing a
     * Sudoku Puzzle
     * @param filename QString holding filename to be parsed
     * @return true if puzzle was parsed succesfully and is a valid puzzle
     */
    bool importSudokyFromFile(QString filename);
};

inline void SudokuSolver::setInput(int row, int col, int value)
{
    input[row][col]    = value;
    solution[row][col] = value;
    user[row][col]     = value;
}

#endif // SUDOKUSOLVER_H
