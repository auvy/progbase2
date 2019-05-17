#include "add_p.h"
#include "ui_add_p.h"

#include <QDebug>
#include <QMessageBox>

add_p::add_p(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_p)
{
    ui->setupUi(this);

    double_val.setNotation(QDoubleValidator::StandardNotation);

    QLocale locale(QLocale::C);
    double_val.setLocale(locale);

    ui->name->setValidator(&regx_val);
    ui->time->setValidator(&double_val);

}

add_p::~add_p()
{
    delete ui;
}

Per add_p::getPer()
{
    return this->per;
}

void add_p::on_buttonBox_accepted()
{
    if(ui->name->text().isEmpty() || ui->time->text().isEmpty())
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "Some fields are empty",
                    QMessageBox::Ok);
        return;
    }
    Per p;
    p.name = ui->name->text().toStdString();
    p.time = ui->time->text().toDouble();
    this->per = p;
    this->accept();
}

void add_p::on_buttonBox_rejected()
{
    this->reject();
}
