#include "new_password.h"
#include "ui_new_password.h"
#include "change_password.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <QMessageBox>

extern QString account;
extern QString password;
extern QString LINE;


new_password::new_password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_password)
{
    ui->setupUi(this);
    setWindowTitle("修改密码");
}

new_password::~new_password()
{
    delete ui;
}

void new_password::on_queding_clicked()
{

    QString pw=this->ui->xinmima->text();
    QString qdpw=this->ui->quedingmima->text();
    if(pw==password){
        QMessageBox::critical(this,"错误","修改的密码不能与原密码相同","确认");
        this->ui->xinmima->clear();
        this->ui->quedingmima->clear();
    }
    if(pw!=qdpw){
        QMessageBox::critical(this,"错误","两次输入的密码不一致","确认");
        this->ui->xinmima->clear();
        this->ui->quedingmima->clear();
    }
    else if(pw.length()<1||qdpw.length()<1){
        QMessageBox::critical(this,"错误","请输入完整信息！","确认");
        this->ui->xinmima->clear();
        this->ui->quedingmima->clear();
    }
    else{
        extern QString LINE;
        QFile file("student.txt");
        QString strAll;
        QStringList strList;
        if(file.open((QIODevice::ReadOnly|QIODevice::Text)))
        {
            QTextStream stream(&file);
            strAll=stream.readAll();
        }
        file.close();



        QFile file_old("student.txt");

        QFile file_new("student_temp.txt");
        file_new.open(QIODevice::WriteOnly | QIODevice::Text);
        file_new.close();
        if(file_old.exists()){
            file_old.remove();
            file_new.rename("student.txt");
            if(file_new.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                qDebug()<<account<<" "<<pw;
                QTextStream stream(&file_new);
                strList=strAll.split("\n");
               // qDebug()<<LINE;
                for(int i=0;i<strList.count();i++)
                {
                    qDebug()<<strList.at(i);
                    if(i==strList.count()-1)
                    {
                        if(strList.at(i)==LINE){
                            stream<<account<<" "<<pw;
                        }
                        else{stream<<strList.at(i);}
                    }
                    else
                    {
                        if(strList.at(i)==LINE){
                            stream<<account<<" "<<pw<<'\n';
                        }
                        else{stream<<strList.at(i)<<'\n';}
                    }
                }
            }
            QMessageBox::information(this,"通知","修改成功！","确认");


        }

        else
        {
          QMessageBox::critical(this,"错误","未有信息保存为文件，无法修改","确认");
        }

        this->close();


    }
}

void new_password::on_quxiao_clicked()
{
    this->close();
}
