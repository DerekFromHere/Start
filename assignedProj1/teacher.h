#ifndef TEACHER_H
#define TEACHER_H

#include "person.h"
#include "course.h"

class FinalItem;

class Teacher : public virtual Person
{
public:
    Teacher();
    Teacher(QString na, QString nu, QString se, QString de);
    Teacher(const QStringList &basicInfo);
    Teacher(const Teacher &other);

    //export basic 5 elements at first, then export info of courses
    virtual QStringList getBasics() const override;

    virtual QStringList courseInfoAt(int i) const override;

    void operator =(const Teacher &other);

    void appendCourse(const Course &c);

    void clearCourse();

    //return if this teacher teach this course
    bool matchCourse(const Course &course) const;

    bool ifHaveCourse(const Course &course) const;

    friend std::ostream &operator <<(std::ostream &output, const Teacher &tea);

    bool operator ==(const Teacher &other) const;

    friend class FinalItem;

protected:
    QList<Course> tea_courseList;


};

#endif // TEACHER_H
