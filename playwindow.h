#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>
#include <QListWidget>

#include "gamecontroller.h"

namespace Ui {
class PlayWindow;
}

class PlayWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayWindow(QWidget *parent = 0);
    ~PlayWindow();
    void startNewGame();
public slots:
    void handleClickSaveGameToFile();
    void handleClickStopGame();
    QListWidget* getListWidget() const { return historyList; }
private:
    Ui::PlayWindow *ui;
    QListWidget* historyList;
    QWidget* parent;
};

#endif // PLAYWINDOW_H
