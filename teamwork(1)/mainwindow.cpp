#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "change_password.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QMessageBox>



QString account;
QString password;
QString LINE;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("登录界面");


    connect(&a,&change_password::Mysignal,this,&MainWindow::returnmainwindow);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_xiugaimima_clicked()
{
    this->close();
    a.show();
}


void MainWindow::returnmainwindow(){
    this->ui->zhanghao->clear();
    this->ui->mima->clear();
    a.hide();
    this->show();
}

void MainWindow::on_denglu_clicked()
{
    int flag=0;
    account=this->ui->zhanghao->text();
    password=this->ui->mima->text();
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
             QMessageBox::critical(this,"错误","用户名不存在！","确认");
             break;
         }
         case 1:{
             QMessageBox::critical(this,"密码错误","密码和用户名不匹配，\n请重新输入","确认");
             this->ui->zhanghao->clear();
             this->ui->mima->clear();
             break;
         }
         case 2:{
             b.show();
             this->hide();
             break;
         }
         }



    }
}
