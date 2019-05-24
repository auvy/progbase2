#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "storage.h"
#include "csv_storage.h"
#include "sqlite_storage.h"


#include <QMainWindow>
#include <QtCore>
#include <QDebug>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QFileInfo>

#include "add_d.h"
#include "add_p.h"
#include "edit_d.h"
#include "edit_p.h"
#include "ui_mainwindow.h"


namespace Ui {class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
//    void onNew();

    void onOpen();    

    void on_add_clicked();

    void on_edit_clicked();

    void on_remove_clicked();

    void on_add2_clicked();

    void on_edit2_clicked();

    void on_remove2_clicked();

    void on_listWidget2_itemSelectionChanged();

    void on_listWidget_itemSelectionChanged();

private:
    Ui::MainWindow *ui;

    void loadfrom(QString & path);
    void fillWListDino(int uid);
    void fillWListPer(int did);
    bool fileWrite(QString & path, QString & data);
    bool defaultFile(QString & path);

    Storage * storage_; // <-- STORAGE
    int uid;
};

#endif // MAINWINDOW_H
