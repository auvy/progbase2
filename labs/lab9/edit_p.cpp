#include "edit_p.h"
#include "ui_edit_p.h"

#include <QDebug>
#include <QMessageBox>

edit_p::edit_p(Per & per, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_p)
{
    ui->setupUi(this);

    double_val.setNotation(QDoubleValidator::StandardNotation);

    QLocale locale(QLocale::C);
    double_val.setLocale(locale);

    this->per.id = per.id;

    ui->name->setText(QString::fromUtf8(per.name.c_str()));
    ui->time->setValue(per.time);

    ui->name->setValidator(&regx_val);
}

edit_p::~edit_p()
{
    delete ui;
}

Per edit_p::getPer()
{
    return this->per;
}

void edit_p::on_buttonBox_accepted()
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
    this->per.name = ui->name->text().toStdString();
    this->per.time = ui->time->value();
    this->accept();
}

void edit_p::on_buttonBox_rejected()
{
    this->reject();
}
