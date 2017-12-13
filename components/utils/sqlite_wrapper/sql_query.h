#ifndef COMPONENTS_UTILS_SQLITE_WRAPPER_SQL_QUERY_H
#define COMPONENTS_UTILS_SQLITE_WRAPPER_SQL_QUERY_H

#include <stdint.h>
#include <string>
#include "sql_error.h"

struct sqlite3_stmt;

class SQLDatabase;

/**
 * Provides a means of executing and manipulating SQL statements
 */
class SQLQuery {
 public:
  explicit SQLQuery(SQLDatabase* db);
  ~SQLQuery();

  /**
   * Prepares the SQL query for executing
   * @param query the utf-8 string of SQL query
   * @return true if successfully
   */
  bool Prepare(const std::string& query);

  /**
   * Resets the binds of query for re-executing
   * @return true if successfully
   */
  bool Reset();

  /**
   * Deletes prepared SQL query
   */
  void Finalize();

  /**
   * Executes SQL query without make binds
   * @param query the utf-8 string of SQL query
   * @return true if successfull
   */
  bool Exec(const std::string& query);

  /**
   * Executes prepared SQL query and positions the query on the first record
   * @return true if successfull
   */
  bool Exec();

  /**
   * Retrieves the next record in the result, if available,
   * and positions the query on the retrieved record
   * @return true if record was retrieved successfully, false if a error was
   * or the result is empty or was retrieves last record
   */
  bool Next();

  /**
   * Binds null in the prepared query
   * @param pos position of param in the query
   */
  void Bind(int pos);

  /**
   * Binds int value in the prepared query.
   * @param pos position of param in the query
   * @param value value of param
   */
  void Bind(int pos, int value);

  /**
   * Binds int64_t value in the prepared query.
   * @param pos position of param in the query
   * @param value value of param
   */
  void Bind(int pos, int64_t value);

  /**
   * Binds double value in the prepared query.
   * @param pos position of param in the query
   * @param value value of param
   */
  void Bind(int pos, double value);

  /**
   * Binds bool value in the prepared query.
   * @param pos position of param in the query
   * @param value value of param
   */
  void Bind(int pos, bool value);

  /**
   * Binds string in the prepared query.
   * @param pos position of param in the query
   * @param value utf-8 string
   */
  void Bind(int pos, const std::string& value);

  /**
   * Gets value in the result record
   * @param pos position of value
   * @return boolean value
   */
  bool GetBoolean(int pos) const;

  /**
   * Gets value in the result record
   * @param pos position of value
   * @return integer value
   */
  int GetInteger(int pos) const;

  /**
   * Gets value in the result record
   * @param pos position of value
   * @return unsigned integer value
   */
  uint32_t GetUInteger(int pos) const;

  /**
   * Gets value in the result record
   * @param pos position of value
   * @return  int64_t value
   */
  int64_t GetLongInt(int pos) const;

  /**
   * Gets value in the result record
   * @param pos position of value
   * @return double value
   */
  double GetDouble(int pos) const;

  /**
   * Gets value in the result record
   * @param pos position of value
   * @return string value
   */
  std::string GetString(int pos) const;

  /**
   * Checks if value is null
   * @param pos position of value
   * @return true if value is null
   */
  bool IsNull(int pos) const;

  /**
   * Gets last id of insert row
   * @return id of insert row
   */
  int64_t LastInsertId() const;

  /**
   * Gets string of the query
   * @return string of the query
   */
  const std::string& query() const;

  /**
   * Gets information about the last error that occurred on the database
   * @return last error
   */
  SQLError LastError() const;

 private:
  /**
   * The instantiation of database
   */
  SQLDatabase& db_;

  /**
   * The string of query
   */
  std::string query_;

  /**
   * The SQL statement in SQLite
   */
  sqlite3_stmt* statement_;

  /**
   * The last error that occurred with this query
   */
  int error_;
};

#endif  // COMPONENTS_UTILS_SQLITE_WRAPPER_SQL_QUERY_H
