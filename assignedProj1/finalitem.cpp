#include "finalitem.h"

FinalItem::FinalItem()
{

}

FinalItem::FinalItem(QList<Student> &stuList, int stuNum, int courseNum,
                     QList<Teacher> &teaList):
    Course(stuList.at(stuNum).courseInfoAt(courseNum)),
    Score(stuList.at(stuNum).score100At(stuNum),
          stuList.at(stuNum).scoreLevelAt(stuNum),
          stuList.at(stuNum).score4At(stuNum)),
    student(stuList.at(stuNum).getBasics())
{
    int len = teaList.length();
    for(int i = 0; i < len; i++)
    {
        QStringList temp = teaList.at(i).getBasics();
        if(temp.contains(teacherNum) && temp.contains(teacherName))
        {
            teacher = Teacher(temp);
            break;
        }
    }
}

const Student &FinalItem::getStudent() const
{
    return student;
}

const Teacher &FinalItem::getTeacher() const
{
    return teacher;
}

Course FinalItem::getCourse() const
{
    return Course(cname, cnum, cdept, teacherName, teacherNum);
}

Score FinalItem::getScore() const
{
    return Score(score100, scoreLevel, score4);
}

void FinalItem::showInTable(QStandardItemModel *table, int row) const
{
    //set the first 4 columns
    int i = 0; //tell the current column
    QList<QStandardItem *> aRow;
    const Person *p = &student;
    QStringList list = p->getBasics();
    for(; i < 4; i++)
    {
        QStandardItem *aItem = new QStandardItem(list.at(i));
        //table->setItem(row, i, aItem);
        aRow << aItem;
    }

    //set column 5
    QStandardItem *aItem = new QStandardItem(cname);
    aRow << aItem;
    i++;

    //set column 6, 7 and 8
    aItem = new QStandardItem(score100);
    aRow << aItem;
    i++;
    aItem = new QStandardItem(scoreLevel);
    aRow << aItem;
    i++;
    aItem = new QStandardItem(score4);
    aRow << aItem;
    i++;

    //set column 9 and 10
    p = &teacher;
    list = p->getBasics();
    for(; i < 10; i++)
    {
    aItem = new QStandardItem(list[i - 8]);
    //table->setItem(row, i, aItem);
    aRow << aItem;
    }

    int tmp = table->rowCount();
    if((row >= 0) && (row < tmp))
    {
        for(int j = 0; j < 10; j++)
        {
            table->setItem(row, j, aRow[j]);
        }
    }
    else
    {
        table->insertRow(row, aRow);
    }
}

void FinalItem::setDisplayableMembers(int row, int column, QVariant data,
                                      QStandardItemModel *table)
{
    switch(column)
    {
    case 0: student.name = data.toString();
        break;
    case 1: student.num = data.toString();
        break;
    case 2: student.classnum = data.toString();
        break;
    case 3: student.sex = data.toString();
        break;
    case 4: cname = data.toString();
        break;
    case 5: setScore100(data.toInt());
        table->setItem(row, 6, new QStandardItem(s100ToSLevel()));
        break;
    case 6: setScoreLevel(data.toString());
        table->setItem(row, 7, new QStandardItem(QString::asprintf("%.1f", sLevelToS4())));
        break;
    case 7: setScore4(data.toDouble());
        break;
    case 8: teacher.name = data.toString();
        teacherName = teacher.name;
        break;
    case 9: teacher.dept = data.toString();
        break;
    default:
        break;
    }
}

bool FinalItem::operator ==(const FinalItem &other) const
{
    return (cname == other.cname &&
            teacherName == other.teacherName &&
            cnum == other.cnum &&
            cdept == other.cdept &&
            teacherNum == other.teacherNum &&
            score100 == other.score100 &&
            student == other.student &&
            teacher == other.teacher);
}
