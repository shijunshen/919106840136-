#include "change_password.h"
#include "ui_change_password.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QStringList>
#include "new_password.h"
#include "mainwindow.h"

#include <QDebug>


extern QString account;
extern QString password;
extern QString LINE;

change_password::change_password(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::change_password)
{
    ui->setupUi(this);
    setWindowTitle("修改密码");

}

change_password::~change_password()
{
    delete ui;
}



void change_password::on_queding_clicked()
{



    account=this->ui->yonghuming->text();
    password=this->ui->yuanmima->text();
    int flag=0;
    LINE=account;
    LINE=LINE.append(" ");
    LINE=LINE.append(password);
    QFile file("student.txt");
    if(account.length()<1||password.length()<1){
        QMessageBox::critical(this,"错误","请输入账号和密码！","确认");
    }
    else if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QMessageBox::critical(this,"错误","学生数据库文件丢失！","确认");
    }
    else{
        QTextStream in(&file);
        while(!in.atEnd()){
            QString line=in.readLine();
            line=line.trimmed();
            QStringList linesplit=line.split(" ");
            if(account==linesplit.at(0)&&password!=linesplit.at(1)){
                flag=1;
                break;
            }
            else if(account==linesplit.at(0)&&password==linesplit.at(1)){
                flag=2;
                break;
            }
        }
        file.close();
        switch(flag){
        case 0:{
            this->close();
            QMessageBox::critical(this,"错误","查询不到该学生信息！","确认");
            break;
        }
        case 1:{
            QMessageBox::critical(this,"密码错误","密码和用户名不匹配，\n请重新输入","确认");
            this->ui->yuanmima->clear();
            this->ui->yonghuming->clear();
            break;
        }
        case 2:{
            new_password *a=new new_password;
            this->close();
            a->show();
            break;
        }
        }
    }
}

void change_password::on_fanhui_clicked()
{
    this->ui->yonghuming->clear();
    this->ui->yuanmima->clear();
    emit Mysignal();
}


