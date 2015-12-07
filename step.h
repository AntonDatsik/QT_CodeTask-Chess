#ifndef STEP
#define STEP


struct Step
{
    int iFrom;
    int jFrom;
    int figureFrom;
    int colorFrom;

    int iTo;
    int jTo;
    int figureTo;
    int colorTo;

public:
    Step()
    {}

    Step(int iFrom, int jFrom, int figureFrom, int ColorFrom, int iTo, int jTo, int figureTo, int colorTo)
    {
        this->iFrom = iFrom;
        this->jFrom = jFrom;
        this->figureFrom = figureFrom;
        this->colorFrom = ColorFrom;
        this->iTo = iTo;
        this->jTo = jTo;
        this->figureTo = figureTo;
        this->colorTo = colorTo;
    }
};


#endif // STEP

