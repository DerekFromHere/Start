#ifndef SCORESTANDARD_H
#define SCORESTANDARD_H

#include <QList>

class ScoreStandard
{
public:
    ScoreStandard();
    ScoreStandard(QList<int> s100, QList<QString> sLevel, QList<qreal> s4);
    ~ScoreStandard();

    //check if 3 lists are equal in length
    bool areMatch();

    //check if numbers in std100 are from small to big
    bool is100Sequential();

    bool is4Sequential();

    int std100At(int i) const;

    QString stdLevelAt(int i) const;

    qreal std4At(int i) const;

    int getLength() const;

private:
    //store the right boundary of each interval(the default lowest score is 0)
    QList<int> *std100;

    //store the level string of each interval
    QList<QString> *stdLevel;

    QList<qreal> *std4;

    int length;
};

#endif // SCORESTANDARD_H
