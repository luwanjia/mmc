#include "sql_database.h"
#include <sqlite3.h>

const std::string SQLDatabase::kInMemory = ":memory:";
const std::string SQLDatabase::kExtension = ".sqlite";

SQLDatabase::SQLDatabase()
    : conn_(NULL), databasename_(kInMemory), error_(SQLITE_OK) {}

SQLDatabase::SQLDatabase(const std::string& db_name)
    : conn_(NULL), databasename_(db_name + kExtension), error_(SQLITE_OK) {}

SQLDatabase::~SQLDatabase() {
  Close();
}

bool SQLDatabase::Open() {
  if (conn_)
    return true;
  error_ = sqlite3_open(get_path().c_str(), &conn_);
  if (error_ != SQLITE_OK) {
    conn_ = NULL;
  }
  return error_ == SQLITE_OK;
}

bool SQLDatabase::IsReadWrite() {
  const char* schema = "main";
  return sqlite3_db_readonly(conn_, schema) == 0;
}

void SQLDatabase::Close() {
  if (!conn_) {
    return;
  }

  error_ = sqlite3_close(conn_);
  if (error_ == SQLITE_OK) {
    conn_ = NULL;
  }
}

bool SQLDatabase::BeginTransaction() {
  return Exec("BEGIN TRANSACTION");
}

bool SQLDatabase::CommitTransaction() {
  return Exec("COMMIT TRANSACTION");
}

bool SQLDatabase::RollbackTransaction() {
  return Exec("ROLLBACK TRANSACTION");
}

bool SQLDatabase::Exec(const std::string& query) {
  error_ = sqlite3_exec(conn_, query.c_str(), NULL, NULL, NULL);
  return error_ == SQLITE_OK;
}

SQLError SQLDatabase::LastError() const {
  return SQLError(Error(error_));
}

sqlite3* SQLDatabase::conn() const {
  return conn_;
}

void SQLDatabase::set_path(const std::string& path) {
  path_ = path;
}

std::string SQLDatabase::get_path() const {
  return path_ + databasename_;
}

bool SQLDatabase::Backup() {
  return true;
}
