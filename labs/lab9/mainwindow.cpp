#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dino.h"
#include "period.h"
#include "auth.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

#include <QSqlDatabase>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    connect(ui->actionOption1, &QAction::triggered, this, &MainWindow::onNew);
    connect(ui->actionOption2, &QAction::triggered, this, &MainWindow::onOpen);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
}



//void MainWindow::onNew()
//{
//    QFileDialog dialog(this);
//    dialog.setFileMode(QFileDialog::Directory);
//    QString current_dir = QDir::currentPath();
//    QString default_name = "new_SqlStorage";
//    QString folder_path = dialog.getSaveFileName(
//        this,
//        "Select New Storage Folder",
//        current_dir + "/" + default_name,
//        "Folders");
//    if(!folder_path.isEmpty())
//    {
//        QDir().mkdir(folder_path);
//        bool success = this->defaultFile(folder_path);
//        if(!success)
//        {
//            ui->listWidget->clear();
//            ui->listWidget2->clear();
//            ui->add->setEnabled(false);
//            ui->add2->setEnabled(false);
//        }
//    }
//}

MainWindow::~MainWindow()
{
    delete this->storage_;
    delete ui;
}

void MainWindow::onOpen()
{
    qDebug() << "OPEN";
    QString file_path = QFileDialog::getExistingDirectory(
                this,              // parent
                "Open database",  // caption
                "",                // directory to start with
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);  // file name filter
    qDebug() << file_path;
    if(!file_path.isEmpty())
    {
        this->loadfrom(file_path);
    }

    auth * au = new auth(this, storage_);
    au->exec();

    ui->add->setEnabled(false);


    uid = au->getUID();
    qDebug() << uid;

    ui->listWidget->clear();
    ui->listWidget2->clear();


    this->fillWListDino(uid);
    if(uid > 0)
    {
        ui->add->setEnabled(true);
    }

}


void MainWindow::loadfrom(QString & path)
{
    std::string filenamestd;
    filenamestd = path.toUtf8().constData();

    SqliteStorage * sql_storage = new SqliteStorage(filenamestd);
\
    delete this->storage_;

    storage_ = sql_storage;



    if(this->storage_->open() == false)
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "Cannot open file!!!",
                    QMessageBox::Ok);
        return;
    }


}


void MainWindow::fillWListDino(int uid)
{
    QVector<Dino> dinos = QVector<Dino>::fromStdVector(storage_->getAllUserDino(uid));

    QVariant var;
    for(Dino & dino : dinos)
    {
        string stext = dino.name;
        QString text = QString::fromStdString(stext);
        QListWidgetItem * new_item = new QListWidgetItem(text);
        var = QVariant::fromValue(dino);
        new_item->setData(Qt::UserRole, var);
        ui->listWidget->addItem(new_item);
    }
}

void MainWindow::fillWListPer(int did)
{
    QVector<Per> pers =  QVector<Per>::fromStdVector(storage_->getAllDinoPer(did));

    QVariant var;
    for(Per & per : pers)
    {
        string stext = per.name;
        QString text = QString::fromStdString(stext);
        QListWidgetItem * new_item = new QListWidgetItem(text);
        var = QVariant::fromValue(per);
        new_item->setData(Qt::UserRole, var);
        ui->listWidget2->addItem(new_item);
    }
}





bool MainWindow::fileWrite(QString &path, QString &data)
{
    QFile file(path);

    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "Cannot create storage!!!",
                    QMessageBox::Ok);
        return false;
    }

    QTextStream out(&file);
    out << data;
    file.close();
    return true;
}

bool MainWindow::defaultFile(QString &path)
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString filename = path + "/data.sqlite";
    db.setDatabaseName(filename);
    bool connected = db.open();
    if (connected) {
        QSqlQuery query;
        query.prepare("CREATE TABLE dinosaurs (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                        " name TEXT NOT NULL,"
                        " period TEXT NOT NULL"
                        " family TEXT NOT NULL,"
                        " discovered INTEGER NOT NULL,"
                        " mass REAL NOT NULL,"
                        " user_id INTEGER,"
                        " FOREIGN KEY(user_id) REFERENCES users(id))");
        query.exec();


        query.prepare("CREATE TABLE periods ( id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                        " name TEXT NOT NULL,"
                        " time REAL NOT NULL )");
        query.exec();


        query.prepare("CREATE TABLE links ( id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                        " dino_id INTEGER NOT NULL,"
                        " per_id INTEGER NOT NULL,"
                        " FOREIGN KEY(per_id) REFERENCES periods(id),"
                        " FOREIGN KEY(dino_id) REFERENCES dinosaurs(id))");
        query.exec();


        query.prepare("CREATE TABLE users ( id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                        " username TEXT NOT NULL,"
                        " password_hash TEXT NOT NULL)");
        query.exec();


        query.prepare("INSERT INTO dinosaurs (name, period, family, discovered, mass, user_id) "
                      "VALUES ('Dino1', 'Cretaceous', 'Dino1f', 123.4, 1), "
                             "('Dino2', 'Triassic', 'Dino2f', 234.0, 2)");
        query.exec();

        query.prepare("INSERT INTO periods (name, time) "
                      "VALUES ('Cretaceous', 145000000),"
                      "('Triassic, 251900000)");
        query.exec();


        query.prepare("INSERT INTO users (username, password_hash) "
                      "VALUES ('qwerty', 'cf21666101224b0efdbc7226ee5ee36e'),"
                      "('John_Yeehaw', 'd8bb63b6f25ce2e9b6f87cf08c4b8343')");
        query.exec();


        query.prepare("INSERT INTO links (dino_id, per_id) "
                      "VALUES (1, 1),"
                      "(2, 2)");
        query.exec();

        db.close();





//        QString filename = path + "/data.sqlite";
//        QString data = "1,Dino,Period,Family,999,999.0";
//        bool dinow = this->fileWrite(filename, data);

//        QString filename2 = path + "/data2.csv";
//        QString data2 = "1,Period,999.0";
//        bool perw = this->fileWrite(filename2, data2);


        this->loadfrom(path);
        return true;

//        else return false;
}
    else return false;

}











void MainWindow::on_add_clicked()
{
    add_d window(this);
    if(window.exec())
    {
        QVariant var;
        Dino dino = window.getDino();
        dino.user_id = uid;
        dino.id = this->storage_->insertDino(dino);

        QListWidgetItem * item = new QListWidgetItem;
        var.setValue(dino); 
        const QString name = QString::fromUtf8(dino.name.c_str());
        item->setText(name);
        item->setData(Qt::UserRole, var);
        ui->listWidget->addItem(item);
    }
}








void MainWindow::on_edit_clicked()
{
    QList<QListWidgetItem *> items = ui->listWidget->selectedItems();
    Dino dino;
    QVariant var;

    foreach (QListWidgetItem * item, items)
    {
        dino = item->data(Qt::UserRole).value<Dino>();
    }

    edit_d window(dino, this);
    
    if(window.exec())
    {
        dino = window.getDino();
        this->storage_->updateDino(dino);

        foreach (QListWidgetItem * item, items)
        {
            var.setValue(dino);
            const QString name = QString::fromUtf8(dino.name.c_str());
            item->setText(name);
            item->setData(Qt::UserRole, var);
        }
    }

//    this->storage_->close();
}

void MainWindow::on_remove_clicked()
{
    QMessageBox::StandardButton remove;
       remove = QMessageBox::question(
           this,
           "Remove",
           "Are you sure?",
           QMessageBox::Yes|QMessageBox::No);

    if (remove == QMessageBox::Yes)
    {
           QList<QListWidgetItem *> items = ui->listWidget->selectedItems();
           Dino dino;
           foreach(QListWidgetItem * item, items)
           {
               dino = item->data(Qt::UserRole).value<Dino>();

               this->storage_->removeDino(dino.id);

               delete ui->listWidget->takeItem(ui->listWidget->row(item));
           }
    }
//    this->storage_->close();
}

void MainWindow::on_add2_clicked()
{
    QListWidgetItem * qdino = ui->listWidget->currentItem();
    Dino d = qdino->data(Qt::UserRole).value<Dino>();
    int id = d.id;
    add_p window(this, id, storage_);
    if(window.exec())
    {
//        QVariant var;
//        Per per = window.getPer();
//        per.id = this->storage_->insertPer(per);

//        QListWidgetItem * item = new QListWidgetItem;
//        var.setValue(per);
//        const QString name = QString::fromUtf8(per.name.c_str());
//        item->setText(name);
//        item->setData(Qt::UserRole, var);
//        ui->listWidget2->addItem(item);
    }
//    this->storage_->close();
}

void MainWindow::on_edit2_clicked()
{
    QList<QListWidgetItem *> items = ui->listWidget2->selectedItems();
    Per per;
    QVariant variant;

    foreach (QListWidgetItem * item, items)
    {
        per = item->data(Qt::UserRole).value<Per>();
    }
    edit_p window(per, this);
    
    if(window.exec())
    {
        per = window.getPer();
        this->storage_->updatePer(per);
        
        foreach (QListWidgetItem * item, items)
        {
            variant.setValue(per);
            const QString name = QString::fromUtf8(per.name.c_str());
            item->setText(name);
            item->setData(Qt::UserRole, variant);
        }
    }

//    this->storage_->close();
}

void MainWindow::on_remove2_clicked()
{
    QMessageBox::StandardButton remove;
       remove = QMessageBox::question(
           this,
           "Remove",
           "Are you sure?",
           QMessageBox::Yes|QMessageBox::No);

    if (remove == QMessageBox::Yes)
    {
        QListWidgetItem * qdino = ui->listWidget->currentItem();
        Dino d = qdino->data(Qt::UserRole).value<Dino>();
        int did = d.id;

        QListWidgetItem * iper = ui->listWidget2->currentItem();
        Per per = iper->data(Qt::UserRole).value<Per>();
        int pid = per.id;

        if(!this->storage_->removeDinoPer(did, pid))
        {
            qDebug() << "Something went wrong";
        }

        delete ui->listWidget2->takeItem(ui->listWidget2->row(iper));
    }

//    this->storage_->close();
}

void MainWindow::on_listWidget2_itemSelectionChanged()
{
    QListWidgetItem * item = ui->listWidget2->currentItem();

    ui->edit2->setEnabled(true);
    ui->remove2->setEnabled(true);

    Per per = item->data(Qt::UserRole).value<Per>();

    ui->lselected_2->setText("Selected period:");
    ui->lplname->setText("Name:");
    ui->lpltime->setText("Length:");

    ui->lpname->setText(QString::fromUtf8(per.name.c_str()));
    ui->lptime->setText(QString::number(per.time));
}

void MainWindow::on_listWidget_itemSelectionChanged()
{
    QListWidgetItem * item = ui->listWidget->currentItem();

    ui->edit->setEnabled(true);
    ui->remove->setEnabled(true);

    Dino dino = item->data(Qt::UserRole).value<Dino>();

    ui->lselected->setText("Selected dino:");
    ui->ldlname->setText("Name:");
    ui->ldlfam->setText("Family:");
    ui->ldldisc->setText("Discovered:");
    ui->ldlmass->setText("Mass");

    ui->ldname->setText(QString::fromUtf8(dino.name.c_str()));
    ui->ldfam-> setText(QString::fromUtf8(dino.fam.c_str()));
    ui->lddisc->setText(QString::number(dino.disc));
    ui->ldmass->setText(QString::number(dino.mass));
    ui->listWidget2->clear();

    this->fillWListPer(dino.id);
    ui->add2->setEnabled(true);
//    }
    //now this to listselect1

}
