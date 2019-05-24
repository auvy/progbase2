#ifndef EDIT_D_H
#define EDIT_D_H

#include <QDialog>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QRegExpValidator>

#include "dino.h"

namespace Ui {
class edit_d;
}

class edit_d : public QDialog
{
    Q_OBJECT

public:
    explicit edit_d(Dino & dino, QWidget *parent = 0);
    ~edit_d();
    Dino getDino();

private slots:
    void on_buttonBox_2_accepted();

    void on_buttonBox_2_rejected();
    
private:
    Ui::edit_d *ui;
    QIntValidator int_val;
    QDoubleValidator double_val;
    QRegExpValidator regx_val;
    Dino dino;
};

#endif // EDIT_D_H
