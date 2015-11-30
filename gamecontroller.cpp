#include "gamecontroller.h"
#include "boardsquare.h"
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

GameController::GameController()
{
}

GameController::~GameController()
{
    delete board;
    delete validator;
}

void GameController::startNewGame(QWidget* parent, QListWidget* list, int x_shift, int y_shift)
{
    historyList = list;
    parentWindow = parent;
    board = new Board(parent, x_shift, y_shift);
    board->initStartPosition();
    validator = new ChessValidator();
    stepNow = BLACK;
}

void GameController::saveGameToFile()
{
    QString fileName = QFileDialog::getSaveFileName(parentWindow, "Save Game", "*.txt");
    while (fileName == NULL) {
        fileName = QFileDialog::getSaveFileName(parentWindow, "Save Game", "*.txt");
    }
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        board->saveToFile(stream);
        for (int i = 0; i < historyList->count(); ++i)
        {
            stream << historyList->item(i)->text() << "\n";
        }
    }
    file.close();
}

bool GameController::tryMove(BoardSquare* squareFrom, BoardSquare* squareTo)
{
    if (squareTo->getFigure() != NOTHING)
        if (squareFrom->getFigureColor() == squareTo->getFigureColor()) return false;

    bool isValidated = false;

    switch(squareFrom->getFigure())
    {
        case BISHOP: {
            isValidated = validator->validateBishop(squareFrom, squareTo, board);
            break;
        }
        case KING: {
            isValidated = validator->validateKing(squareFrom, squareTo, board);
            break;
        }
        case KNIGHT: { isValidated = validator->validateKnight(squareFrom, squareTo, board); break; }
        case PAWN: { isValidated = validator->validatePawn(squareFrom, squareTo, board); break; }
        case QUEEN: { isValidated = validator->validateQueen(squareFrom, squareTo, board); break; }
        case ROOK: { isValidated = validator->validateRook(squareFrom, squareTo, board); break; }
        case NOTHING: { return false; }
    }
    if (isValidated)
        move(squareFrom, squareTo);

    return isValidated;
}




void GameController::move(BoardSquare *squareFrom, BoardSquare *squareTo)
{
    QString str = QString("%1,%2 (%3-%4) : %5,%6 (%7-%8)").arg( QString::number(squareFrom->pos_x + 1), QString::number(squareFrom->pos_y + 1)
    ,QString::number(static_cast<int>(squareFrom->getFigure())), QString::number(static_cast<int>(squareFrom->getFigureColor())),
                                                                QString::number(squareTo->pos_x + 1)
    , QString::number(squareTo->pos_y + 1), QString::number(static_cast<int>(squareTo->getFigure())),
                                                                QString::number(static_cast<int>(squareTo->getFigureColor())));
    historyList->addItem(str);

    Figure figure = squareFrom->getFigure();
    Color color = squareFrom->getFigureColor();
    squareFrom->setFigure(NOTHING, BLACK);
    squareFrom->update();
    squareTo->setFigure(figure, color);
    squareTo->update();

    if (stepNow == WHITE) stepNow = BLACK;
    else
        stepNow = WHITE;


}

bool GameController::ChessValidator::validateBishop(BoardSquare *squareFrom, BoardSquare *squareTo, Board *board)
{
    int xFrom = squareFrom->pos_x;
    int yFrom = squareFrom->pos_y;

    int xTo = squareTo->pos_x;
    int yTo = squareTo->pos_y;

    if (xTo > xFrom)
    {
        if (yTo > yFrom)
        {
            while (!((++xFrom == xTo)  & (++yFrom == yTo)))
            {
                if (board->squares[xFrom][yFrom].getFigure() != NOTHING) return false;

            }
            return (xFrom == xTo && yFrom == yTo);
        }
        else
        if (yTo < yFrom)
        {
            while (!((++xFrom == xTo)  & (--yFrom == yTo)))
            {
                if (board->squares[xFrom][yFrom].getFigure() != NOTHING) return false;

            }
            return (xFrom == xTo && yFrom == yTo);
        }
    }
    else
    {
        if (yTo > yFrom)
        {
            while (!((--xFrom == xTo)  & (++yFrom == yTo)))
            {
                if (board->squares[xFrom][yFrom].getFigure() != NOTHING) return false;

            }
            return (xFrom == xTo && yFrom == yTo);
        }
        else
        if (yTo < yFrom)
        {
            while (!((--xFrom == xTo)  & (--yFrom == yTo)))
            {
                if (board->squares[xFrom][yFrom].getFigure() != NOTHING) return false;

            }
            return (xFrom == xTo && yFrom == yTo);
        }
    }

    return false;

}

bool GameController::ChessValidator::validatePawn(BoardSquare *squareFrom, BoardSquare *squareTo, Board *board)
{
    int xFrom = squareFrom->pos_x;
    int yFrom = squareFrom->pos_y;

    int xTo = squareTo->pos_x;
    int yTo = squareTo->pos_y;

    if (squareFrom->getFigureColor() == BLACK)
        return ((xFrom == xTo && ((yTo + 2 == yFrom && yFrom == 6) || yTo + 1 == yFrom))
            || (yTo + 1 == yFrom && (xTo + 1 == xFrom || xTo-1 == xFrom) && (squareTo->getFigure() != NOTHING && squareTo->getFigureColor() != squareFrom->getFigureColor())));
    else
        return ((xFrom == xTo && ((yTo - 2 == yFrom && yFrom == 1) || yTo - 1 == yFrom))
            || (yTo - 1 == yFrom && (xTo + 1 == xFrom || xTo-1 == xFrom) && (squareTo->getFigure() != NOTHING && squareTo->getFigureColor() != squareFrom->getFigureColor())));
}

bool GameController::ChessValidator::validateKing(BoardSquare *squareFrom, BoardSquare *squareTo, Board *board)
{
    int xFrom = squareFrom->pos_x;
    int yFrom = squareFrom->pos_y;

    int xTo = squareTo->pos_x;
    int yTo = squareTo->pos_y;

    if (xFrom == xTo || yFrom == yTo)
    {
        if (squareTo->getFigure() != NOTHING) return false;
    }

    if (xFrom + 1 == xTo || xFrom -1 == xTo || xFrom == xTo)
        return yFrom - 1 == yTo || yFrom + 1 == yTo || yFrom == yTo;

    return false;
}

bool GameController::ChessValidator::validateQueen(BoardSquare *squareFrom, BoardSquare *squareTo, Board *board)
{
    return (validateRook(squareFrom, squareTo, board) || validateBishop(squareFrom, squareTo, board));
}

bool GameController::ChessValidator::validateRook(BoardSquare *squareFrom, BoardSquare *squareTo, Board *board)
{
    int xFrom = squareFrom->pos_x;
    int yFrom = squareFrom->pos_y;

    int xTo = squareTo->pos_x;
    int yTo = squareTo->pos_y;

    if (xFrom == xTo)
    {
        if (yTo > yFrom)
        {
            while (++yFrom != yTo)
            {
                if (board->squares[xFrom][yFrom].getFigure() != NOTHING) return false;

            }
            return (yFrom == yTo);
        }
        else
        if (yTo < yFrom)
        {
            while (--yFrom != yTo)
            {
                if (board->squares[xFrom][yFrom].getFigure() != NOTHING) return false;

            }
            return (yFrom == yTo);
        }
    }
    if (yTo == yFrom)
    {
        if (xTo > xFrom)
        {
            while (++xFrom != xTo)
            {
                if (board->squares[xFrom][yFrom].getFigure() != NOTHING) return false;

            }
            return (xFrom == xTo);
        }
        else
        if (xTo < xFrom)
        {
            while (--xFrom != xTo)
            {
                if (board->squares[xFrom][yFrom].getFigure() != NOTHING) return false;

            }
            return (xFrom == xTo);
        }
    }

    return false;
}

bool GameController::ChessValidator::validateKnight(BoardSquare *squareFrom, BoardSquare *squareTo, Board *board)
{
    int xFrom = squareFrom->pos_x;
    int yFrom = squareFrom->pos_y;

    int xTo = squareTo->pos_x;
    int yTo = squareTo->pos_y;

    return ((xTo - 2 == xFrom && yTo - 1 == yFrom) || (xTo - 2 == xFrom && yTo + 1 == yFrom)
        || (xTo - 1 == xFrom && yTo - 2 == yFrom) || (xTo - 1 == xFrom && yTo + 2 == yFrom)
            || (xTo + 2 == xFrom && yTo - 1 == yFrom) || (xTo + 2 == xFrom && yTo + 1 == yFrom)
            || (xTo + 1 == xFrom && yTo - 2 == yFrom) || (xTo + 1 == xFrom && yTo + 2 == yFrom));
}
