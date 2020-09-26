#include "studentsub.h"
#include "ui_studentsub.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>

studentSub::studentSub(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::studentSub)
{

    ui->setupUi(this);
    this->setWindowTitle("学生课程管理");
    b.setParent(this);
    b.setText("返回");
    b.move(750,750);
    this->model1=new QStandardItemModel;
    this->ui->tb_subject->setModel(model1);
    setHeader1();
    this->ui->tb_subject->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tb_subject->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->model2=new QStandardItemModel;
    this->ui->tb_select->setModel(model2);
    setHeader2();
    readselectedfile();
    int r=0;
    for(int i=0;i<selected_line.length();i++)
    {
        QString line=selected_line.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split(" ");
        display2(r++, linesplit);
    }
    this->ui->tb_select->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tb_select->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(&b,&QPushButton::clicked,this,&studentSub::sendSignal);

}
void studentSub::setHeader1(){
    this->model1->setHorizontalHeaderItem(0,new QStandardItem("课程名称"));
    this->model1->setHorizontalHeaderItem(1,new QStandardItem("教师姓名"));
    this->model1->setHorizontalHeaderItem(2,new QStandardItem("课程性质"));
    this->model1->setHorizontalHeaderItem(3,new QStandardItem("学分"));
    this->model1->setHorizontalHeaderItem(4,new QStandardItem("上课时间"));
    this->model1->setHorizontalHeaderItem(5,new QStandardItem("上课地点"));

    this->ui->tb_subject->setColumnWidth(0,120);
    this->ui->tb_subject->setColumnWidth(1,80);
    this->ui->tb_subject->setColumnWidth(2,100);
    this->ui->tb_subject->setColumnWidth(3,50);
    this->ui->tb_subject->setColumnWidth(4,90);
    this->ui->tb_subject->setColumnWidth(5,90);
}

void studentSub::setHeader2(){
    this->model2->setHorizontalHeaderItem(0,new QStandardItem("课程名称"));
    this->model2->setHorizontalHeaderItem(1,new QStandardItem("教师姓名"));
    this->model2->setHorizontalHeaderItem(2,new QStandardItem("课程性质"));
    this->model2->setHorizontalHeaderItem(3,new QStandardItem("学分"));
    this->model2->setHorizontalHeaderItem(4,new QStandardItem("上课时间"));
    this->model2->setHorizontalHeaderItem(5,new QStandardItem("上课地点"));

    this->ui->tb_select->setColumnWidth(0,120);
    this->ui->tb_select->setColumnWidth(1,80);
    this->ui->tb_select->setColumnWidth(2,100);
    this->ui->tb_select->setColumnWidth(3,50);
    this->ui->tb_select->setColumnWidth(4,90);
    this->ui->tb_select->setColumnWidth(5,90);

}

int studentSub::readsubjectfile()
{
    course_line.clear();
    QFile file("subject.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return -1;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
       QString line=in.readLine();
       course_line.append(line);
    }
    file.close();
    return 0;
}

int studentSub::readselectedfile()
{
    selected_line.clear();
    QFile file("selected.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return -1;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
       QString line=in.readLine();
       selected_line.append(line);
       QStringList linesplit=line.split(" ");
    }
    file.close();
    return 0;
}


void studentSub::display1(int row, QStringList course_line)
{
    int i=0;
    for (i=0;i<course_line.length();i++)
    {
        this->model1->setItem(row,i,new QStandardItem(course_line.at(i)));
    }
}


void studentSub::display2(int row, QStringList selected_line)
{
    int i=0;
    for (i=0;i<selected_line.length();i++)
    {
        this->model2->setItem(row,i,new QStandardItem(selected_line.at(i)));
    }
}


studentSub::~studentSub()
{
    delete ui;
}


void studentSub::sendSignal(){
    emit fanhui();
}

void studentSub::on_tb_select_doubleClicked(const QModelIndex &index)
{
    int row=this->ui->tb_select->currentIndex().row();
    QString name=model2->data(model2->index(row,0)).toString();
    int ret=QMessageBox::question(this,"请确认","确定退出当前课程？","退课","取消");
    if(ret==0)
    {
        int i=0;
        for (i=0;i<selected_line.length();i++)
        {
            QString line=selected_line.at(i);
            line=line.trimmed();
            QStringList linesplit=line.split(" ");
            if(name!=linesplit.at(0))
            {
                QFile file("selected_temp.txt");
                if(!file.open(QIODevice::Append|QIODevice::Text))
                {
                   QMessageBox::critical(this,"错误","文件打开失败！","确认");
                   return;
                }
            QTextStream out(&file);
            out<<line+"\n";
            file.close();
            }
        }
        QFile file_old("selected.txt");
        QFile file_new("selected_temp.txt");
        if (file_old.exists())
        {
           file_old.remove();
           file_new.rename("selected.txt");
        }
        else
        {
           QMessageBox::critical(this,"错误","未有信息保存为文件，无法退课","确认");
        }
        QMessageBox::information(this,"通知","退课成功！","确认");
    }
    this->model2->clear();
    setHeader2();
    readselectedfile();
    int r=0;
    for(int i=0;i<selected_line.length();i++)
    {
        QString line=selected_line.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split(" ");
        display2(r++, linesplit);
    }
}


void studentSub::on_tb_subject_doubleClicked(const QModelIndex &index)
{
    int flag=0;
    int row=this->ui->tb_subject->currentIndex().row();
    QString name=model1->data(model1->index(row,0)).toString();
    QString id=model1->data(model1->index(row,1)).toString();
    QString nature=model1->data(model1->index(row,2)).toString();
    QString point=model1->data(model1->index(row,3)).toString();
    QString college=model1->data(model1->index(row,4)).toString();
    QString place=model1->data(model1->index(row,5)).toString();

    readselectedfile();
    for(int i=0;i<selected_line.length();i++)
    {
        QString line=selected_line.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split(" ");
        if(name==linesplit.at(0))
        {
            QMessageBox::critical(this,"错误","不可重复选择课程！","确认");
            flag=1;
        }
    }

    if(flag==0)
    {
    QString messagebox_out="课程名称："+name+"\n"+"教师姓名："+id+"\n"+"课程性质："+nature+"\n"+
                           "课程学分："+point+"\n"+"上课时间："+college+"\n"+"上课地点："+place;
    QString info=name+" "+id+" "+nature+" "+point+" "+college+" "+place;

    int ret=QMessageBox::question(this,"请确认",messagebox_out,"选课","取消");
    if(ret==0)
       {
          writeIn(info);
       }
    this->model2->clear();
    setHeader2();
    readselectedfile();
    int r=0;
    for(int i=0;i<selected_line.length();i++)
    {
        QString line=selected_line.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split(" ");
        display2(r++, linesplit);
    }
    }
}

void studentSub::writeIn(QString info)
{
    QFile mFile("selected.txt");
    if(!mFile.open(QIODevice::Append|QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","文件打开失败，课程没有添加","确认");
        return;
    }
    QTextStream out(&mFile);
    out<<info<<"\n";
    mFile.flush();
    mFile.close();
}

void studentSub::on_show_clicked()
{
    this->model1->clear();
    setHeader1();
    readsubjectfile();
    int r=0;
    for(int i=0;i<course_line.length();i++)
    {
        QString line=course_line.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split(" ");
        display1(r++, linesplit);
    }
}
