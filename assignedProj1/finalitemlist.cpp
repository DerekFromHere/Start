#include "finalitemlist.h"

FinalItemList::FinalItemList()
{

}

const FinalItem &FinalItemList::at(int i)
{
    return list.at(i);
}

int FinalItemList::length()
{
    return list.length();
}

void FinalItemList::append(const FinalItem &value)
{
    list.append(value);
}

void FinalItemList::insert(int i, const FinalItem &value)
{
    list.insert(i, value);
}

void FinalItemList::removeAt(int i)
{
    list.removeAt(i);
}

void FinalItemList::removeOne(const FinalItem &obj)
{
    list.removeOne(obj);
}

void FinalItemList::clear()
{
    list.clear();
}

FinalItem &FinalItemList::operator [](int i)
{
    return list[i];
}

void FinalItemList::showItemByNum(int num, QStandardItemModel *table, int row)
{
    list.at(num).showInTable(table, row);
}

void FinalItemList::on_currentChanged_inList(QStandardItem *aItem,
                                             QStandardItemModel *table)
{
    QModelIndex index = table->indexFromItem(aItem);
    list[index.row()].setDisplayableMembers(index.row(), index.column(),
                                                 index.data(), table);
}
