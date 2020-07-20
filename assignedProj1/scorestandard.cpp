#include "scorestandard.h"
#include <stdlib.h>

ScoreStandard::ScoreStandard()
{
    std100 = new QList<int>();
    *std100 << 59 << 62 << 66 << 69
                 << 72 << 76 << 79 << 84
                 << 89 << 94 << 100;
    stdLevel = new QList<QString>();
    *stdLevel << "F" << "D" << "D+" << "C-"
                   << "C" << "C+" << "B-" << "B"
                   << "B+" << "A-" << "A/A+";
    std4 = new QList<qreal>();
    *std4 << 0 << 1.0 << 1.3 << 1.7
               << 2.0 << 2.3 << 2.7 << 3.0
               << 3.3 << 3.6 << 4.0;
    length = std100->length();
}

ScoreStandard::ScoreStandard(QList<int> s100, QList<QString> sLevel, QList<qreal> s4)
{
    std100 = new QList<int>(s100);
    stdLevel = new QList<QString>(sLevel);
    std4 = new QList<qreal>(s4);
    assert(areMatch() && is100Sequential() && is4Sequential());
    length = std100->length();
}

ScoreStandard::~ScoreStandard()
{
    delete std100;
    delete stdLevel;
    delete std4;
}

bool ScoreStandard::areMatch()
{
    if((std100->length() != stdLevel->length()) ||
       (stdLevel->length() != std4->length()) ||
       (std4->length() != std100->length()))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool ScoreStandard::is100Sequential()
{
    for(int i = 1; i < length; i++)
    {
        if(std100->at(i - 1) >= std100->at(i))
        {
            return false;
        }
    }
    return true;
}

bool ScoreStandard::is4Sequential()
{
    for(int i = 1; i < length; i++)
    {
        if(std4->at(i - 1) >= std4->at(i))
        {
            return false;
        }
    }
    return true;
}

int ScoreStandard::std100At(int i) const
{
    return std100->at(i);
}

qreal ScoreStandard::std4At(int i) const
{
    return std4->at(i);
}

QString ScoreStandard::stdLevelAt(int i) const
{
    return stdLevel->at(i);
}

int ScoreStandard::getLength() const
{
    return length;
}
