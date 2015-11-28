#include "boardsquare.h"
#include "playwindow.h"
#include <QTextStream>

extern GameController* controller;

BoardSquare* choosed = NULL;

BoardSquare::BoardSquare()
{
    figure = NOTHING;
}


void BoardSquare::mousePressEvent(QMouseEvent *ev)
{
    if (controller == NULL) return;
    if (this->figure != NOTHING && this->getFigureColor() == controller->getStepNow())
    {
        if (this == choosed)
        {
            this->setStyleSheet(styleSheet);
            choosed = NULL;
            return;
        }
        if (choosed == NULL)
        {
            this->setStyleSheet("QLabel {background-color: red;}:hover{background-color: rgb(170,85,127);}");
            choosed = this;
        }
        else
        {
            choosed->setStyleSheet(choosed->getStyleSheet());
            controller->tryMove(choosed, this);
            choosed = NULL;
        }
    }
    else
    {
        if(choosed != NULL)
        {
            choosed->setStyleSheet(choosed->getStyleSheet());
            controller->tryMove(choosed, this);
            choosed = NULL;
        }
    }
}

void BoardSquare::setColor(const QString &styleSheet)
{
    this->styleSheet = styleSheet;
    this->setStyleSheet(styleSheet);
}

void BoardSquare::setFigure(Figure figure, Color color)
{
    this->figure = figure;
    this->figureColor = color;
}

void BoardSquare::update()
{
    if (this->figure == NOTHING)
    {
        this->clear();
        return;
    }

    if (this->figureColor == BLACK)
    switch (this->figure)
    {
        case PAWN: { this->setPixmap(QPixmap(":/images/resources/pawn_black.svg")); break; }
        case BISHOP: { this->setPixmap(QPixmap(":/images/resources/bishop_black.svg")); break;}
        case KING: { this->setPixmap(QPixmap(":/images/resources/king_black.svg")); break;}
        case KNIGHT: { this->setPixmap(QPixmap(":/images/resources/knight_black.svg")); break;}
        case QUEEN: { this->setPixmap(QPixmap(":/images/resources/queen_black.svg")); break;}
        case ROOK: { this->setPixmap(QPixmap(":/images/resources/rook_black.svg")); break;}
        default : break;
    }
    else
        switch (this->figure)
        {
            case PAWN: { this->setPixmap(QPixmap(":/images/resources/pawn_white.svg")); break; }
            case BISHOP: { this->setPixmap(QPixmap(":/images/resources/bishop_white.svg")); break;}
            case KING: { this->setPixmap(QPixmap(":/images/resources/king_white.svg")); break;}
            case KNIGHT: { this->setPixmap(QPixmap(":/images/resources/knight_white.svg")); break;}
            case QUEEN: { this->setPixmap(QPixmap(":/images/resources/queen_white.svg")); break;}
            case ROOK: { this->setPixmap(QPixmap(":/images/resources/rook_white.svg")); break;}
            default : break;
        }
}

void BoardSquare::setPosition(int x, int y)
{
    pos_x = x;
    pos_y = y;
}

Figure BoardSquare::getFigure()
{
    return figure;
}

Color BoardSquare::getFigureColor()
{
    return figureColor;
}
