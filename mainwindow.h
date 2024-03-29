#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "gameboard.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();

    void onGameFinished(enum PLAYER winner);
    void onCellChanged();

    void on_pushButton_newGame_clicked();

private:
    QString playerEnumToString(const enum PLAYER& player);
    void updateUi();
    
private:
    Ui::MainWindow *ui;

    GameBoard *gb;
};

#endif // MAINWINDOW_H
