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
          QTableWidgetItem* item = new QTableWidgetItem();
          QFont font = item->font();
          font.setBold(true);
          item->setTextAlignment(Qt::AlignCenter);
          item->setFont(font);

          bool isShaded = (((int)(i/3)+(int)(j/3))+1)%2;

          if(isShaded)
              item->setBackgroundColor(QColor(225,225,225,160));
          else
               item->setBackgroundColor(QColor(225,225,225,80));
          ui->tableWidget->setItem(i,j,item);
      }
    }

    ui->label->setAlignment(Qt::AlignCenter);

    //Connect Qt Widgets/Signals to appropriate methods
    connect(ui->tableWidget, SIGNAL(cellChanged(int,int)),
                this, SLOT(tableEdit(int, int)));
    connect(ui->solveButton, SIGNAL(pressed()),
                this, SLOT(solveSudoku()));
    connect(ui->clearButton, SIGNAL(pressed()),
                this, SLOT(clearPuzzle()));
    connect(ui->modeButton, SIGNAL(pressed()),
                this, SLOT(changeMode()));
    connect(ui->loadFileButton, SIGNAL(pressed()),
                this, SLOT(loadFile()));
    connect(ui->randomButton, SIGNAL(pressed()),
                this, SLOT(generatePuzzle()));
    connect(ui->comboBox, SIGNAL(activated(int)),
                this, SLOT(changeSkin(int)));

    ui->modeButton->setCheckable(true);

    //Setup the Sudoku Solver
    solver = SudokuSolver();
    solver.reset();

    is_user_mode = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::solveSudoku()
{
    if(!is_user_mode)
    {
        //Solve Given puzzle
        QString t;
        if(solver.solve(0,0)) //This calls the solve method
        {   
            for(int i = 0; i<9; i++)
            {
              for(int j =0; j< 9; j++)
              {
                  //Set grid with solved values
                  t.setNum(solver.solution[i][j]);
                  solver.user[i][j] = solver.solution[i][j];

                  //if value was inputed at start keep bold
                  if(solver.input[i][j]==0)
                  {
                      QFont font = ui->tableWidget->item(i,j)->font();
                      font.setBold(false);
                      ui->tableWidget->item(i,j)->setFont(font);
                  }
                  ui->tableWidget->item(i,j)->setData(Qt::DisplayRole,t);
              }
            }
            ui->label->setText(QString("Sudoku Solved"));
        }
        else
        {
             ui->label->setText(QString("Unable to Solve Sudoku"));
        }

        ui->tableWidget->repaint(); //is this neccesary??
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
    if(!is_user_mode)
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
    is_user_mode = !is_user_mode;
    if(is_user_mode)
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

void MainWindow::changeSkin(int skin_id)
{
    switch(skin_id)
    {
        case 0:
            ui->label->setText(QString("Default Skin"));
            ui->tableWidget->setStyleSheet("");
            //ui->frame->setStyleSheet("font: 75 15pt "MS Shell Dlg 2";";
            ui->frame->setStyleSheet("font-size: 15px");
            break;
        case 1:
            ui->label->setText(QString("Wood Skin"));
            ui->tableWidget->setStyleSheet("border-image: url(:/Oak.jpg)");
            ui->frame->setStyleSheet("border-image: url(:/Mahogany.jpg);font-size: 15px");
            break;
        case 2:
            ui->label->setText(QString("Lolcat Skin"));
            ui->tableWidget->setStyleSheet("border-image: url(:/welcome_to_the_internet__please_follow_me_by_sharpwriter-d5buwfu (1).jpg);");
            ui->frame->setStyleSheet("border-image: url(:/NYAN.png);font-size: 15px");
            break;
        default:
            break;
    }

}

void MainWindow::loadFile()
{

}

void MainWindow::generatePuzzle()
{
    clearPuzzle();

    solver.generatePuzzle();
    QString t;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(solver.input[i][j]!=0)
            {
                t.setNum(solver.input[i][j]);
                ui->tableWidget->item(i,j)->setData(Qt::DisplayRole,t);
            }
        }
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
    if(!is_user_mode)
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
        //if(solver.solution[row][column]==0)
        if(true)
        {
            int test_int = ui->tableWidget->item(row,column)->data(0).toInt();
            //solver.setInput(row,column,test_int);
            solver.user[row][column] = test_int;
            std::cout << "INPUT: " << solver.user[row][column];
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
