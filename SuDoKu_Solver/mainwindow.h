#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ui_mainwindow.h>
#include <sudokusolver.h>

namespace Ui {
/**
 * @brief Mainwindow This Class acts as the user interface. It relays changes
 * to the puzzle to the sudokusolver class and also handles the gui format
 * and graphics
 */
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    SudokuSolver solver;
    bool is_user_mode;

public slots:
    /**
     * @brief changeSkin This method changes the skin/style of the application
     * to the skin with the given int value
     * @param skin_id value of skin to be used
     */
    void changeSkin(int skin_id);
    /**
     * @brief solveSudoku This method solves the Sudoku puzzle through calling
     * the sudokusolver class
     */
    void solveSudoku();

    /**
     * @brief clearPuzzle This method removes all values from the puzzle
     */
    void clearPuzzle();

    /**
     * @brief tableEdit chenge the value at (row,col)
     * @param row
     * @param column
     */
    void tableEdit(int row, int column);

    /**
     * @brief changeMode this method alternates the mode between user mode and
     * solver mode
     */
    void changeMode();

    /**
     * @brief loadFile this method creates the file loader to load a Sudoku
     * puzzle
     */
    void loadFile();

    /**
     * @brief generatePuzzle This method generates a solvable sudoku puzzle
     * (currwently in a rather inefficient way)
     */
    void generatePuzzle();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
