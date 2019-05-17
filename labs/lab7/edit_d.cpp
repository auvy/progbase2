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
    ui->per->setText(QString::fromUtf8(dino.per.c_str()));
    ui->disc->setText(QString::number(dino.disc));
    ui->mass->setText(QString::number(dino.mass));

    ui->name->setValidator(&regx_val);
    ui->fam->setValidator(&regx_val);
    ui->per->setValidator(&regx_val);
    ui->disc->setValidator(&int_val);
    ui->mass->setValidator(&double_val);
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
    if(ui->name->text().isEmpty() || ui->per->text().isEmpty() || ui->fam->text().isEmpty() || ui->disc->text().isEmpty() || ui->mass->text().isEmpty())
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "Some fields are empty",
                    QMessageBox::Ok);
        return;
    }
    this->dino.name = ui->name->text().toStdString();
    this->dino.per = ui->per->text().toStdString();
    this->dino.fam = ui->fam->text().toStdString();
    this->dino.disc = ui->disc->text().toInt();
    this->dino.mass = ui->mass->text().toDouble();
    this->accept();
}

void edit_d::on_buttonBox_2_rejected()
{
    this->reject();
}
