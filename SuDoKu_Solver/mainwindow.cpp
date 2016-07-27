#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //format table_widget cells
    for(int i = 0; i<9; i++)
    {
      for(int j =0; j< 9; j++)
      {
          bool isShaded = ((int)(i/3)+(int)(j/3))%2;
          QTableWidgetItem* item = new QTableWidgetItem();
          item->setTextAlignment(Qt::AlignCenter);
          if(isShaded)
              item->setBackgroundColor(QColor(225,225,225));
        ui->tableWidget->setItem(i,j,item);

      }
    }

    connect(ui->tableWidget, SIGNAL(cellChanged(int,int)),
                     this, SLOT(tableEdit(int, int)));
    connect(ui->solveButton, SIGNAL(pressed()),
                             this, SLOT(solveSudoku()));
    connect(ui->clearButton, SIGNAL(pressed()),
                             this, SLOT(clearPuzzle()));

    solver = SudokuSolver();
    solver.reset();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::solveSudoku()
{
    QString t;
    if(solver.solve(0,0))
    {
        std::cout << "IT SHOULD BE SOLVED\n";
        /*for(int i = 0; i < 9; i ++)
        {
            for(int j = 0; j<9; j++)
            {
                std::cout << &solver.solution[i][j] << " ";
            }
             std::cout << std::endl;
        }*/

        for(int i = 0; i<9; i++)
        {
          for(int j =0; j< 9; j++)
          {

              t.setNum(solver.solution[i][j]);
              //ui->tableWidget->item(i,j)->setData(11,t);
            ui->tableWidget->item(i,j)->setData(Qt::DisplayRole,t);
            //ui->tableWidget->item(i,j)->setData(Qt::UserRole, solver.solution[i][j]);
          }
        }
        ui->tableWidget->repaint();
        //write solved
    }
    else
    {
        //write error
    }

}

void MainWindow::clearPuzzle()
{
    QString t = "";
    solver.reset();
    for(int i = 0; i<9; i++)
    {
      for(int j =0; j< 9; j++)
      {
           ui->tableWidget->item(i,j)->setData(Qt::DisplayRole,t);
      }
    }
}

void MainWindow::tableEdit(int row, int column)
{
    try
    {
        int test_int = ui->tableWidget->item(row,column)->data(0).toInt();

        if(test_int > 0 && test_int <= 9)
        {
            solver.setInput(row,column,test_int);

            std::cout << "good ";
        }

        std::cout << "table edit performed\n";
        /*else
        {
            bool isShaded = ((int)(row/3)+(int)(column/3))%2;
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignCenter);
            if(isShaded)
                item->setBackgroundColor(QColor(225,225,225));
            ui->tableWidget->setItem(row,column,item);
            //text edit says invalid entry
        }*/
    }
    catch(int e){}
}
