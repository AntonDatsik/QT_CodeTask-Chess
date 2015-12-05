#ifndef BOARD_H
#define BOARD_H

#include "boardsquare.h"
#include <QTextStream>


class Board
{

public:
    Board(QWidget *parent, int, int);
    QLabel leftBorders[8];
    QLabel topBorders[8];
    BoardSquare squares[8][8];
    void initStartPosition();
    bool loadFromFile(QTextStream& stream);
    void saveToFile(QTextStream& stream);
//    friend void operator>> (std::ifstream& ifile, Board& board);
//    friend void operator << (std::ofstream& ifile, Board& board);
private:
    QPixmap figures[12];
    QWidget* parent;
    int x_shift;
    int y_shift;
};

#endif // BOARD_H
