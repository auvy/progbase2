#pragma once

#include <QtCore>
#include <QtXml>

#include <QString>
#include <QFile>
#include <QtXml>
#include <QDebug>
#include <QTextStream>
#include <string>
#include <vector>


#include "dino.h"
#include "period.h"
#include "optional.h"
#include "storage.h"

using std::string;
using std::vector;

class XmlStorage : public Storage
{
   const string dir_name_;

   vector<Dino> dinos_;
   vector<Per> pers_;

   int getNewDinoId();
   int getNewPerId();


 public:
   XmlStorage(const string & dir_name) : dir_name_(dir_name) { }

   bool open();
   bool close();

   vector<Dino> getAllDinos();
   optional<Dino> getDinoById(int Dino_id);
   bool updateDino(const Dino &dvno);
   bool removeDino(int Dino_id);
   int insertDino(const Dino &dvno);


   vector<Per> getAllPers();
   optional<Per> getPerById(int Per_id);
   bool updatePer(const Per &pr);
   bool removePer(int Per_id);
   int insertPer(const Per &pr);

   bool loadfromstr(string filename, int strtype);

};


