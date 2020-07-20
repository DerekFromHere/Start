#ifndef PERSON_H
#define PERSON_H
#include "course.h"
#include "score.h"


class Person
{
public:
    Person();
    Person(QString na, QString nu, QString cl, QString se, QString de);
    Person(const Person &other);
    virtual ~Person();

    //output the data to the ui editor
    virtual QStringList getBasics() const = 0;

    //compare 2 person objects, by using the 1st object and the pointer of 2nd object
    //virtual bool operator ==(const Person *other) = 0;

    virtual QStringList courseInfoAt(int i) const = 0;

    static int getCountOfDigits(int i);

protected:
    QString name;
    QString num;
    QString classnum;
    QString sex;
    QString dept;

};

#endif // PERSON_H
