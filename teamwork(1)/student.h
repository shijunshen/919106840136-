#ifndef STUDENT_H
#define STUDENT_H

#include <QWidget>
#include"studentsub.h"
#include"timetable.h"

namespace Ui {
class Student;
}

class Student : public QWidget
{
    Q_OBJECT

public:
    explicit Student(QWidget *parent = 0);
    ~Student();
    void showWin1();
    void showWin2();

private slots:


    void on_xuanke_clicked();

    void on_tuichu_clicked();

    void on_pushButton_clicked();

private:
    Ui::Student *ui;
    studentSub w1;
    timeTable w2;

};

#endif // STUDENT_H
