#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dino.h"
#include "period.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionOption1, &QAction::triggered, this, &MainWindow::onNew);
    connect(ui->actionOption2, &QAction::triggered, this, &MainWindow::onOpen);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
}



void MainWindow::onNew()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString current_dir = QDir::currentPath();
    QString default_name = "new_CsvStorage";
    QString folder_path = dialog.getSaveFileName(
        this,
        "Select New Storage Folder",
        current_dir + "/" + default_name,
        "Folders");
    if(!folder_path.isEmpty())
    {
        QDir().mkdir(folder_path);
        bool success = this->defaultFile(folder_path);
        if(!success)
        {
            ui->listWidget->clear();
            ui->listWidget2->clear();
            ui->add->setEnabled(false);
            ui->add2->setEnabled(false);
        }
    }
}

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
                "Dialog Caption",  // caption
                "",                // directory to start with
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);  // file name filter
    qDebug() << file_path;
    if(!file_path.isEmpty())
    {
        this->loadfrom(file_path);
    }
}


void MainWindow::loadfrom(QString & path)
{
    std::string filenamestd;
    CsvStorage * csv_storage;
//    QFileInfo check_file(path);
//    if (check_file.exists() && check_file.isFile())
//    {

//    }
//    else
//    {
//        QDir().mkdir(path);
//        bool success = this->defaultFile(path);
//        if(!success)
//        {
//            ui->listWidget->clear();
//            ui->listWidget2->clear();
//            ui->add->setEnabled(false);
//            ui->add2->setEnabled(false);
//        }
//        return;
//    }



    filenamestd = path.toUtf8().constData();
    csv_storage = new CsvStorage(filenamestd);
    delete this->storage_;

    storage_ = csv_storage;



    if(storage_->load(filenamestd) == false)
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "Cannot open file!!!",
                    QMessageBox::Ok);
        return;
    }

    ui->listWidget->clear();
    this->fillWListDino();
    ui->add->setEnabled(true);

    ui->listWidget2->clear();
    this->fillWListPer();
    ui->add2->setEnabled(true);
}


void MainWindow::fillWListDino()
{
    QVector<Dino> dinos = QVector<Dino>::fromStdVector(storage_->getAllDinos());

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

void MainWindow::fillWListPer()
{
    QVector<Per> pers =  QVector<Per>::fromStdVector(storage_->getAllPers());
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

        QString filename = path + "/data.csv";
        QString data = "1,Dino,Period,Family,999,999.0";
        bool dinow = this->fileWrite(filename, data);

        QString filename2 = path + "/data2.csv";
        QString data2 = "1,Period,999.0";
        bool perw = this->fileWrite(filename2, data2);

        if(dinow == true && perw == true)
        {
            this->loadfrom(path);
            return true;
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
        dino.id = this->storage_->insertDino(dino);

        QListWidgetItem * item = new QListWidgetItem;
        var.setValue(dino); 
        const QString name = QString::fromUtf8(dino.name.c_str());
        item->setText(name);
        item->setData(Qt::UserRole, var);
        ui->listWidget->addItem(item);
    }
    this->storage_->save();
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

    this->storage_->save();
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
    this->storage_->save();
}

void MainWindow::on_add2_clicked()
{
    add_p window(this);
    if(window.exec())
    {
        QVariant var;
        Per per = window.getPer();
        per.id = this->storage_->insertPer(per);

        QListWidgetItem * item = new QListWidgetItem;
        var.setValue(per);
        const QString name = QString::fromUtf8(per.name.c_str());
        item->setText(name);
        item->setData(Qt::UserRole, var);
        ui->listWidget2->addItem(item);
    }
    this->storage_->save();
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

    this->storage_->save();
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
           QList<QListWidgetItem *> items = ui->listWidget2->selectedItems();
           Per per;
           foreach(QListWidgetItem * item, items)
           {
               per = item->data(Qt::UserRole).value<Per>();

               this->storage_->removePer(per.id);

               delete ui->listWidget2->takeItem(ui->listWidget2->row(item));
           }
    }

    this->storage_->save();
}

void MainWindow::on_listWidget2_itemSelectionChanged()
{
    QList<QListWidgetItem *> items = ui->listWidget2->selectedItems();
    if(items.size() != 1)
    {
        ui->lselected_2->setText("");
        ui->lplname->setText("");
        ui->lpltime->setText("");


        ui->lpname->setText("");
        ui->lptime->setText("");

        if(items.size() == 0)
        {
            ui->edit2->setEnabled(false);
            ui->remove2->setEnabled(false);
        }
        else
        {
            ui->edit2->setEnabled(false);
            ui->remove2->setEnabled(true);
        }

    }
    else
    {

        ui->edit2->setEnabled(true);
        ui->remove2->setEnabled(true);
        foreach (QListWidgetItem * item, items)
        {
            Per per = item->data(Qt::UserRole).value<Per>();

            ui->lselected_2->setText("Selected period:");
            ui->lplname->setText("Name:");
            ui->lpltime->setText("Length:");

            ui->lpname->setText(QString::fromUtf8(per.name.c_str()));
            ui->lptime->setText(QString::number(per.time));
        }

    }
}

void MainWindow::on_listWidget_itemSelectionChanged()
{
    QList<QListWidgetItem *> items = ui->listWidget->selectedItems();
    if(items.size() != 1)
    {
        ui->lselected->setText("");
        ui->ldlname->setText("");
        ui->ldlper->setText("");
        ui->ldlfam->setText("");
        ui->ldldisc->setText("");
        ui->ldlmass->setText("");

        ui->ldname->setText("");
        ui->ldper->setText("");
        ui->ldfam->setText("");
        ui->lddisc->setText("");
        ui->ldmass->setText("");

        if(items.size() == 0)
        {
            ui->edit->setEnabled(false);
            ui->remove->setEnabled(false);
        }
        else
        {
            ui->edit->setEnabled(false);
            ui->remove->setEnabled(true);
        }

    }
    else
    {

        ui->edit->setEnabled(true);
        ui->remove->setEnabled(true);
        foreach (QListWidgetItem * item, items)
        {
            Dino dino = item->data(Qt::UserRole).value<Dino>();

            ui->lselected->setText("Selected dino:");
            ui->ldlname->setText("Name:");
            ui->ldlper->setText("Period:");
            ui->ldlfam->setText("Family:");
            ui->ldldisc->setText("Discovered:");
            ui->ldlmass->setText("Mass");


            ui->ldname->setText(QString::fromUtf8(dino.name.c_str()));
            ui->ldper-> setText(QString::fromUtf8(dino.per.c_str()));
            ui->ldfam-> setText(QString::fromUtf8(dino.fam.c_str()));
            ui->lddisc->setText(QString::number(dino.disc));
            ui->ldmass->setText(QString::number(dino.mass));
        }

    }
}
