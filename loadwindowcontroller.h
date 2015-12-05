#ifndef LOADWINDOWCONTROLLER_H
#define LOADWINDOWCONTROLLER_H
#include "board.h"
#include <QFile>

struct Step
{
    char iFrom;
    char jFrom;
    char figureFrom;
    char colorFrom;

    char iTo;
    char jTo;
    char figureTo;
    char colorTo;

public:
    Step(char iFrom, char jFrom, char figureFrom, char ColorFrom, char iTo, char jTo, char figureTo, char colorTo)
    {
        this->iFrom = iFrom;
        this->jFrom = jFrom;
        this->figureFrom = figureFrom;
        this->colorFrom = ColorFrom;
        this->iTo = iTo;
        this->jTo = jTo;
        this->figureTo = figureTo;
        this->colorTo = colorTo;
    }
};


class LoadWindowController
{
public:
    LoadWindowController(QWidget* parent);
    ~LoadWindowController();
    bool loadGame(QString fileName);
    void nextStep();
    void prevStep();
private:
    QWidget* parent;
    Board* board;
    QList<Step> list;
    int index;
    bool replaceFiguresPrev(int index);
    bool replaceFiguresNext(int index);
    bool validateListOfSteps();
    bool validateStep(QString string);
    bool validateFigure(int figureNum, int figureColor);
    bool validateColor(int figureColor);
    bool validateCoord(int i, int j);
};

#endif // LOADWINDOWCONTROLLER_H
