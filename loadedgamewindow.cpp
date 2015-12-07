#include "loadedgamewindow.h"
#include "ui_loadedgamewindow.h"
#include <QDesktopWidget>
#include <QFileDialog>
#include <QMessageBox>
#include "mainwindow.h"

LoadedGameWindow::LoadedGameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoadedGameWindow)
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

    QPushButton* buttonNext = ui->pushButtonNext;
    QPushButton* buttonPrev = ui->pushButtonPrev;

    QPushButton* buttonNewGame = ui->pushButtonStartNewGame;
    QPushButton* buttonLoadGame = ui->pushButtonLoadGame;

    connect(buttonNext, SIGNAL(pressed()), this, SLOT(handleClickButtonNext()));
    connect(buttonPrev, SIGNAL(pressed()), this, SLOT(handleCickButtonPrev()));
    connect(buttonNewGame, SIGNAL(pressed()), this, SLOT(handleClickButtonNewGame()));
    connect(buttonLoadGame, SIGNAL(pressed()), this, SLOT(handleClickButtonLoadGame()));

}

LoadedGameWindow::~LoadedGameWindow()
{
    delete ui;
    delete controller;
}

void LoadedGameWindow::handleCickButtonPrev()
{
    controller->prevStep();
}

void LoadedGameWindow::handleClickButtonNext()
{
    controller->nextStep();
}

void LoadedGameWindow::handleClickButtonLoadGame()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Saved Game", "*.txt");

    if (!controller->loadGame(fileName))
    {
        QMessageBox msBox;
        msBox.setText("Invalid file for loading");
        msBox.exec();
        parent->show();
        this->close();
    }
}

void LoadedGameWindow::handleClickButtonNewGame()
{
    MainWindow* mainWindow = dynamic_cast<MainWindow*>(parent);
    mainWindow->show();
    mainWindow->playWindow = new PlayWindow(parent);
    mainWindow->playWindow->startNewGame();
    mainWindow->playWindow->show();
    this->close();
    mainWindow->hide();
}

bool LoadedGameWindow::initLoadingFile()
{
    controller = new LoadWindowController(this);

    QString fileName = QFileDialog::getOpenFileName(parent, "Open Saved Game", "*.txt");

    return controller->loadGame(fileName);
}
