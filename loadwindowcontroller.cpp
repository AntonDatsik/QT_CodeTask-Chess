#include "loadwindowcontroller.h"

LoadWindowController::LoadWindowController(QWidget* parent)
{
    this->parent = parent;
    board = new Board(parent, 50, 30);
}

LoadWindowController::~LoadWindowController()
{
    delete board;
}

void LoadWindowController::loadGame(QString fileName)
{
    list.clear();
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        board->loadFromFile(stream);
        while (!stream.atEnd())
        {
            list.push_back(stream.readLine());
        }
    }
    file.close();
    index = list.count();
}

void LoadWindowController::prevStep()
{
    if (index <= 0) return;
    replaceFiguresPrev(--index);
}

void LoadWindowController::nextStep()
{
    if (index > (list.count() - 1))
        return;
    replaceFiguresNext(index);
    index++;
}

void LoadWindowController::replaceFiguresPrev(int index)
{
    QString step = list.at(index); //variable step has format '3,7 (3-1) : 3,5 (6-0)'
    int i_from = step.at(0).digitValue() - 1;
    int j_from = step.at(2).digitValue() - 1;
    int figure_from = step.at(5).digitValue();
    int color_from = step.at(7).digitValue();

    int i_to = step.at(12).digitValue() - 1;
    int j_to = step.at(14).digitValue() - 1;
    int figure_to = step.at(17).digitValue();
    int color_to = step.at(19).digitValue();

    board->squares[i_to][j_to].setFigure(static_cast<Figure>(figure_to), static_cast<Color>(color_to));
    board->squares[i_to][j_to].update();


    board->squares[i_from][j_from].setFigure(static_cast<Figure>(figure_from), static_cast<Color>(color_from));
    board->squares[i_from][j_from].update();
}

void LoadWindowController::replaceFiguresNext(int index)
{
    QString step = list.at(index); //varibale step has format '3,7 (3-1) : 3,5 (6-0)'
    int i_from = step.at(0).digitValue() - 1;
    int j_from = step.at(2).digitValue() - 1;
    int figure_from = step.at(5).digitValue();
    int color_from = step.at(7).digitValue();

    int i_to = step.at(12).digitValue() - 1;
    int j_to = step.at(14).digitValue() - 1;

    board->squares[i_to][j_to].setFigure(static_cast<Figure>(figure_from), static_cast<Color>(color_from));
    board->squares[i_to][j_to].update();


    board->squares[i_from][j_from].setFigure(NOTHING, static_cast<Color>(color_from));
    board->squares[i_from][j_from].update();
}


