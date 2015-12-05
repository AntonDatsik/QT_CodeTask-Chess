#include "loadwindowcontroller.h"
#include <QMessageBox>

LoadWindowController::LoadWindowController(QWidget* parent)
{
    this->parent = parent;
    board = new Board(parent, 50, 30);
}

LoadWindowController::~LoadWindowController()
{
    delete board;
}

bool LoadWindowController::loadGame(QString fileName)
{
    if (fileName == NULL) return false;
    list.clear();
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        while (!stream.atEnd())
        {
            QString string = stream.readLine();
            if (!validateStep(string))
            {
                file.close();
                return false;
            }
        }
    }
    else
        return false;

    file.close();

    board->initStartPosition();

    index = 0;

    return true;
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

bool LoadWindowController::replaceFiguresPrev(int index)
{
    Step step = list.at(index);

    board->squares[step.iTo][step.jTo].setFigure(static_cast<Figure>(step.figureTo), static_cast<Color>(step.colorTo));
    board->squares[step.iTo][step.jTo].update();


    board->squares[step.iFrom][step.jFrom].setFigure(static_cast<Figure>(step.figureFrom), static_cast<Color>(step.colorFrom));
    board->squares[step.iFrom][step.jFrom].update();

    return true;
}

bool LoadWindowController::replaceFiguresNext(int index)
{
    Step step = list.at(index);

    board->squares[step.iTo][step.jTo].setFigure(static_cast<Figure>(step.figureFrom), static_cast<Color>(step.colorFrom));
    board->squares[step.iTo][step.jTo].update();

    board->squares[step.iFrom][step.jFrom].setFigure(NOTHING, static_cast<Color>(step.colorFrom));
    board->squares[step.iFrom][step.jFrom].update();

    return true;
}

bool LoadWindowController::validateStep(QString string)
{
    int iFrom = string.at(0).digitValue() - 1;
    int jFrom = string.at(2).digitValue() - 1;
    int figureFrom = string.at(5).digitValue();
    int colorFrom = string.at(7).digitValue();

    int iTo = string.at(12).digitValue() - 1;
    int jTo = string.at(14).digitValue() - 1;
    int figureTo = string.at(17).digitValue();
    int colorTo = string.at(19).digitValue();

    bool isValidCoordFrom = validateCoord(iFrom, jFrom);
    bool isValidCoordTo = validateCoord(iTo, jTo);

    if (isValidCoordFrom && isValidCoordTo)
    {
        bool result = (validateFigure(figureFrom, colorFrom)&&
                validateFigure(figureTo, colorTo));
        if (result)
        {
            Step step(iFrom, jFrom, figureFrom, colorFrom, iTo, jTo, figureTo, colorTo);
            list.push_back(step);
        }
        return result;
    }
    else
        return false;
}

bool LoadWindowController::validateFigure(int figureNum, int figureColor)
{
    if (!(figureNum < KING || figureNum > NOTHING))
    {
        if (figureNum != NOTHING)
        {
            return validateColor(figureColor);
        }
        else
            return true;
    }
    else
        return false;
}

bool LoadWindowController::validateColor(int figureColor)
{
    return !(figureColor < 0 || figureColor > 1);
}

bool LoadWindowController::validateCoord(int i, int j)
{
    return (i >= 0 && i < 8 && j >=0 && j <8);
}


