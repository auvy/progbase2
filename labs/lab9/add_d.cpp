#include "add_d.h"
#include "ui_add_d.h"


#include <QDebug>
#include <QMessageBox>

add_d::add_d(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_d)
{
    ui->setupUi(this);


    double_val.setNotation(QDoubleValidator::StandardNotation);

    QLocale locale(QLocale::C);
    double_val.setLocale(locale);

    ui->name->setText(QString::fromUtf8("Dinosaur"));
    ui->fam->setText(QString::fromUtf8("Family"));
    ui->disc->setValue(1000);
    ui->mass->setValue(100.0);


    ui->name->setValidator(&regx_val);
    ui->fam->setValidator(&regx_val);
}

add_d::~add_d()
{
    delete ui;
}

Dino add_d::getDino()
{
    return this->dino;
}

void add_d::on_buttonBox_accepted()
{
    if(ui->name->text().isEmpty() || ui->fam->text().isEmpty() || ui->disc->text().isEmpty() || ui->mass->text().isEmpty())
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "Some fields are empty",
                    QMessageBox::Ok);
        return;
    }
    Dino d;
    d.name = ui->name->text().toStdString();
    d.fam = ui->fam->text().toStdString();
    d.disc = ui->disc->value();
    d.mass = ui->mass->value();
    this->dino = d;
    this->accept();
}

void add_d::on_buttonBox_rejected()
{
    this->reject();
}
