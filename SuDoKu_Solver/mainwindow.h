#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ui_mainwindow.h>
#include <sudokusolver.h>

namespace Ui {
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
     * @brief solveSudoku
     */
    void solveSudoku();

    /**
     * @brief clearPuzzle
     */
    void clearPuzzle();

    /**
     * @brief tableEdit
     * @param row
     * @param column
     */
    void tableEdit(int row, int column);

    /**
     * @brief changeMode
     */
    void changeMode();

    /**
     * @brief loadFile
     */
    void loadFile();

    /**
     * @brief generatePuzzle
     */
    void generatePuzzle();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
