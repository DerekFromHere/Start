#ifndef SCORE_H
#define SCORE_H

#include "scorestandard.h"

//the number of strings in the list returned by func getAll()
const int scoreInfoCount = 3;

class Score
{
public:
    Score();
    Score(int s100, QString sLevel, qreal s4, ScoreStandard sStd = ScoreStandard());
    Score(const Score &other);

    //converting inside the object by the scoreStd,
    //return the result of conversion
    QString s100ToSLevel();
    qreal s100ToS4();
    int sLevelToS100();
    qreal sLevelToS4();
    int s4ToS100();
    QString s4ToSLevel();

    //return the scores
    int getScore100() const;
    QString getScoreLevel() const;
    qreal getScore4() const;
    ScoreStandard getScoreStd() const;

    //return all scores
    QStringList getAll() const;

    //set score standard
    void setScoreStd(ScoreStandard sStd);

    void setScore100(int s100);

    void setScoreLevel(QString sLevel);

    void setScore4(qreal s4);

    bool operator ==(const Score &other) const;

protected:
    int score100;

    QString scoreLevel;

    qreal score4;

    ScoreStandard scoreStd;


};

#endif // SCORE_H
