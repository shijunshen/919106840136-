#include "timetable.h"
#include "ui_timetable.h"

timeTable::timeTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::timeTable)
{
    ui->setupUi(this);
    pages=0;
    this->model1=new QStandardItemModel;
    this->ui->tableView->setModel(model1);
    setHeader();
    setSub();
    str="第"+QString(pages+'0'+1)+"页";
    ui->label->setText(str);
}

timeTable::~timeTable()
{
    delete ui;
}
void timeTable::setHeader(){
    this->model1->setHorizontalHeaderItem(0,new QStandardItem("1"));
    this->model1->setHorizontalHeaderItem(1,new QStandardItem("2"));
    this->model1->setHorizontalHeaderItem(2,new QStandardItem("3"));
    this->model1->setHorizontalHeaderItem(3,new QStandardItem("4"));
    this->model1->setHorizontalHeaderItem(4,new QStandardItem("5"));
    this->model1->setHorizontalHeaderItem(5,new QStandardItem("6"));
    this->model1->setHorizontalHeaderItem(6,new QStandardItem("7"));


    this->model1->setRowCount(5);
    this->ui->tableView->setRowHeight(0,200);
    this->ui->tableView->setRowHeight(1,200);
    this->ui->tableView->setRowHeight(2,200);
    this->ui->tableView->setRowHeight(3,200);
    this->ui->tableView->setRowHeight(4,200);
    model1->setHeaderData(0,Qt::Vertical,"1");
    model1->setHeaderData(1,Qt::Vertical,"2");
    model1->setHeaderData(2,Qt::Vertical,"3");
    model1->setHeaderData(3,Qt::Vertical,"4");
    model1->setHeaderData(4,Qt::Vertical,"5");

}

void timeTable::setSub(){

}
void timeTable::on_previous_clicked()
{
    if(pages==0)pages=4;
    else pages--;
    this->model1->clear();
    str="第"+QString(pages+'0'+1)+"页";
    ui->label->setText(str);
    setHeader();
    setSub();
}

void timeTable::on_next_clicked()
{
    if(pages==4)pages=0;
    else pages++;
    this->model1->clear();
    str="第"+QString(pages+'0'+1)+"页";
    ui->label->setText(str);
    setHeader();
    setSub();
}



void timeTable::on_back_clicked()
{
    emit fanhui1();
}
