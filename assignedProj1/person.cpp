#include "person.h"

Person::Person()
{

}

Person::Person(QString na, QString nu, QString cl, QString se, QString de):
    name(na),
    num(nu),
    classnum(cl),
    sex(se),
    dept(de)
{

}

Person::Person(const Person &other):
    name(other.name),
    num(other.num),
    classnum(other.classnum),
    sex(other.sex),
    dept(other.dept)
{

}

Person::~Person()
{

}

int Person::getCountOfDigits(int i)
{
    int count = 0;
    while(i != 0)
    {
        i /= 10;
        count ++;
    }
    return count;
}
