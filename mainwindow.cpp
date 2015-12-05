#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "playwindow.h"
#include <QPushButton>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        ));

    board = new Board(this, 50, 30);

    QPushButton* startButton = ui->ButtonStart;
    QPushButton* loadButton = ui->ButtonLoad;
    connect(startButton, SIGNAL(clicked(bool)), this, SLOT(handleClickStartButton()));
    connect(loadButton, SIGNAL(clicked(bool)), this, SLOT(handleClickLoadButton()));
}

MainWindow::~MainWindow()
{
    delete board;
    delete ui;
}

void MainWindow::handleClickStartButton()
{
    playWindow = new PlayWindow(this);
    playWindow->startNewGame();
    playWindow->show();
    this->hide();
}

void MainWindow::handleClickLoadButton()
{
    loadedGameWindow = new LoadedGameWindow(this);
    if (loadedGameWindow->initLoadingFile())
    {
        loadedGameWindow->show();
        this->hide();
    }
    else
        delete loadedGameWindow;
}

