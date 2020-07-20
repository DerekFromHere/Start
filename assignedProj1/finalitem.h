#ifndef FINALITEM_H
#define FINALITEM_H

#include "student.h"
#include "teacher.h"
#include "course.h"
#include "score.h"
#include <QList>
#include <QStandardItemModel>

class FinalItem: public virtual Course, public virtual Score
{

public:
    FinalItem();
    FinalItem(QList<Student> &stuList, int stuNum, int courseNum,
              QList<Teacher> &teaList);

    const Student &getStudent() const;
    const Teacher &getTeacher() const;
    Course getCourse() const;
    Score getScore() const;
    //export the info to the given row in the given table
    void showInTable(QStandardItemModel *table, int row) const;

    //set various items that are displayed in Ui
    void setDisplayableMembers(int row, int column, QVariant data,
                               QStandardItemModel *table);

    bool operator ==(const FinalItem &other) const;

private:
    Student student;
    Teacher teacher;

};

#endif // FINALITEM_H
