#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "change_password.h"
#include "student.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void returnmainwindow();



private:
    Ui::MainWindow *ui;
    change_password a;
    Student b;


private slots:

    void on_xiugaimima_clicked();
    void on_denglu_clicked();
};

#endif // MAINWINDOW_H
