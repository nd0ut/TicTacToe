#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QObject>

enum PLAYER { NOP, CROSS, NOUGHT };

struct Cell {
    enum PLAYER myPlayer;

    Cell(){
        myPlayer = NOP;
    }

    bool operator==(const Cell& right) {
        if(this->myPlayer == right.myPlayer)
            return true;

        else
            return false;
    }

    void operator=(const Cell& right) {
        this->myPlayer = right.myPlayer;
    }
};

class GameBoard : public QObject
{
    Q_OBJECT
public:
    explicit GameBoard();
    ~GameBoard();

    enum PLAYER getWinner();
    enum PLAYER getNextPlayer();

    enum PLAYER& getCellPlayer(int i, int j);
    
private:
    bool isGameFinished();


signals:
    void gameIsFinished(enum PLAYER _winner);
    void cellChanged();
    
public slots:
    void resetState();
    void checkForFinish();
    void makeNextMove(int row, int col);
    
private:
    Cell **board;

    enum PLAYER nextPlayer;
    enum PLAYER winner;

    bool gameFinished;
    int movesCount;
};

#endif // GAMEBOARD_H
