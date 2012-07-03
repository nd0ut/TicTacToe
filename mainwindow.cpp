#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gb = new GameBoard;
    updateUi();

    connect(gb, SIGNAL(gameIsFinished(PLAYER)), this, SLOT(onGameFinished(PLAYER)));
    connect(gb,SIGNAL(cellChanged()), this, SLOT(onCellChanged()));
}

MainWindow::~MainWindow()
{
    delete gb;
    delete ui;
}

QString MainWindow::playerEnumToString(const PLAYER &player)
{
    if(player == NOP)
        return "-";

    if(player == NOUGHT)
        return "O";

    if(player == CROSS)
        return "X";
}

void MainWindow::updateUi()
{
    ui->pushButton->setText(playerEnumToString(gb->getCellPlayer(0,0)));
    ui->pushButton_2->setText(playerEnumToString(gb->getCellPlayer(0,1)));
    ui->pushButton_3->setText(playerEnumToString(gb->getCellPlayer(0,2)));
    ui->pushButton_4->setText(playerEnumToString(gb->getCellPlayer(1,0)));
    ui->pushButton_5->setText(playerEnumToString(gb->getCellPlayer(1,1)));
    ui->pushButton_6->setText(playerEnumToString(gb->getCellPlayer(1,2)));
    ui->pushButton_7->setText(playerEnumToString(gb->getCellPlayer(2,0)));
    ui->pushButton_8->setText(playerEnumToString(gb->getCellPlayer(2,1)));
    ui->pushButton_9->setText(playerEnumToString(gb->getCellPlayer(2,2)));

    ui->LNextPlayer->setText(playerEnumToString(gb->getNextPlayer()));
}

void MainWindow::on_pushButton_clicked()
{
    gb->makeNextMove(0,0);
    updateUi();
}

void MainWindow::on_pushButton_2_clicked()
{
    gb->makeNextMove(0,1);
    updateUi();
}

void MainWindow::on_pushButton_3_clicked()
{
    gb->makeNextMove(0,2);
    updateUi();
}

void MainWindow::on_pushButton_4_clicked()
{
    gb->makeNextMove(1,0);
    updateUi();
}

void MainWindow::on_pushButton_5_clicked()
{
    gb->makeNextMove(1,1);
    updateUi();
}

void MainWindow::on_pushButton_6_clicked()
{
    gb->makeNextMove(1,2);
    updateUi();
}

void MainWindow::on_pushButton_7_clicked()
{
    gb->makeNextMove(2,0);
    updateUi();
}

void MainWindow::on_pushButton_8_clicked()
{
    gb->makeNextMove(2,1);
    updateUi();
}

void MainWindow::on_pushButton_9_clicked()
{
    gb->makeNextMove(2,2);
    updateUi();
}

void MainWindow::onGameFinished(PLAYER winner)
{
    QString text;

    if(winner != NOP)
        text = "Player " + playerEnumToString(winner) + " has won the game! \nRestart game?";
    else
        text = "Draw! Nobody won the game. \nRestart game?";

    QMessageBox pmbx("Game over!",
                        text,
                        QMessageBox::Information,
                        QMessageBox::Yes,
                        QMessageBox::No,
                        QMessageBox::NoButton);

    int pressed = pmbx.exec();

    if(pressed == 16384) {
        gb->resetState();
        updateUi();
    }

}

void MainWindow::onCellChanged()
{
    updateUi();
}

void MainWindow::on_pushButton_newGame_clicked()
{
    gb->resetState();
    updateUi();
}
