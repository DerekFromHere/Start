#ifndef STUDENT_H
#define STUDENT_H
#include "person.h"
#include "course.h"
#include <iostream>

class FinalItem;

struct CourseWithScore
{
    Course course;
    Score score;
};

class Student : public virtual Person
{
public:
    Student();
    Student(QString na, QString nu, QString cl, QString se, QString de);
    Student(const QStringList &basicInfo);
    Student(const Student &other);

    //export basic 5 elements at first, then export info of courses and scores
    virtual QStringList getBasics() const override;

    virtual QStringList courseInfoAt(int i) const override;

    int score100At(int i) const;

    QString scoreLevelAt(int i) const;

    qreal score4At(int i) const;

    int getCourseAndScoreListLength() const;

    void appendCourseAndScore(const Course &c, const Score &s);

    void clearCourseAndScore();

    friend std::ostream& operator <<(std::ostream& output, const Student& stu);

    bool operator ==(const Student &other) const;

    friend class FinalItem;

private:
    QList<CourseWithScore> stu_courseScoreList;

};

#endif // STUDENT_H
