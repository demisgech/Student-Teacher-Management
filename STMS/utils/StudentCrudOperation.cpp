#include "StudentCrudOperation.h"
#include <iostream>
#include <sqlite3.h>
#include <stdexcept>
using namespace std;

static int callback(void *data, int argc, char **argv, char **azColName) {
  static bool headersPrinted = false;
  if (!headersPrinted) {
    for (int i = 0; i < argc; i++) {
      std::cout << azColName[i] << "\t";
    }
    std::cout << std::endl;
    headersPrinted = true;
  }

  for (int i = 0; i < argc; i++) {
    std::cout << (argv[i] ? argv[i] : "NULL") << "\t";
  }
  std::cout << std::endl;
  return 0;
}

StudentCrudOperation::StudentCrudOperation(const string &dbPath) {
  if (sqlite3_open(dbPath.c_str(), &db)) {
    string errorMsg = "Can't open database: " + string(sqlite3_errmsg(db));
    sqlite3_close(db);
    throw runtime_error(errorMsg);
  }
}

StudentCrudOperation::~StudentCrudOperation() {
  if (db)
    sqlite3_close(db);
}

void StudentCrudOperation::executeSQL(const string &sql) const {
  char *errMsg = nullptr;
  if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &errMsg) != SQLITE_OK) {
    string error = "SQL error: " + string(errMsg);
    sqlite3_free(errMsg);
    throw runtime_error(error);
  }
}

void StudentCrudOperation::insert(Student &data) {
  cout << endl << "**** Welcome to register a Student ****" << endl;
  cout << "Please, enter your info. carefully!" << endl;
  cout << "name:";
  string name;
  cin >> name;
  // getline(cin, name);
  data.setName(name);

  cout << "phoneNumber:";
  string phoneNumber;
  cin >> phoneNumber;
  // getline(cin, phoneNumber);
  data.setPhoneNumber(phoneNumber);

  cout << "Email:";
  string email;
  cin >> email;
  // getline(cin, email);
  data.setEmail(email);

  cout << "age:";
  int age;
  cin >> age;
  data.setAge(age);

  cout << "CGPA:";
  double cgpa;
  cin >> cgpa;
  data.setCGPA(cgpa);

  string sql = "INSERT INTO Students"
               "(name,phoneNumber,email,age,cgpa) VALUES ('" +
               data.getName() + "','" + data.getPhoneNumber() + "','" +
               data.getEmail() + "','" + to_string(data.getAge()) + "','" +
               to_string(data.getCGPA()) + "');";
  executeSQL(sql);
  cout << endl << "Successfully registered!!!" << endl;
}

void StudentCrudOperation::update(int id, Student &data) {
  // You can update anything and everything ...
  cout << endl << "**** Name updating ... ****" << endl << "New Name:";
  string name;
  cin >> name;
  // getline(cin, name);
  data.setName(name);
  string sql = "UPDATE Students SET name = '" + data.getName() +
               "' WHERE id = " + to_string(id) + ";";
  executeSQL(sql);
  cout << "Successfuly Updated!!!" << endl;
}

void StudentCrudOperation::remove(int id) {
  string sql = "DELETE FROM Students WHERE id = " + to_string(id) + ";";
  executeSQL(sql);
  cout << endl << "Successfully deleted!!!" << endl;
}

void StudentCrudOperation::read(int id) const {
  string sql = "SELECT * FROM Students WHERE id = " + to_string(id) + ";";
  executeSQL(sql);
}

void StudentCrudOperation::readAll() {
  string sql = "SELECT * FROM Students";
  executeSQL(sql);
}

void StudentCrudOperation::createTable() {
  const char *sql_create_table =
      "CREATE TABLE IF NOT EXISTS Students ( id INTEGER PRIMARY KEY "
      "AUTOINCREMENT,name TEXT "
      "NOT NULL, age INTEGER, phoneNumber TEXT,email TEXT gender TEXT,cgpa "
      "REAL NOT NULL);";
  return executeSQL(sql_create_table);
}
