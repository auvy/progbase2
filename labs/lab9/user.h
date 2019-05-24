#pragma once

#include <string>
#include <QMetaType>

using namespace std;
struct  User
{
    int id = 0;
    string username = "";
    string password_hash = "";

    User();
    User(int id, string username, string password_hash);
};
Q_DECLARE_METATYPE(User)

