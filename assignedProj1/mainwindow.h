#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QItemSelection>
#include <fstream>
#include "finalitemlist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);
    void on_itemChanged(QStandardItem *aItem);
    void on_actSave_triggered();
    void on_actOpen_triggered();
    void on_actInsert_triggered();
    void on_actAppend_triggered();

    void on_actRemove_triggered();

    void on_btnFilter_clicked();

    void on_chkShowAll_clicked(bool checked);

    void on_chkCourse_clicked(bool checked);

    void on_chkStudent_clicked(bool checked);

    void on_chkScoreInterval_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    QLabel *labCurFile;
    QLabel *labCellPos;               //当前单元格行列号
    QLabel *labCellText;              //The content of cur. unit
    QStandardItemModel *theModel;     //data model
    QItemSelectionModel *theSelection;//selection model

    //these 3 lists are used to store data
    QList<Student> stuList;
    QList<Teacher> teaList;
    FinalItemList itemList;

    //point to the current list of finalitems
    QList<FinalItem*> *curList;

    void iniCurList();

    void iniModelFromCurList();//initialize data model

    void iniStatusbar();

    void iniItemsFromStuTeaList();

    void getStrFromFile(QString &str, std::fstream &aFile);

    QString getStrFromFile(std::fstream &aFile);

signals:
    void displayItemByNum(int num, QStandardItemModel *theModel, int row);
    void currentChanged_toList(QStandardItem *aItem, QStandardItemModel *table);

};
#endif // MAINWINDOW_H
