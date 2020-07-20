#ifndef COURSE_H
#define COURSE_H

#include <QStringList>

const int courseInfoCount = 3;
const int cTeacherInfoCount = 2;

class Course
{
public:
    Course();
    Course(QString na, QString nu, QString de, QString tNa, QString tNu);
    Course(const QStringList& info);
    Course(const Course& other);
    ~Course();
    QString getCourseName() const;

    QStringList getCourseInfo() const;

    //return the name and number of its teacher
    QStringList getTeacherInfo() const;

    bool operator ==(const Course &other) const;
protected:
    QString cname; //name of the course
    QString cnum;  //number of the course
    QString cdept; //the faculty
    QString teacherName;
    QString teacherNum;
};

#endif // COURSE_H
