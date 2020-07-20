#include "course.h"
#include <iostream>
#include <cstring>
#include <QStringList>
using namespace std;

Course::Course()
{

}

Course::Course(QString na, QString nu, QString de, QString tNa, QString tNu):
    cname(na),
    cnum(nu),
    cdept(de),
    teacherName(tNa),
    teacherNum(tNu)
{

}

Course::Course(const QStringList &info)
{
    assert(info.length() == 5);
    cname = info.at(0);
    cnum = info.at(1);
    cdept = info.at(2);
    teacherName = info.at(3);
    teacherNum = info.at(4);
}

Course::Course(const Course &other)
{
    cname = other.cname;
    cnum = other.cnum;
    cdept = other.cdept;
}

Course::~Course()
{

}

QString Course::getCourseName() const
{
    return cname;
}

QStringList Course::getCourseInfo() const
{
    QStringList info;
    info << cname << cnum << cdept;
    return info;
}

QStringList Course::getTeacherInfo() const
{
    QStringList info;
    info << teacherName << teacherNum;
    return info;
}

bool Course::operator ==(const Course &other) const
{
    return (cname == other.cname &&
            teacherName == other.teacherName &&
            cnum == other.cnum &&
            cdept == other.cdept &&
            teacherNum == other.teacherNum);
}
