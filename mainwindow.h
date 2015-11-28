#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "playwindow.h"
#include "loadedgamewindow.h"
#include "board.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    PlayWindow* playWindow;
    LoadedGameWindow* loadedGameWindow;
private slots:
    void handleClickStartButton();
    void handleClickLoadButton();
private:
    Ui::MainWindow *ui;
    Board* board;
};

#endif // MAINWINDOW_H
