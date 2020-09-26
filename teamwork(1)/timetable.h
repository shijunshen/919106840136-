#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QWidget>
#include<QStandardItem>
#include<QStandardItemModel>
#include<Qstring>

namespace Ui {
class timeTable;
}

class timeTable : public QWidget
{
    Q_OBJECT

public:
    explicit timeTable(QWidget *parent = 0);
    ~timeTable();
    void setHeader();
    void setSub();

private slots:
    void on_previous_clicked();

    void on_next_clicked();


    void on_back_clicked();

private:
    Ui::timeTable *ui;
    int pages;
    QStandardItemModel *model1;
    QString str;

signals:
    void fanhui1();
};

#endif // TIMETABLE_H
