#ifndef LOADWINDOWCONTROLLER_H
#define LOADWINDOWCONTROLLER_H
#include "board.h"
#include <QFile>
#include "step.h"

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
    void reloadBoard();
};

#endif // LOADWINDOWCONTROLLER_H
