#ifndef ADD_P_H
#define ADD_P_H

#include <QDialog>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QRegExpValidator>

#include "period.h"
#include "dino.h"
#include "storage.h"

namespace Ui {
class add_p;
}

class add_p : public QDialog
{
    Q_OBJECT

public:
    explicit add_p(QWidget *parent = 0, int did = 0, Storage * storage = NULL);
    ~add_p();
    Per getPer();

private slots:
    void on_cancel_clicked();

    void on_add_clicked();

    void on_listWidget2_4_itemSelectionChanged();

    void fillWListPer();


private:
    Ui::add_p *ui;
    Per per;
    QIntValidator int_val;
    QDoubleValidator double_val;
    QRegExpValidator regx_val;
    int did_;
    Storage * storage_;
};

#endif // ADD_P_H
