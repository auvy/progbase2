#ifndef ADD_P_H
#define ADD_P_H

#include <QDialog>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QRegExpValidator>

#include "period.h"

namespace Ui {
class add_p;
}

class add_p : public QDialog
{
    Q_OBJECT

public:
    explicit add_p(QWidget *parent = 0);
    ~add_p();
    Per getPer();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();


private:
    Ui::add_p *ui;
    Per per;
    QIntValidator int_val;
    QDoubleValidator double_val;
    QRegExpValidator regx_val;
};

#endif // ADD_P_H
