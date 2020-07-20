#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractItemView>
#include <QFileDialog>
#include <QMessageBox>
#include <QList>
#include <fstream>

const int FixedColumnCount = 10;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitter_2);
    theModel = new QStandardItemModel(0, FixedColumnCount, this);
    iniCurList();
    iniModelFromCurList();
    theSelection = new QItemSelectionModel(theModel);
    connect(theSelection, SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)),
            this, SLOT(on_currentChanged(const QModelIndex &, const QModelIndex &)));
    connect(theModel, SIGNAL(itemChanged(QStandardItem *)),
            this, SLOT(on_itemChanged(QStandardItem *)));
    connect(this, SIGNAL(displayItemByNum(int, QStandardItemModel *, int)),
            &itemList, SLOT(showItemByNum(int, QStandardItemModel *, int)));
    connect(this, SIGNAL(currentChanged_toList(QStandardItem *, QStandardItemModel *)),
            &itemList, SLOT(on_currentChanged_inList(QStandardItem *, QStandardItemModel *)));
    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->chkShowAll->setCheckState(Qt::Checked);
    iniStatusbar();
}

void MainWindow::iniStatusbar()
{
    labCurFile = new QLabel("当前文件：");
    ui->statusbar->addWidget(labCurFile);
    ui->statusbar->addWidget(new QSplitter(Qt::Vertical));
    labCellPos = new QLabel("当前单元格：");
    ui->statusbar->addWidget(labCellPos);
    ui->statusbar->addWidget(new QSplitter(Qt::Vertical));
    labCellText = new QLabel("当前单元格内容：");
    ui->statusbar->addWidget(labCellText);
}

void MainWindow::iniItemsFromStuTeaList()
{
    itemList.clear();
    int len = stuList.length();
    for(int i = 0; i < len; i++) //enumerate the students
    {
        int count = stuList.at(i).getCourseAndScoreListLength(); //enumerate the courses
        for(int j = 0; j < count; j++)
        {
            FinalItem *temp = new FinalItem(stuList, i, j, teaList);
            itemList.append(*temp);
        }
    }
}

void MainWindow::getStrFromFile(QString &str, std::fstream &aFile)
{
    char buffer[80];
    aFile.get(buffer, 80, '\t');
    aFile.seekg(1, std::ios::cur);
    str = QString::fromUtf8(buffer, strlen(buffer));
}

QString MainWindow::getStrFromFile(std::fstream &aFile)
{
    char buffer[80];
    aFile.get(buffer, 80, '\t');
    aFile.seekg(1, std::ios::cur);
    return QString::fromUtf8(buffer, strlen(buffer));
}


MainWindow::~MainWindow()
{
    delete ui;
    delete labCellPos;
    delete labCurFile;
    delete labCellText;
    delete theModel;
    delete theSelection;
}

void MainWindow::on_currentChanged(const QModelIndex &current,
                                   const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if(current.isValid())
    {
        labCellPos->setText(QString::asprintf("当前单元格：%d行，%d列",
                                              current.row(), current.column()));
        labCellText->setText(current.data().toString());
    }
}

void MainWindow::on_itemChanged(QStandardItem *aItem)
{
    //emit currentChanged_toList(aItem, theModel);
    QModelIndex index = theSelection->currentIndex();
    (*curList)[index.row()]->setDisplayableMembers(index.row(), index.column(),
                                                   aItem->data(), theModel);
}


void MainWindow::on_actSave_triggered()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString aFileName = QFileDialog::getSaveFileName(this, "选择一个文件", curPath
                                                     , "成绩数据文件(*.dat);;所有文件(*.*)");
    if(aFileName.isEmpty())
        return;
    QByteArray temp = aFileName.toLatin1();
    char *fileName = temp.data();
    std::fstream aFile(fileName, std::ios::out | std::ios::trunc);   //get the file to save

    //turn finalItems to stuList and teaList
    stuList.clear();
    teaList.clear();
    int count = itemList.length();
    for(int i = 0; i < count; i++)
    {
        bool flag = false;

        //try to find the student,
        //and append course and score if it exists
        for(int j = 0; j < stuList.length(); j++)
        {
            if(itemList.at(i).getStudent() == stuList.at(j))
            {
                Student *stu = new Student(stuList.at(j));
                stu->appendCourseAndScore(itemList.at(i).getCourse(),
                                          itemList.at(i).getScore());
                stuList.replace(j, *stu);
                flag = true;
                break;
            }            
        }

        //if the student doesn't exist, create one
        if(flag == false)
        {
            Student *stu = new Student(itemList.at(i).getStudent());
            stu->clearCourseAndScore();
            stu->appendCourseAndScore(itemList.at(i).getCourse(),
                                      itemList.at(i).getScore());
            stuList.append(*stu);
        }

        //try to find the teacher
        flag = false;
        for(int j = 0; j < teaList.length(); j++)
        {
            //as long as there is a teacher in the list,
            //and this teacher contains no such course
            if(itemList.at(i).getTeacher() == teaList.at(j) &&
                    !(teaList.at(j).ifHaveCourse(itemList.at(i).getCourse())))
            {
                Teacher *tea = new Teacher(teaList.at(j));
                tea->appendCourse(itemList.at(i).getCourse());
                teaList.replace(j, *tea);
                flag = true;
                break;
            }
        }

        //if the teacher doesn't exist
        if(flag == false)
        {
            Teacher *tea = new Teacher(itemList.at(i).getTeacher());
            tea->clearCourse();
            tea->appendCourse(itemList.at(i).getCourse());
            teaList.append(*tea);
        }
    }

    /*
    int len = stuList.length();
    aFile.write((char*)&len, sizeof(uint));
    for(int i = 0; i < len; i++)
    {
        uint objSize = sizeof(stuList.at(i));
        aFile.write((char*)&objSize, sizeof(uint));
        Student tmp(stuList[i]);
        aFile.write((const char*)&tmp, objSize);
    }
    len = teaList.length();
    aFile.write((char*)&len, sizeof(uint));
    for(int i = 0; i < len; i++)
    {
        uint objSize = sizeof(teaList.at(i));
        aFile.write((char*)&objSize, sizeof(uint));
        Teacher tmp(teaList[i]);
        aFile.write((const char*)&tmp, objSize);
    }

    aFile.close();
    */

    //export stuList and teaList to the file

    aFile << stuList.length() << "\t";
    for(int i = 0; i < stuList.length(); i++)
    {
        aFile << stuList.at(i);
    }
    aFile << teaList.length() << "\t";
    for(int i = 0; i < teaList.length(); i++)
    {
        aFile << teaList.at(i);
    }

    aFile.close();

}

void MainWindow::on_actOpen_triggered()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString aFileName = QFileDialog::getOpenFileName(this, "选择一个文件", curPath
                                                     , "成绩数据文件(*.dat);;所有文件(*.*)");
    if(aFileName.isEmpty())
        return;
    QByteArray temp = aFileName.toLatin1();
    char *fileName = temp.data();
    std::fstream aFile(fileName, std::ios::in);   //open the file

    //read stuList and teaList
    stuList.clear();
    teaList.clear();
    uint len;
    aFile.seekg(std::ios::beg);
    len = getStrFromFile(aFile).toUInt();
    if(len <= 0)
    {
        QMessageBox::warning(this, "警告", "文件不符合要求或已损坏。");
        return;
    }
    for(uint i = 0; i < len; i++) //enumerate the Students
    {
        /*
        uint objSize;
        aFile.read((char*)&objSize, sizeof(uint));
        Student *stu = new Student();
        aFile.read((char*)&stu, objSize);
        stuList.append(*stu);
        */

        //get the basics
        QString na, nu, cl, se, de;
        getStrFromFile(na, aFile);
        getStrFromFile(nu, aFile);
        getStrFromFile(cl, aFile);
        getStrFromFile(se, aFile);
        getStrFromFile(de, aFile);
        Student *stu = new Student(na, nu, cl, se, de);

        //get the (CourseAndScore)s
        int count = getStrFromFile(aFile).toInt();  //the number of (CourseAndScore)s
        Course *cBuffer;
        Score *sBuffer;
        for(int j = 0; j < count; j++)
        {
            getStrFromFile(na, aFile);
            getStrFromFile(nu, aFile);
            getStrFromFile(de, aFile);
            QString tNa = getStrFromFile(aFile);
            QString tNu = getStrFromFile(aFile);
            cBuffer = new Course(na, nu, de, tNa, tNu);

            int s100 = getStrFromFile(aFile).toInt();
            QString sLevel = getStrFromFile(aFile);
            qreal s4 = getStrFromFile(aFile).toDouble();
            sBuffer = new Score(s100, sLevel, s4);

            stu->appendCourseAndScore(*cBuffer, *sBuffer);
        }
        stuList.append(*stu);
    }

    len = getStrFromFile(aFile).toUInt();
    for(uint i = 0; i < len; i++)
    {
        /* temporarily aborted:get info from dat file
        uint objSize;
        aFile.read((char*)&objSize, sizeof(uint));
        Teacher *tea = (Teacher*)malloc(objSize);
        aFile.read((char*)&tea, objSize);
        teaList.append(*tea);
        */

        //get the basics
        QString na, nu, se, de;
        getStrFromFile(na, aFile);
        getStrFromFile(nu, aFile);
        getStrFromFile(se, aFile);
        getStrFromFile(de, aFile);
        Teacher *tea = new Teacher(na, nu, se, de);

        //get the Courses
        int count = getStrFromFile(aFile).toInt(); //the number of courses
        Course *cBuffer;
        for(int j = 0; j < count; j++)
        {
            getStrFromFile(na, aFile);
            getStrFromFile(nu, aFile);
            getStrFromFile(de, aFile);
            QString tNa = getStrFromFile(aFile);
            QString tNu = getStrFromFile(aFile);
            cBuffer = new Course(na, nu, de, tNa, tNu);
            tea->appendCourse(*cBuffer);
        }
        teaList.append(*tea);
    }
    aFile.close();
    iniItemsFromStuTeaList();
    iniModelFromCurList();
}

void MainWindow::iniModelFromCurList()
{
    theModel->clear();
    QStringList headerList;
    headerList << "姓名" << "学号" << "班号" <<"性别" << "科目" << "百分制成绩"
               << "等级制成绩" << "绩点制成绩" << "授课教师姓名" << "授课教师系别";
    theModel->setHorizontalHeaderLabels(headerList);
    for(int i = 0; i < curList->length(); i++)
    {
        curList->at(i)->showInTable(theModel, i);
    }
}

void MainWindow::on_actInsert_triggered()
{
    int row = theSelection->currentIndex().row();
    FinalItem *temp = new FinalItem();
    int i = 0;
    for(; i < itemList.length(); i++)
    {
        if(curList->at(row) == &itemList.at(i))
        {
            itemList.insert(i, *temp);
            break;
        }
    }
    curList->insert(row, &itemList[i]);
    free(temp);
    curList->at(row)->showInTable(theModel, row);
}

void MainWindow::on_actAppend_triggered()
{
    int row = theModel->rowCount();
    FinalItem *temp = new FinalItem();
    itemList.append(*temp);
    curList->append(&itemList[row]);
    free(temp);
    curList->at(row)->showInTable(theModel, row);
}

void MainWindow::on_actRemove_triggered()
{
    int row = theSelection->currentIndex().row();
    theModel->removeRow(row);
    for(int i = 0; i < itemList.length(); i++)
    {
        if(curList->at(row) == &itemList.at(i))
        {
            itemList.removeAt(i);
            break;
        }
    }
    curList->removeAt(row);
}

void MainWindow::on_btnFilter_clicked()
{
    //to check if the current filter is valid
    if(ui->sBoxSmall > ui->sBoxLarge)
    {
        QMessageBox::warning(this, "筛选条件不合法！", "成绩区间为空集。");
        return;
    }

    iniCurList();

    if(ui->chkShowAll->checkState() == Qt::Checked)
    {

    }
    else
    {
        if(ui->chkCourse->checkState() == Qt::Checked)
        {
            QList<FinalItem*> *tempList = new QList<FinalItem*>();
            QString courseName = ui->linCourseName->text();
            for(int i = 0; i < curList->length(); i++)
            {
                if(courseName == curList->at(i)->getCourseName())
                {
                    tempList->append((*curList)[i]);
                }
            }
            free(curList);
            curList = tempList;
        }

        if(ui->chkStudent->checkState() == Qt::Checked)
        {
            QList<FinalItem*> *tempList = new QList<FinalItem*>();
            QString stuName = ui->linStudentName->text();
            QString stuNum = ui->linStudentNumber->text();
            for(int i = 0; i < curList->length(); i++)
            {
                QStringList basics = curList->at(i)->getStudent().getBasics();
                QString tmpName = basics.at(0);
                QString tmpNum = basics.at(1);
                if(stuName == tmpName && stuNum == tmpNum)
                {
                    tempList->append(curList->at(i));
                }
            }
            free(curList);
            curList = tempList;
        }

        if(ui->chkScoreInterval->checkState() == Qt::Checked)
        {
            QList<FinalItem*> *tempList = new QList<FinalItem*>();
            for(int i = 0; i < curList->length(); i++)
            {
                if(ui->sBoxSmall->value() <= curList->at(i)->getScore100() &&
                   curList->at(i)->getScore100() <= ui->sBoxLarge->value())
                {
                    tempList->append(curList->at(i));
                }
            }
            free(curList);
            curList = tempList;
        }

    }
    //check if list is empty
    if(curList->length() == 0)
    {
        QMessageBox::warning(this, "提示", "没有找到符合条件的项。");
        return;
    }

    //not empty, setup the model.
    theModel->clear();
    QStringList headerList;
    headerList << "姓名" << "学号" << "班号" <<"性别" << "科目" << "百分制成绩"
               << "等级制成绩" << "绩点制成绩" << "授课教师姓名" << "授课教师系别";
    theModel->setHorizontalHeaderLabels(headerList);
    for(int i = 0; i < curList->length(); i++)
    {
        curList->at(i)->showInTable(theModel, i);
    }
}

void MainWindow::on_chkShowAll_clicked(bool checked)
{
    if(checked)
    {
        ui->chkCourse->setCheckState(Qt::Unchecked);
        ui->chkStudent->setCheckState(Qt::Unchecked);
        ui->chkScoreInterval->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_chkCourse_clicked(bool checked)
{
    if(checked)
    {
        ui->chkShowAll->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_chkStudent_clicked(bool checked)
{
    if(checked)
    {
        ui->chkShowAll->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_chkScoreInterval_clicked(bool checked)
{
    if(checked)
    {
        ui->chkShowAll->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::iniCurList()
{
    for(int i = 0; i < itemList.length(); i++)
    {
        curList->append(&(itemList[i]));
    }
}
