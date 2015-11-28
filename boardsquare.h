#ifndef BOARDSQUARE_H
#define BOARDSQUARE_H

#include <QLabel>
#include <QColor>
#include "figures.h"
#include <QFile>


class BoardSquare : public QLabel
{
public:
    BoardSquare();
    void mousePressEvent(QMouseEvent *ev);
    void setColor(const QString &styleSheet);
    void setFigure(Figure figure, Color color);
    void update();
    Figure getFigure();
    Color getFigureColor();
    void setPosition(int x, int y);
    int pos_x;
    int pos_y;
    QString getStyleSheet() { return styleSheet;}
private:

    Figure figure;
    Color  figureColor;
    QString styleSheet;

};

#endif // BOARDSQUARE_H
