#ifndef LOADWINDOWCONTROLLER_H
#define LOADWINDOWCONTROLLER_H
#include "board.h"
#include <QFile>

class LoadWindowController
{
public:
    LoadWindowController(QWidget* parent);
    ~LoadWindowController();
    void loadGame(QString fileName);
    void nextStep();
    void prevStep();
private:
    QWidget* parent;
    Board* board;
    QList<QString> list;
    int index;
    void replaceFiguresPrev(int index);
    void replaceFiguresNext(int index);
};

#endif // LOADWINDOWCONTROLLER_H
