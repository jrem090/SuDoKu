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
<<<<<<< HEAD
    bool is_user_mode;
=======

    bool user_mode;
>>>>>>> debd226948e8e0471e33e99df792fd63697c4384

public slots:
    /**
     * @brief solveSudoku
     */
    void solveSudoku();

    /**
     * @brief clearPuzzle
     */
    void clearPuzzle();
<<<<<<< HEAD
=======

    /**
     * @brief tableEdit
     * @param row
     * @param column
     */
    void tableEdit(int row, int column);

    /**
     * @brief changeMode
     */
>>>>>>> debd226948e8e0471e33e99df792fd63697c4384
    void changeMode();
    void loadFile();
    void generatePuzzle();
    void tableEdit(int row, int column);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
