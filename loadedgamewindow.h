#ifndef LOADEDGAMEWINDOW_H
#define LOADEDGAMEWINDOW_H

#include <QMainWindow>
#include "loadwindowcontroller.h"

namespace Ui {
class LoadedGameWindow;
}

class LoadedGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoadedGameWindow(QWidget *parent = 0);
    ~LoadedGameWindow();
    bool initLoadingFile();
private slots:
    void handleClickButtonNext();
    void handleCickButtonPrev();
    void handleClickButtonNewGame();
    void handleClickButtonLoadGame();

private:

    Ui::LoadedGameWindow *ui;
    QWidget* parent;
    LoadWindowController* controller;
};

#endif // LOADEDGAMEWINDOW_H
