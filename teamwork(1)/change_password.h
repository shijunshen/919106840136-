#ifndef CHANGE_PASSWORD_H
#define CHANGE_PASSWORD_H

#include <QWidget>

namespace Ui {
class change_password;
}

class change_password : public QWidget
{
    Q_OBJECT

public:
    explicit change_password(QWidget *parent = nullptr);
    ~change_password();


signals:
    void Mysignal();



private slots:
    void on_queding_clicked();

    void on_fanhui_clicked();

private:
    Ui::change_password *ui;
};

#endif // CHANGE_PASSWORD_H
