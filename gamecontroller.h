#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "board.h"
#include "figures.h"
#include <QListWidget>

class GameController
{
public:
    GameController();
    ~GameController();
    bool tryMove(BoardSquare* squareFrom, BoardSquare* squareTo);
    void startNewGame(QWidget* parent, QListWidget* list, int x_sshift, int y_shift);
    Color getStepNow() {return stepNow;}
    void saveGameToFile();
    void stopGame();
private:
    QWidget* parentWindow;
    Board* board;
    Color stepNow; // who can do next step(WHITE - Player_1, BLACK - Player_2)
    void move(BoardSquare* squareFrom, BoardSquare* squareTo);
    QListWidget* historyList;
    class ChessValidator
    {
    public:
        bool validateKing(BoardSquare* squareFrom, BoardSquare* squareTo, Board* board);
        bool validateRook(BoardSquare* squareFrom, BoardSquare* squareTo, Board* board);
        bool validateBishop(BoardSquare* squareFrom, BoardSquare* squareTo, Board* board);
        bool validateKnight(BoardSquare* squareFrom, BoardSquare* squareTo, Board* board);
        bool validatePawn(BoardSquare* squareFrom, BoardSquare* squareTo, Board* board);
        bool validateQueen(BoardSquare* squareFrom, BoardSquare* squareTo, Board* board);
    };
    ChessValidator* validator;

};

#endif // GAMECONTROLLER_H
