#include "sql_query.h"
#include <sqlite3.h>
#include <cassert>
#include "sql_database.h"

SQLQuery::SQLQuery(SQLDatabase* db)
    : db_(*db), query_(""), statement_(NULL), error_(SQLITE_OK) {}

SQLQuery::~SQLQuery() {
  Finalize();
}

bool SQLQuery::Prepare(const std::string& query) {
  Finalize();

  if (statement_)
    return false;
  error_ = sqlite3_prepare(
      db_.conn(), query.c_str(), query.length(), &statement_, NULL);
  query_ = query;
  return error_ == SQLITE_OK;
}

bool SQLQuery::Exec() {
  error_ = sqlite3_step(statement_);
  return error_ == SQLITE_ROW || error_ == SQLITE_DONE;
}

bool SQLQuery::Next() {
  error_ = sqlite3_step(statement_);
  return error_ == SQLITE_ROW;
}

bool SQLQuery::Reset() {
  error_ = sqlite3_reset(statement_);
  return error_ == SQLITE_OK;
}

void SQLQuery::Finalize() {
  error_ = sqlite3_finalize(statement_);
  if (error_ == SQLITE_OK) {
    statement_ = NULL;
  }
}

bool SQLQuery::Exec(const std::string& query) {
  query_ = query;
  error_ = sqlite3_exec(db_.conn(), query.c_str(), NULL, NULL, NULL);
  return error_ == SQLITE_OK;
}

void SQLQuery::Bind(int pos, int value) {
  // In SQLite the number of position for binding starts since 1.
  error_ = sqlite3_bind_int(statement_, pos + 1, value);
}

void SQLQuery::Bind(int pos, int64_t value) {
  // In SQLite the number of position for binding starts since 1.
  error_ = sqlite3_bind_int64(statement_, pos + 1, value);
}

void SQLQuery::Bind(int pos, double value) {
  // In SQLite the number of position for binding starts since 1.
  error_ = sqlite3_bind_double(statement_, pos + 1, value);
}

void SQLQuery::Bind(int pos, bool value) {
  Bind(pos, static_cast<int>(value));
}

void SQLQuery::Bind(int pos, const std::string& value) {
  // In SQLite the number of position for binding starts since 1.
  error_ = sqlite3_bind_text(
      statement_, pos + 1, value.c_str(), value.length(), SQLITE_TRANSIENT);
}

bool SQLQuery::GetBoolean(int pos) const {
  return static_cast<bool>(GetInteger(pos));
}

int SQLQuery::GetInteger(int pos) const {
  return sqlite3_column_int(statement_, pos);
}

uint32_t SQLQuery::GetUInteger(int pos) const {
  return static_cast<uint32_t>(sqlite3_column_int64(statement_, pos));
}

int64_t SQLQuery::GetLongInt(int pos) const {
  return static_cast<int64_t>(sqlite3_column_int64(statement_, pos));
}

double SQLQuery::GetDouble(int pos) const {
  return sqlite3_column_double(statement_, pos);
}

std::string SQLQuery::GetString(int pos) const {
  const unsigned char* str = sqlite3_column_text(statement_, pos);
  return str ? reinterpret_cast<const char*>(str) : "";
}

const std::string& SQLQuery::query() const {
  // TODO(KKolodiy): may return string query with value of arguments
  return query_;
}

bool SQLQuery::IsNull(int pos) const {
  return sqlite3_column_type(statement_, pos) == SQLITE_NULL;
}

void SQLQuery::Bind(int pos) {
  // In SQLite the number of position for binding starts since 1.
  error_ = sqlite3_bind_null(statement_, pos + 1);
}

SQLError SQLQuery::LastError() const {
  return SQLError(Error(error_));
}

int64_t SQLQuery::LastInsertId() const {
  return sqlite3_last_insert_rowid(db_.conn());
}
