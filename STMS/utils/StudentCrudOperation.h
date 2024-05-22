#ifndef STUDENTCRUDOPERATION_H
#define STUDENTCRUDOPERATION_H

#include "../../library/sqlite3.h"
#include "DatabaseCrudOperation.h"
#include "Student.h"
// #include <sqlite3.h>
#include <string>

class StudentCrudOperation : public DatabaseCrudOperation<Student> {
public:
  StudentCrudOperation(const std::string &dbPath);
  ~StudentCrudOperation();

  void insert(Student &data) override;
  void update(int id, Student &data) override;
  void remove(int id) override;
  std::string read(int id) const override;

private:
  sqlite3 *db;
  void executeSQL(const std::string &sql) const;
};

#endif // STUDENTCRUDOPERATION_H