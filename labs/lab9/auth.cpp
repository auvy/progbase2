#include "auth.h"
#include "ui_auth.h"

#include <QDebug>
#include <QMessageBox>
#include "sqlite_storage.h"
#include <QSqlQuery>
#include <QtSql>
#include <QSqlDatabase>

#include <QCryptographicHash>
#include <QDebug>

auth::auth(QWidget *parent, Storage * stor) :
    QDialog(parent),
    ui(new Ui::auth)
{
    ui->setupUi(this);
    astorage_ = stor;
}

auth::~auth()
{
    delete ui;
}

int auth::getUID()
{
    int a = uid;
    return a;
}


void auth::on_loginb_clicked()
{
    if(ui->password->text().isEmpty() || ui->login->text().isEmpty())
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "Some fields are empty",
                    QMessageBox::Ok);
        return;
    }

    string username = ui->login->text().toStdString().c_str();
    string password = ui->password->text().toStdString().c_str();

    if(astorage_->getUserAuth(username, password) != nullopt)
    {
        if(astorage_->getUserAuth(username, password).value().id == -1)
        {
            QMessageBox::warning(
                        this,
                        "WARNING",
                        "Uncorrect password. Try again",
                        QMessageBox::Ok);
            return;
        }
        else if(astorage_->getUserAuth(username, password).value().id == -2)
        {
            QMessageBox::warning(
                        this,
                        "WARNING",
                        "Unknown user. Try again",
                        QMessageBox::Ok);
            return;
        }
        else
        {
            uid = astorage_->getUserAuth(username, password).value().id;

            qDebug() << uid;

            qDebug() << "ok";

            this->accept();
        }
    }
    else if(astorage_->getUserAuth(username, password) == nullopt)
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "Something went terribly wrong",
                    QMessageBox::Ok);
        return;
    }

}


void auth::on_back_clicked()
{
    this->reject();
}

QString auth::hashPassword(QString const & pass)
{
   QByteArray pass_ba = pass.toUtf8();
   QByteArray hash_ba = QCryptographicHash::hash(pass_ba, QCryptographicHash::Md5);
   QString pass_hash = QString(hash_ba.toHex());
   return pass_hash;
}




void auth::on_create_clicked()
{
    if(ui->password->text().isEmpty() || ui->login->text().isEmpty())
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "Some fields are empty",
                    QMessageBox::Ok);
        return;
    }

    string username = ui->login->text().toStdString().c_str();
    string password = ui->password->text().toStdString().c_str();

    QString fhash = hashPassword(QString::fromUtf8(password.c_str()));
    string passhash = fhash.toUtf8().constData();

    if(astorage_->getUserAuth(username, password).value().id == -1)
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "This login is taken",
                    QMessageBox::Ok);
        return;
    }


    QSqlQuery query;

    query.prepare("INSERT INTO users (username, password_hash) VALUES (:username, :password_hash)");

    query.bindValue(":username", username.c_str());
    query.bindValue(":password_hash" ,  passhash.c_str());

    if (!query.exec())
    {
        qDebug() << "addtoUsers error:" << query.lastError();
        abort();
    }

    QVariant var = query.lastInsertId();
    uid = var.toInt();

    this->accept();
}
