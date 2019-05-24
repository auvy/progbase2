#pragma once

#include <string>
#include <QMetaType>
#include <QtCore>


using namespace std;
struct  Per
{
    int id = 0;
    string name = "";
    double time = 0.0;

    Per();
    Per(int id, string name, double time);
};
Q_DECLARE_METATYPE(Per)
