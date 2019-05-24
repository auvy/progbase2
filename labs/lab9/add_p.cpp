#include "add_p.h"
#include "ui_add_p.h"
#include "dino.h"
#include "mainwindow.h"

#include <QDebug>
#include <QMessageBox>

#include <QFileDialog>
#include <QMessageBox>

#include <QSqlDatabase>
#include <QSqlQuery>


add_p::add_p(QWidget *parent, int did, Storage * storage) :
    QDialog(parent),
    ui(new Ui::add_p)
{
    ui->setupUi(this);
    did_ = did;
    storage_ = storage;
    this->fillWListPer();

//    double_val.setNotation(QDoubleValidator::StandardNotation);

//    QLocale locale(QLocale::C);
//    double_val.setLocale(locale);

//    ui->name->setText(QString::fromUtf8("Period"));
//    ui->time->setValue(100000);

//    ui->name->setValidator(&regx_val);

}

add_p::~add_p()
{
    delete ui;
}

Per add_p::getPer()
{
    return this->per;
}


void add_p::on_cancel_clicked()
{
    this->reject();
}


void add_p::fillWListPer()
{
    QVector<Per> pers = QVector<Per>::fromStdVector(storage_->getAllPers());
    QVariant var;
    for(Per & per : pers)
    {
        string stext = per.name;
        QString text = QString::fromStdString(stext);
        QListWidgetItem * new_item = new QListWidgetItem(text);
        var = QVariant::fromValue(per);
        new_item->setData(Qt::UserRole, var);
        ui->listWidget2_4->addItem(new_item);
    }
}

void add_p::on_add_clicked()
{
    QListWidgetItem * item = ui->listWidget2_4->currentItem();

    Per per = item->data(Qt::UserRole).value<Per>();

    int pid = per.id;
    int did = did_;


    QSqlQuery query;
    query.prepare("INSERT INTO links (dino_id, per_id) VALUES (:dino_id, :per_id)");

    query.bindValue(":dino_id", did);
    query.bindValue(":per_id", pid);

    if (!query.exec())
    {
        qDebug() << "addlink error" ;
        abort();
    }
    this->accept();
}


void add_p::on_listWidget2_4_itemSelectionChanged()
{
    QListWidgetItem * item = ui->listWidget2_4->currentItem();

    Per per = item->data(Qt::UserRole).value<Per>();

    ui->lselected_5->setText("Selected period:");
    ui->lplname_4->setText("Name:");
    ui->lpltime_4->setText("Length:");

    ui->lpname_4->setText(QString::fromUtf8(per.name.c_str()));
    ui->lptime_4->setText(QString::number(per.time));
}
