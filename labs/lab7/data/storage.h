
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "optional.h"
#include "dino.h"
#include "period.h"

using namespace std;

class Storage
{
 public:
   virtual bool load() = 0;
   virtual bool save() = 0;
   // dinosaurs
   virtual vector<Dino> getAllDinos(void) = 0;
   virtual optional<Dino> getDinoById(int Dino_id) = 0;
   virtual bool updateDino(const Dino &dvno) = 0;
   virtual bool removeDino(int Dino_id) = 0;
   virtual int insertDino(const Dino &dvno) = 0;


   // periods
   virtual vector<Per> getAllPers(void) = 0;
   virtual optional<Per> getPerById(int Per_id) = 0;
   virtual bool updatePer(const Per &pr) = 0;
   virtual bool removePer(int Per_id) = 0;
   virtual int insertPer(const Per &pr) = 0;
};
