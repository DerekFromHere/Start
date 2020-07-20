#include "teacher.h"
#include "course.h"

Teacher::Teacher()
{

}

Teacher::Teacher(QString na, QString nu, QString se, QString de)
{
    name = na;
    num = nu;
    sex = se;
    dept = de;
}

Teacher::Teacher(const QStringList &basicInfo)
{
    name = basicInfo.at(0);
    num = basicInfo.at(1);
    sex = basicInfo.at(2);
    dept = basicInfo.at(3);
}

Teacher::Teacher(const Teacher &other):
    Person()
{
    name = other.name;
    num = other.num;
    sex = other.sex;
    dept = other.dept;
    tea_courseList = other.tea_courseList;
}

QStringList Teacher::getBasics() const
{
    QStringList info;
    info << name << num << sex << dept;
    /*int len = tea_courseList.length();
    for(int i = 0; i < len; i++)
    {
        info << tea_courseList.at(i).getAll();
    }
    */
    return info;
}

QStringList Teacher::courseInfoAt(int i) const
{
    return tea_courseList.at(i).getCourseInfo();
}

void Teacher::operator =(const Teacher &other)
{
    name = other.name;
    num = other.num;
    sex = other.sex;
    dept = other.dept;
    tea_courseList = other.tea_courseList;
}

void Teacher::appendCourse(const Course &c)
{
    tea_courseList.append(c);
}

void Teacher::clearCourse()
{
    tea_courseList.clear();
}

bool Teacher::matchCourse(const Course &course) const
{
    return (course.getTeacherInfo().at(0) == name &&
            course.getTeacherInfo().at(1) == num);
}

bool Teacher::ifHaveCourse(const Course &course) const
{
    return tea_courseList.contains(course);
}

bool Teacher::operator ==(const Teacher &other) const
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

std::ostream &operator <<(std::ostream &output, const Teacher &tea)
{
    QByteArray transit;
    char *data;
    transit = tea.name.toUtf8() + QByteArray("\t") +
              tea.num.toUtf8() + QByteArray("\t") +
              tea.sex.toUtf8() + QByteArray("\t") +
              tea.dept.toUtf8() + QByteArray("\t");

    //export the number of Courses
    int len = tea.tea_courseList.length();
    char *temp = (char*)malloc(Person::getCountOfDigits(len) + 1);
    transit += QByteArray(itoa(len, temp, 10))
             + QByteArray("\t");
    free(temp);

    //export Courses
    for(int i = 0; i < len; i++)
    {
        QStringList cInfo = tea.tea_courseList.at(i).getCourseInfo(); //len: 3
        QStringList tInfo = tea.tea_courseList.at(i).getTeacherInfo(); //len: 2
        for(int j = 0; j < cInfo.length(); j++)
        {
            transit += cInfo.at(j).toUtf8() + QByteArray("\t");
        }
        for(int j = 0; j < tInfo.length(); j++)
        {
            transit += tInfo.at(j).toUtf8() + QByteArray("\t");
        }
    }

    data = transit.data();
    output << data;
    return output;
}
