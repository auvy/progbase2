#include "dino.h"
#include <QDebug>

Dino::Dino() { }

Dino::Dino(int id, string name, string per, string fam, int disc, double mass, int user_id)
{
    this->id = id;
    this->name = name;
    this->per = per;
    this->fam = fam;
    this->disc = disc;
    this->mass = mass;
    this->user_id = user_id;
}
