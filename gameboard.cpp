#include "gameboard.h"

GameBoard::GameBoard() : QObject()
{
    board = new Cell*[3];

    for(int i = 0; i < 3; i++)
        board[i] = new Cell[3];

    resetState();
}

GameBoard::~GameBoard()
{
    for(int i = 0; i < 3; i++)
        delete[] board[i];

    delete[] board;

    nextPlayer = NOP;
    winner = NOP;
}

enum PLAYER GameBoard::getWinner()
{
    return winner;
}

enum PLAYER GameBoard::getNextPlayer()
{
    return nextPlayer;
}

PLAYER &GameBoard::getCellPlayer(int i, int j)
{
    return board[i][j].myPlayer;
}

bool GameBoard::isGameFinished()
{
    return gameFinished;
}

void GameBoard::resetState()
{
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            board[i][j].myPlayer = NOP;

    nextPlayer = CROSS;
    winner = NOP;

    gameFinished = false;
    movesCount = 0;
}

void GameBoard::makeNextMove(int i, int j)
{
    if(isGameFinished())
        return;

    if(board[i][j].myPlayer != NOP)
        return;

    //make move
    enum PLAYER currentPlayer = nextPlayer;
    nextPlayer = nextPlayer == CROSS ? NOUGHT : CROSS;

    board[i][j].myPlayer = currentPlayer;
    movesCount++;

    emit cellChanged();

    //check for win situation
    checkForFinish();
}

void GameBoard::checkForFinish()
{
    if(isGameFinished())
        return;

    enum PLAYER currentWinner = NOP;

    //check cells for winning
    for(int i = 0; i < 3; i++) {
        Cell current;

        //horizontal
        current = board[i][1];
        Cell left = board[i][0];
        Cell right = board[i][2];

        if(left == current && right == current && current.myPlayer != NOP) {
            currentWinner = current.myPlayer;
            break;
        }

        //vertical
        current = board[1][i];
        Cell top = board[0][i];
        Cell bottom = board[2][i];

        if(top == current && bottom == current && current.myPlayer != NOP) {
            currentWinner = current.myPlayer;
            break;
        }

        if(i == 2)
            break;

        //diagonal
        current = board[1][1];
        Cell leftTop = board[0][0];
        Cell leftBottom = board[2][0];
        Cell rightTop = board[0][2];
        Cell rightBottom = board[2][2];

        if( (leftTop == current && rightBottom == current && current.myPlayer != NOP) ||
            (rightTop == current && leftBottom == current && current.myPlayer != NOP) ) {
            currentWinner = current.myPlayer;
            break;
        }
    }

    //somebody won
    if(currentWinner != NOP) {
        nextPlayer = NOP;
        winner = currentWinner;

        gameFinished = true;

        emit gameIsFinished(winner);

        return;
    }

    //nobody won
    if(movesCount == 9) {
        gameFinished = true;

        emit gameIsFinished(NOP);
    }

}
