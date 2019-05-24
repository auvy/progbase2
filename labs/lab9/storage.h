
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>


#include "optional.h"
#include "dino.h"
#include "period.h"
#include "user.h"

using namespace std;

class Storage
{
 public:
   virtual ~Storage() {}


   virtual bool open() = 0;
   virtual bool close() = 0;
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


    //new functs
    virtual vector<Dino> getAllUserDino(int user_id) = 0;

    virtual optional<User> getUserAuth(string & username, string & password) = 0;

    virtual vector<Per> getAllDinoPer(int dino_id) = 0;
    virtual bool insertDinoPer(int dino_id, int per_id) = 0;
    virtual bool removeDinoPer(int dino_id, int per_id) = 0;
};
