#ifndef NEW_PASSWORD_H
#define NEW_PASSWORD_H

#include <QDialog>

namespace Ui {
class new_password;
}

class new_password : public QDialog
{
    Q_OBJECT

public:
    explicit new_password(QWidget *parent = 0);
    ~new_password();

private slots:
    void on_queding_clicked();

    void on_quxiao_clicked();




private:
    Ui::new_password *ui;
};

#endif // NEW_PASSWORD_H
