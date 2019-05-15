#include "sqlite_storage.h"

#include <QtSql>

SqliteStorage::SqliteStorage(const string & dir_name) : dir_name_(dir_name)
{
    db_ = QSqlDatabase::addDatabase("QSQLITE");
}


bool SqliteStorage::open()
{
    QString path = QString::fromStdString(this->dir_name_) + "/data.sqlite";

    db_.setDatabaseName(path);    // set sqlite database file path

    bool connected = db_.open();  // open db connection

    if (!connected) {return false;}
    return true;
}

bool SqliteStorage::close()
{
    db_.close();
    return true;
}


Dino getDinoFromQuery(const QSqlQuery & query)
{
    int id = query.value("id").toInt();
    string name = query.value("name").toString().toStdString();
    string period = query.value("period").toString().toStdString();
    string family = query.value("family").toString().toStdString();
    int discovered = query.value("discovered").toInt();
    double mass = query.value("mass").toDouble();

    Dino d;
    d.id = id;
    d.name = name;
    d.per = period;
    d.fam = family;
    d.disc = discovered;
    d.mass = mass;

    return d;
}

void queryBindDino(const Dino &dvno, QSqlQuery & query)
{
    query.bindValue(":name", QString::fromStdString(dvno.name));
    query.bindValue(":period", QString::fromStdString(dvno.per));
    query.bindValue(":family", QString::fromStdString(dvno.fam));
    query.bindValue(":discovered", dvno.disc);
    query.bindValue(":mass", dvno.mass);
}

vector<Dino> SqliteStorage::getAllDinos(void)
{
    vector<Dino> dinos;
    QSqlQuery query("SELECT * FROM dinosaurs");
    while (query.next())
    {
       Dino d = getDinoFromQuery(query);
       dinos.push_back(d);
    }
    return dinos;
}

optional<Dino> SqliteStorage::getDinoById(int Dino_id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM dinosaurs WHERE id = :id");
    query.bindValue(":id", Dino_id);

    if (!query.exec())
    {
       qDebug() << "get dinosaur error:" << query.lastError();
       return nullopt;
    }
    if (query.next())
    {
        Dino d = getDinoFromQuery(query);
        return d;
   }
    else {return nullopt;}

}

bool SqliteStorage::updateDino(const Dino &dvno)
{
    QSqlQuery query;
    query.prepare("UPDATE dinosaurs SET name = :name, period = :period, family = :family, discovered = :discovered, mass = :mass WHERE id = :id");
    query.bindValue(":id", dvno.id);
    queryBindDino(dvno, query);

    if (!query.exec())
    {
        qDebug() << "updateDino error:" << query.lastError();
        return false;
    }
    if(query.numRowsAffected() == 0)
    {
        return false;
    }
    return true;
}

bool SqliteStorage::removeDino(int Dino_id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM dinosaurs WHERE id = :id");
    query.bindValue(":id", Dino_id);

    if (!query.exec())
    {
        qDebug() << "deleteDino error: " << query.lastError();
        return false;
    }

    if(query.numRowsAffected() == 0) {return false;}

    return true;

}

int SqliteStorage::insertDino(const Dino &dvno)
{
    QSqlQuery query;
    query.prepare("INSERT INTO dinosaurs (name, period, family, discovered, mass) VALUES (:name, :period, :family, :discovered, :mass)");

    queryBindDino(dvno, query);

    if (!query.exec())
    {
        qDebug() << "addPerson error:" << query.lastError();
        return 0;
    }

    QVariant var = query.lastInsertId();
    return var.toInt();
}






Per getPerFromQuery(const QSqlQuery & query)
{
    int id = query.value("id").toInt();
    string name = query.value("name").toString().toStdString();
    double time = query.value("time").toDouble();

    Per p;
    p.id = id;
    p.name = name;
    p.time = time;

    return p;
}

void queryBindDino(const Per &pr, QSqlQuery & query)
{
    query.bindValue(":name", QString::fromStdString(pr.name));
    query.bindValue(":time", pr.time);
}

vector<Per> SqliteStorage::getAllPers(void)
{
    vector<Per> pers;
    QSqlQuery query("SELECT * FROM periods");
    while (query.next())
    {
       Per p = getPerFromQuery(query);
       pers.push_back(p);
    }
    return pers;
}

optional<Per> SqliteStorage::getPerById(int Per_id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM periods WHERE id = :id");
    query.bindValue(":id", Per_id);

    if (!query.exec())
    {
       qDebug() << "get period error:" << query.lastError();
       return nullopt;
    }
    if (query.next())
    {
        Per p = getPerFromQuery(query);
        return p;
   }
    else {return nullopt;}

}

bool SqliteStorage::updatePer(const Per &pr)
{
    QSqlQuery query;
    query.prepare("UPDATE periods SET name = :name, time = :time WHERE id = :id");
    query.bindValue(":id", pr.id);
    queryBindDino(pr, query);

    if (!query.exec())
    {
        qDebug() << "updatePer error:" << query.lastError();
        return false;
    }
    if(query.numRowsAffected() == 0)
    {
        return false;
    }
    return true;
}

bool SqliteStorage::removePer(int Per_id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM periods WHERE id = :id");
    query.bindValue(":id", Per_id);

    if (!query.exec())
    {
        qDebug() << "deletePer error: " << query.lastError();
        return false;
    }

    if(query.numRowsAffected() == 0) {return false;}

    return true;

}

int SqliteStorage::insertPer(const Per &pr)
{
    QSqlQuery query;
    query.prepare("INSERT INTO periods (name, time) VALUES (:name, :time)");

    queryBindDino(pr, query);

    if (!query.exec())
    {
        qDebug() << "addPeriod error:" << query.lastError();
        return 0;
    }

    QVariant var = query.lastInsertId();
    return var.toInt();
}
