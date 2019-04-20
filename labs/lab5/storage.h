#pragma once

#include <vector>
#include <string>

#include "dino.h"
#include "period.h"
#include "csv.h"
#include "optional.h"

using std::string;
using std::vector;

class Storage
{
   const string dir_name_;

   vector<Dino> dinos_;
   vector<Per> pers_;

   static Dino rowToDino(const CsvRow &row);
   static CsvRow DinoToRow(const Dino &dino);

   static Per rowToPer(const CsvRow &row);
   static CsvRow PerToRow(const Per &pr);

   int getNewDinoId();
   int getNewPerId();


 public:
   Storage(const string & dir_name) : dir_name_(dir_name) { }

   bool load();
   bool save();
   // Dinos
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
};
