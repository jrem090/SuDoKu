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
    void solveSudoku();
    void clearPuzzle();
    void changeMode();
    void loadFile();
    void generatePuzzle();
    void tableEdit(int row, int column);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
