#include "student.h"
#include "ui_student.h"
#include"studentsub.h"
#include"timetable.h"

Student::Student(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Student)
{
    ui->setupUi(this);
    connect(&w1,&studentSub::fanhui,this,&Student::showWin1);
    connect(&w2,&timeTable::fanhui1,this,&Student::showWin2);
}

Student::~Student()
{
    delete ui;
}

void Student::on_xuanke_clicked()
{
    this->hide();
    w1.show();
}

void Student::showWin1(){
    w1.close();
    this->show();
}

void Student::on_tuichu_clicked()
{
    this->close();
}

void Student::on_pushButton_clicked()
{
    this->hide();
    w2.show();
}
void Student::showWin2(){
    w2.close();
    this->show();
}
