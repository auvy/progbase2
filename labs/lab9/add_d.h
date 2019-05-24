#ifndef ADD_D_H
#define ADD_D_H

#include <QDialog>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QRegExpValidator>

#include "dino.h"


namespace Ui {
class add_d;
}

class add_d : public QDialog
{
    Q_OBJECT

public:
    explicit add_d(QWidget *parent = 0);
    ~add_d();
    Dino getDino();
\
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::add_d *ui;
    Dino dino;
    QIntValidator int_val;
    QDoubleValidator double_val;
    QRegExpValidator regx_val;
};

#endif // ADD_D_H
