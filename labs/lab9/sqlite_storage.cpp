#include "sqlite_storage.h"

#include <QtSql>

#include <QCryptographicHash>
#include <QDebug>

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
    query.bindValue(":user_id", dvno.user_id);
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
    query.prepare("INSERT INTO dinosaurs (name, period, family, discovered, mass, user_id) VALUES (:name, :period, :family, :discovered, :mass, :user_id)");

    queryBindDino(dvno, query);

    if (!query.exec())
    {
        qDebug() << "adddino error:" << query.lastError();
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
    else return nullopt;
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
        query.prepare("DELETE FROM links WHERE id = :id");
        query.bindValue(":id", Per_id);

        if (!query.exec())
        {
            qDebug() << "deletePer error: " << query.lastError();
            return false;
        }

        if(query.numRowsAffected() == 0) {return false;}

        return true;



//    QSqlQuery query;
//    query.prepare("DELETE FROM periods WHERE id = :id");
//    query.bindValue(":id", Per_id);

//    if (!query.exec())
//    {
//        qDebug() << "deletePer error: " << query.lastError();
//        return false;
//    }

//    if(query.numRowsAffected() == 0) {return false;}

//    return true;

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





QString hashPassword(QString const & pass)
{
   QByteArray pass_ba = pass.toUtf8();
   QByteArray hash_ba = QCryptographicHash::hash(pass_ba, QCryptographicHash::Md5);
   QString pass_hash = QString(hash_ba.toHex());
   return pass_hash;
}





vector<Dino> SqliteStorage::getAllUserDino(int user_id)
{
    qDebug() << user_id;
    vector<Dino> dinos;
    QSqlQuery query;
    query.prepare("SELECT * FROM dinosaurs WHERE user_id = :user_id");
    query.bindValue(":user_id", user_id);
    if (!query.exec())
    {
        qDebug() << query.lastError().text();

        abort();
    }

    while (query.next())
    {
        Dino d = getDinoFromQuery(query);
        qDebug() << d.name.c_str();
        dinos.push_back(d);

    }
    return dinos;
}


//vector<Dino> SqliteStorage::getAllUserDino(int user_id)
//{
//   QSqlQuery query;
//   query.prepare("SELECT * FROM dinosaurs"
//                 "WHERE user_id = :user_id;");
//   query.bindValue(":user_id", user_id);
//   if (!query.exec())
//   {
//       QSqlError error = query.lastError();
//       throw error;
//   }
//   vector<Dino> data_v;
//   while (query.next())
//   {
//       Dino d;
//       dino.id = query.value("id").toInt();
//       dino.user_id = user_id;
//       dino.data = query.value("data").toString();
//       data_v.push_back(data);
//   }
//   return data_v;
//}



optional<User> SqliteStorage::getUserAuth(string & username, string & password)
{
    User user;
    QString fhash = hashPassword(QString::fromUtf8(password.c_str()));
    string passhash = fhash.toUtf8().constData();

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :un;");
    query.bindValue(":un", username.c_str());

    if(!query.exec())
    {
        qDebug() << "Unknown error: " << query.lastError();
        return nullopt;
    }

    if(query.next())
    {

            //if found user
            string uhash = query.value("password_hash").toString().toStdString();


            if(passhash == uhash)
            {
                user.id = query.value("id").toInt();
                qDebug() << user.id;
                user.username = query.value("username").toString().toStdString();
                qDebug() << user.username.c_str();
                user.password_hash = query.value("password_hash").toString().toStdString();
                qDebug() << user.password_hash.c_str();

                return user;
            }
            else
            {
                //uncorrect password
                qDebug() << "Uncorrect password. Try again. Error: " << query.lastError();
                User up;
                up.id = -1;
                return up;
            }
        }

    qDebug() << "Unknown user";
    User up;
    up.id = -2;
    return up;
}




vector<Per> SqliteStorage::getAllDinoPer(int dino_id)
{
//    qDebug() << user_id;
//    vector<Dino> dinos;
//    QSqlQuery query;
//    query.prepare("SELECT * FROM dinosaurs WHERE user_id = :user_id");
//    query.bindValue(":user_id", user_id);
//    if (!query.exec())
//    {
//        qDebug() << query.lastError().text();

//        abort();
//    }

//    while (query.next())
//    {
//        Dino d = getDinoFromQuery(query);
//        qDebug() << d.name.c_str();
//        dinos.push_back(d);

//    }
//    return dinos;
//}

    vector<Per> pers;

    QSqlQuery query;
    query.prepare("SELECT * FROM links WHERE dino_id = :dino_id");
    query.bindValue(":dino_id", dino_id);
    if (!query.exec())
    {
        qDebug() << query.lastError().text();

        abort();
    }

    while(query.next())
    {
        int pid = query.value("per_id").toInt();

        Per p = this->getPerById(pid).value();
        pers.push_back(p);
    }

    return pers;
}



bool SqliteStorage::insertDinoPer(int dino_id, int per_id)
{
    QSqlQuery query3;
    query3.prepare("INSERT INTO links VALUES (:dino_id, :per_id)");

    query3.bindValue(":dino_id", dino_id);
    query3.bindValue(":per_id" ,  per_id);

    qDebug () << query3.lastQuery();

    if (!query3.exec())
    {
        qDebug() << "addtoLinks error:" << query3.lastError();
        return false;
    }
    return true;
}


bool SqliteStorage::removeDinoPer(int dino_id, int per_id)
{
    QSqlQuery query3;

    query3.prepare("DELETE FROM links WHERE dino_id = :dino_id AND per_id = :per_id");
    query3.bindValue(":dino_id", dino_id);
    query3.bindValue(":per_id",  per_id);


    if (!query3.exec())
    {
        qDebug() << "addtoLinks error:" << query3.lastError();
        return false;
    }
    return true;

}





