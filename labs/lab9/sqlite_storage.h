#ifndef SQLITE_STORAGE_H
#define SQLITE_STORAGE_H

#include "storage.h"
#include <QSqlDatabase>
#include <QSqlQuery>

class SqliteStorage : public Storage
{
  const string dir_name_;
  QSqlDatabase db_;

public:
  SqliteStorage(const string & dir_name);

  bool open();
  bool close();
  // dinosaurs
  vector<Dino> getAllDinos(void);
  optional<Dino> getDinoById(int Dino_id);
  bool updateDino(const Dino &dvno);
  bool removeDino(int Dino_id);
  int insertDino(const Dino &dvno);


  // periods
  vector<Per> getAllPers(void);
  optional<Per> getPerById(int Per_id);
  bool updatePer(const Per &pr);
  bool removePer(int Per_id);
  int insertPer(const Per &pr);

  vector<Dino> getAllUserDino(int user_id);

  optional<User> getUserAuth(string & username, string & password);

  vector<Per> getAllDinoPer(int dino_id);
  bool insertDinoPer(int dino_id, int per_id);
  bool removeDinoPer(int dino_id, int per_id);
};

#endif // SQLITE_STORAGE_H
