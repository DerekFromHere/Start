#include "student.h"
#include "course.h"

Student::Student()
{

}

Student::Student(QString na, QString nu, QString cl, QString se, QString de):
    Person(na, nu, cl, se, de)
{

}

Student::Student(const QStringList &basicInfo)
{
    name = basicInfo.at(0);
    num = basicInfo.at(1);
}

Student::Student(const Student &other):
    Person(other.name, other.num, other.classnum, other.sex, other.dept)
{
    stu_courseScoreList = other.stu_courseScoreList;
}

QStringList Student::getBasics() const
{
    QStringList info;
    info << name << num << classnum << sex << dept;
    return info;
}

QStringList Student::courseInfoAt(int i) const
{
    return stu_courseScoreList.at(i).course.getCourseInfo();
}

int Student::score100At(int i) const
{
    return stu_courseScoreList.at(i).score.getScore100();
}

QString Student::scoreLevelAt(int i) const
{
    return stu_courseScoreList.at(i).score.getScoreLevel();
}

qreal Student::score4At(int i) const
{
    return stu_courseScoreList.at(i).score.getScore4();
}

int Student::getCourseAndScoreListLength() const
{
    return  stu_courseScoreList.length();
}

void Student::appendCourseAndScore(const Course &c, const Score &s)
{
    CourseWithScore temp = {Course(c), Score(s)};
    stu_courseScoreList.append(temp);
}

void Student::clearCourseAndScore()
{
    stu_courseScoreList.clear();
}

bool Student::operator ==(const Student &other) const
{
    if((name == other.name) && (num == other.num))
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::ostream &operator <<(std::ostream &output, const Student &stu)
{
    QByteArray transit;
    char *data;
    //export basics
    transit = stu.name.toUtf8() + QByteArray("\t") +
              stu.num.toUtf8() + QByteArray("\t") +
              stu.classnum.toUtf8() + QByteArray("\t") +
              stu.sex.toUtf8() + QByteArray("\t") +
              stu.dept.toUtf8() + QByteArray("\t");

    //export the number of (CourseandScore)s
    int len = stu.stu_courseScoreList.length();
    char *temp = (char*)malloc(Person::getCountOfDigits(len) + 1);
    transit += QByteArray(itoa(len, temp, 10))
             + QByteArray("\t");
    free(temp);

    //export (CourseAndScore)s
    for(int i = 0; i < len; i++)
    {
        QStringList cInfo = stu.stu_courseScoreList.at(i).course.getCourseInfo(); //len: 3
        QStringList tInfo = stu.stu_courseScoreList.at(i).course.getTeacherInfo(); //len: 2
        QStringList sInfo = stu.stu_courseScoreList.at(i).score.getAll(); //len: 3
        for(int j = 0; j < cInfo.length(); j++)
        {
            transit += cInfo.at(j).toUtf8() + QByteArray("\t");
        }
        for(int j = 0; j < tInfo.length(); j++)
        {
            transit += tInfo.at(j).toUtf8() + QByteArray("\t");
        }
        for(int j = 0; j < sInfo.length(); j++)
        {
            transit += sInfo.at(j).toUtf8() + QByteArray("\t");
        }
    }

    data = transit.data();
    output << data;
    return output;
}
