#include "board.h"
#include <stdio.h>
#include <QTextStream>

#define SIZE_OF_SQUARE 65
#define SQUARE_BORDER_SIZE 5

Board::Board(QWidget *parent, int x_shift, int y_shift)
{
    this->parent = parent;
    this->x_shift = x_shift;
    this->y_shift = y_shift;
    for (int i = 0; i < 8; ++i)
    {
        leftBorders[i].setGeometry(20, y_shift + i*(SIZE_OF_SQUARE + SQUARE_BORDER_SIZE) + SQUARE_BORDER_SIZE, 30, SIZE_OF_SQUARE);
        char num[1];
        sprintf(num, "%d", 8 - i);
        leftBorders[i].setParent(parent);
        leftBorders[i].setText(num);
        leftBorders[i].setStyleSheet("QLabel {font: bold 20px;}");

        num[0] = i + 65; //code of lowercase symbol
        topBorders[i].setGeometry(x_shift + i * (SIZE_OF_SQUARE + SQUARE_BORDER_SIZE) + SIZE_OF_SQUARE/2, 0, SIZE_OF_SQUARE, 30);
        topBorders[i].setParent(parent);
        topBorders[i].setText(num);
        topBorders[i].setStyleSheet("QLabel {font: bold 20px;}");
    }

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            squares[i][j].setPosition(i, j);
            squares[i][j].setParent(parent);
            squares[i][j].setGeometry(x_shift + i*(SIZE_OF_SQUARE + SQUARE_BORDER_SIZE) + SQUARE_BORDER_SIZE, y_shift + j*(SIZE_OF_SQUARE + SQUARE_BORDER_SIZE) + SQUARE_BORDER_SIZE, SIZE_OF_SQUARE, SIZE_OF_SQUARE);
            if ((i + j) % 2 == 0)
                squares[i][j].setColor("QLabel {background-color: rgb(161, 125, 53);}:hover{background-color: green;}");
            else
                squares[i][j].setColor("QLabel {background-color: rgb(211, 211, 158);}:hover{background-color: green;}");
        }
    }
}

void Board::initStartPosition()
{


    squares[0][0].setFigure(ROOK, WHITE);
    squares[1][0].setFigure(KNIGHT, WHITE);
    squares[2][0].setFigure(BISHOP, WHITE);
    squares[3][0].setFigure(QUEEN, WHITE);
    squares[4][0].setFigure(KING, WHITE);
    squares[5][0].setFigure(BISHOP, WHITE);
    squares[6][0].setFigure(KNIGHT, WHITE);
    squares[7][0].setFigure(ROOK, WHITE);
    for (int i = 0; i < 8; ++i)
    {
        squares[i][1].setFigure(PAWN, WHITE);
    }

    squares[0][7].setFigure(ROOK, BLACK);
    squares[1][7].setFigure(KNIGHT, BLACK);
    squares[2][7].setFigure(BISHOP, BLACK);
    squares[3][7].setFigure(QUEEN, BLACK);
    squares[4][7].setFigure(KING, BLACK);
    squares[5][7].setFigure(BISHOP, BLACK);
    squares[6][7].setFigure(KNIGHT, BLACK);
    squares[7][7].setFigure(ROOK, BLACK);

    for (int i = 0; i < 8; ++i)
    {
        squares[i][6].setFigure(PAWN, BLACK);
    }

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            squares[i][j].update();
}

void Board::loadFromFile(QTextStream& stream)
{
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
        {
            QString strFigNum = stream.readLine();
            QString strCOlNum = stream.readLine();
            QString style = stream.readLine();
            squares[i][j].setStyleSheet(style);
            squares[i][j].setFigure(static_cast<Figure>(strFigNum.toInt()), static_cast<Color>(strCOlNum.toInt()));
            squares[i][j].update();
        }
}

void Board::saveToFile(QTextStream& stream)
{
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
        {
            int figureNumber = static_cast<int>(squares[i][j].getFigure());
            int colorNumber = static_cast<int>(squares[i][j].getFigureColor());
            QString style = squares[i][j].getStyleSheet();
            stream << figureNumber << '\n';
            stream << colorNumber << '\n';
            stream << style << '\n';
        }
}
