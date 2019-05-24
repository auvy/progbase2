#ifndef AUTH_H
#define AUTH_H

#include <QDialog>
#include "storage.h"

namespace Ui {
class auth;
}

class auth : public QDialog
{
    Q_OBJECT

public:
    explicit auth(QWidget *parent = 0, Storage * stor = NULL);
    int getUID();
    ~auth();

private slots:

    QString hashPassword(QString const & pass);

    void on_loginb_clicked();

    void on_back_clicked();

    void on_create_clicked();

private:
    Ui::auth *ui;

    Storage * astorage_; // <-- STORAGE

    int uid = -3;
};

#endif // AUTH_H
