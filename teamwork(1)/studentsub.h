#ifndef STUDENTSUB_H
#define STUDENTSUB_H

#include <QWidget>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QPushButton>

namespace Ui {
class studentSub;
}

class studentSub : public QWidget
{
    Q_OBJECT

public:
    explicit studentSub(QWidget *parent = 0);
    ~studentSub();
    void  sendSignal();
    int readsubjectfile();
    int readselectedfile();
    void display1(int row, QStringList course_line);
    void display2(int row, QStringList selected_line);
    void setHeader1();
    void setHeader2();
    void writeIn(QString info);

private:
    Ui::studentSub *ui;
    QStandardItemModel *model1;
    QStandardItemModel *model2;
    QList<QString> course_line;
    QList<QString> selected_line;
    QPushButton b;

signals:
    void fanhui();
private slots:
    void on_tb_select_doubleClicked(const QModelIndex &index);
    void on_tb_subject_doubleClicked(const QModelIndex &index);
    void on_show_clicked();
};

#endif // STUDENTSUB_H
