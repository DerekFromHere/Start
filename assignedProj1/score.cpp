#include "score.h"
#include "scorestandard.h"

Score::Score()
{
    score100 = 0;
    s100ToSLevel();
    s100ToS4();
}

Score::Score(int s100, QString sLevel, qreal s4, ScoreStandard sStd)
{
    score100 = s100;
    //assert((sLevel == s100ToSLevel()) &&
           //(s4 == s100ToS4()));
    setScoreStd(sStd);
}

Score::Score(const Score &other):
    score100(other.score100),
    scoreLevel(other.scoreLevel),
    score4(other.score4),
    scoreStd(other.scoreStd)
{

}

QString Score::s100ToSLevel()
{
    int len = scoreStd.getLength();
    for(int i = 0; i < len; i++)
    {
        if(score100 <= scoreStd.std100At(i))
        {
            scoreLevel = scoreStd.stdLevelAt(i);
            return scoreLevel;
        }
    }
    return QString("undefined");
}

qreal Score::s100ToS4()
{
    int len = scoreStd.getLength();
    for(int i = 0; i < len; i++)
    {
        if(score100 <= scoreStd.std100At(i))
        {
            score4 = scoreStd.std4At(i);
            return score4;
        }
    }
    return -1;
}

int Score::sLevelToS100()
{
    int len = scoreStd.getLength();
    for(int i = 0; i < len; i++)
    {
        if(scoreLevel == scoreStd.stdLevelAt(i))
        {
            score100 = scoreStd.std100At(i);
            return score100;
        }
    }
    return -1;
}

qreal Score::sLevelToS4()
{
    int len = scoreStd.getLength();
    for(int i = 0; i < len; i++)
    {
        if(scoreLevel == scoreStd.stdLevelAt(i))
        {
            score4 = scoreStd.std4At(i);
            return score4;
        }
    }
    return -1;
}

int Score::s4ToS100()
{
    int len = scoreStd.getLength();
    for(int i = 0; i < len; i++)
    {
        if(score4 <= scoreStd.std4At(i))
        {
            score100 = scoreStd.std100At(i);
            return score100;
        }
    }
    return -1;
}

QString Score::s4ToSLevel()
{
    int len = scoreStd.getLength();
    for(int i = 0; i < len; i++)
    {
        if(score4 <= scoreStd.std4At(i))
        {
            scoreLevel = scoreStd.stdLevelAt(i);
            return scoreLevel;
        }
    }
    return QString("undefined");
}

int Score::getScore100() const
{
    return score100;
}

QString Score::getScoreLevel() const
{
    return scoreLevel;
}

qreal Score::getScore4() const
{
    return score4;
}

ScoreStandard Score::getScoreStd() const
{
    return scoreStd;
}

QStringList Score::getAll() const
{
    QStringList info;
    info << QString::asprintf("%d", score100)
         << scoreLevel
         << QString::asprintf("%.1f", score4);
    return info;
}

void Score::setScoreStd(ScoreStandard sStd)
{
    scoreStd = sStd;
}

void Score::setScore100(int s100)
{
    score100 = s100;
}

void Score::setScoreLevel(QString sLevel)
{
    scoreLevel = sLevel;
}

void Score::setScore4(qreal s4)
{
    score4 = s4;
}

bool Score::operator ==(const Score &other) const
{
    return score100 == other.score100;
}
