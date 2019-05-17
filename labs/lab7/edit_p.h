#ifndef EDIT_P_H
#define EDIT_P_H

#include <QDialog>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QRegExpValidator>

#include "period.h"

namespace Ui {
class edit_p;
}

class edit_p : public QDialog
{
    Q_OBJECT

public:
    explicit edit_p(Per & per, QWidget *parent = 0);
    ~edit_p();
    Per getPer();


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::edit_p *ui;
    QIntValidator int_val;
    QDoubleValidator double_val;
    QRegExpValidator regx_val;
    Per per;
};

#endif // EDIT_P_H
