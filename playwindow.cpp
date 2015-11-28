#include "playwindow.h"
#include "ui_playwindow.h"
#include <QDesktopWidget>
#include "mainwindow.h"

GameController* controller;

PlayWindow::PlayWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayWindow)
{
    ui->setupUi(this);
    this->parent = parent;
    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        ));

    this->setAttribute(Qt::WA_DeleteOnClose, true);

    QPushButton* saveButton = ui->pushButtonSave;
    QPushButton* stopButton = ui->pushButtonStop;
    historyList = ui->listWidget;

    controller = new GameController();
    connect(saveButton, SIGNAL(pressed()), this, SLOT(handleClickSaveGameToFile()));
    connect(stopButton, SIGNAL(pressed()), this, SLOT(handleClickStopGame()));
    //connect(controller, SIGNAL(move(BoardSquare *squareFrom, BoardSquare *squareTo)), this, SLOT(addToHistoryList(BoardSquare *squareFrom, BoardSquare *squareTo))); //add record to log
}

PlayWindow::~PlayWindow()
{
    delete ui;
    delete controller;
}

void PlayWindow::handleClickSaveGameToFile()
{
    controller->saveGameToFile();
}

void PlayWindow::handleClickStopGame()
{
    parent->show();
    this->close();
}

void PlayWindow::startNewGame()
{
    controller->startNewGame(this, historyList, 50, 30);
}

