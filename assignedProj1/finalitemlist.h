#ifndef FINALITEMLIST_H
#define FINALITEMLIST_H

#include "finalitem.h"
#include <QList>
#include <QStandardItemModel>

class FinalItemList : public QObject
{
    Q_OBJECT
public:
    FinalItemList();
    const FinalItem &at(int i);
    int length();
    void append(const FinalItem &value);
    void insert(int i, const FinalItem &value);
    void removeAt(int i);
    void removeOne(const FinalItem &obj);
    void clear();
    FinalItem & operator [](int i);

private:
    QList<FinalItem> list;

private slots:
    //insert a row in the table
    void showItemByNum(int num, QStandardItemModel *table, int row);
    void on_currentChanged_inList(QStandardItem *aItem, QStandardItemModel *table);

};

#endif // FINALITEMLIST_H
