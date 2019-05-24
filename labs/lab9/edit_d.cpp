#include "edit_d.h"
#include "ui_edit_d.h"

#include <QDebug>
#include <QMessageBox>

edit_d::edit_d(Dino & dino, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_d)
{
    ui->setupUi(this);

    double_val.setNotation(QDoubleValidator::StandardNotation);

    QLocale locale(QLocale::C);
    double_val.setLocale(locale);


    this->dino.id = dino.id;

    ui->name->setText(QString::fromUtf8(dino.name.c_str()));
    ui->fam->setText(QString::fromUtf8(dino.fam.c_str()));
    ui->disc->setValue(dino.disc);
    ui->mass->setValue(dino.mass);

    ui->name->setValidator(&regx_val);
    ui->fam->setValidator(&regx_val);
}

edit_d::~edit_d()
{
    delete ui;
}


Dino edit_d::getDino()
{
    return this->dino;
}

void edit_d::on_buttonBox_2_accepted()
{
    if(ui->name->text().isEmpty()  || ui->fam->text().isEmpty() || ui->disc->text().isEmpty() || ui->mass->text().isEmpty())
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "Some fields are empty",
                    QMessageBox::Ok);
        return;
    }
    this->dino.name = ui->name->text().toStdString();
    this->dino.fam = ui->fam->text().toStdString();
    this->dino.disc = ui->disc->value();
    this->dino.mass = ui->mass->value();
    this->accept();
}

void edit_d::on_buttonBox_2_rejected()
{
    this->reject();
}
