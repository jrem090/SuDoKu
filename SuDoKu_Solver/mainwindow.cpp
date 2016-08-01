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
          QFont font = item->font();
          font.setBold(true);
          item->setTextAlignment(Qt::AlignCenter);
          item->setFont(font);
          if(isShaded)
              item->setBackgroundColor(QColor(225,225,225));
        ui->tableWidget->setItem(i,j,item);

      }
    }

    ui->label->setAlignment(Qt::AlignCenter);

    connect(ui->tableWidget, SIGNAL(cellChanged(int,int)),
                this, SLOT(tableEdit(int, int)));
    connect(ui->solveButton, SIGNAL(pressed()),
                this, SLOT(solveSudoku()));
    connect(ui->clearButton, SIGNAL(pressed()),
                this, SLOT(clearPuzzle()));
    connect(ui->modeButton, SIGNAL(pressed()),
                this, SLOT(changeMode()));

    ui->modeButton->setCheckable(true);

    solver = SudokuSolver();
    solver.reset();

    user_mode = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::solveSudoku()
{
    if(!user_mode)
    {
        QString t;
        if(solver.solve(0,0))
        {
            //std::cout << "IT SHOULD BE SOLVED\n";
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
                  if(solver.input[i][j]==0)
                  {
                      QFont font = ui->tableWidget->item(i,j)->font();
                      font.setBold(false);
                      ui->tableWidget->item(i,j)->setFont(font);
                  }
                ui->tableWidget->item(i,j)->setData(Qt::DisplayRole,t);
                //ui->tableWidget->item(i,j)->setData(Qt::UserRole, solver.solution[i][j]);
              }
            }
            ui->label->setText(QString("Sudoku Solved"));
            ui->tableWidget->repaint();
            //write solved
        }
        else
        {
             ui->label->setText(QString("Unable to Solve Sudoku"));
            //write error
        }
    }
    else
    {
        if(solver.checkUserSolution())
        {
               ui->label->setText(QString("You Solved The Puzzle!"));
        }
        else
        {
            ui->label->setText(QString("Puzzle Was Not Solved Correctly"));
        }
    }
}

void MainWindow::clearPuzzle()
{
    if(!user_mode)
    {
        QString t = "";
        solver.reset();
        for(int i = 0; i<9; i++)
        {
          for(int j =0; j< 9; j++)
          {
              QFont font = ui->tableWidget->item(i,j)->font();
              font.setBold(true);
               ui->tableWidget->item(i,j)->setData(Qt::DisplayRole,t);
               ui->tableWidget->item(i,j)->setFont(font);
          }
        }
         ui->label->setText(QString("Cleared Puzzle"));
    }
}

void MainWindow::changeMode()
{
    user_mode = !user_mode;
    if(user_mode)
    {
        ui->solveButton->setText("Check Solution");
        ui->clearButton->setText("Restart Puzzle");
    }
    else
    {
        ui->solveButton->setText("Solve");
        ui->clearButton->setText("Clear");
    }

}

/**
 * @brief MainWindow::tableEdit
 * @param row
 * @param column
 * This method is responsible for handling when a cell on the table is changed.
 */
void MainWindow::tableEdit(int row, int column)
{
    if(!user_mode)
    {
        try
        {
            int test_int = ui->tableWidget->item(row,column)->data(0).toInt();

            if(test_int > 0 && test_int <= 9)
            {
                if(solver.checkBox(row,column,test_int)&&
                        solver.checkHorizontal(row,column,test_int)&&
                        solver.checkVertical(row,column,test_int))
                {
                    solver.setInput(row,column,test_int);
                    ui->label->setText(QString(""));
                }
                else
                {
                    QString t = "";
                    ui->tableWidget->item(row,column)->setData(Qt::DisplayRole,t);
                    if(test_int != 0)
                       ui->label->setText(QString("Invalid Entry. Broken Puzzle."));
                }
            }
            else
            {
                QString t = "";
                ui->tableWidget->item(row,column)->setData(Qt::DisplayRole,t);
                if(test_int != 0)
                   ui->label->setText(QString("Invalid Entry. Enter an integer value 1-9."));
            }
        }
        catch(int e){}
    }
    else
    {
        //check if trying to overwrite given value
        if(solver.solution[row][column]==0)
        {
            int test_int = ui->tableWidget->item(row,column)->data(0).toInt();
            solver.setInput(row,column,test_int);
            //ui->
            QFont font = ui->tableWidget->item(row,column)->font();
            font.setBold(false);
            ui->tableWidget->item(row,column)->setFont(font);
            ui->label->setText(QString(""));
        }
        else
        {
             ui->label->setText(QString("Stop trying to overwrite a starting value, Dinghus"));
             QString t = "";
             t.setNum(solver.solution[row][column]);
             ui->tableWidget->item(row,column)->setData(Qt::DisplayRole,t);

        }
    }
}
