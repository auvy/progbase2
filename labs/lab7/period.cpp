#include "period.h"
#include <QDebug>

Per::Per() { }

Per::Per(int id, string name, double time)
{
    this->id = id;
    this->name = name;
    this->time = time;
}
