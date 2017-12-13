#ifndef COMPONENTS_UTILS_SQLITE_WRAPPER_SQL_DATABASE_H
#define COMPONENTS_UTILS_SQLITE_WRAPPER_SQL_DATABASE_H

#include <string>
#include "sql_error.h"

struct sqlite3;

class SQLQuery;

/**
 * Represents a connection to a database.
 */
class SQLDatabase {
 public:
  SQLDatabase();
  explicit SQLDatabase(const std::string& filename);
  ~SQLDatabase();

  /**
   * Opens connection to the temporary in-memory database
   * @return true if successfully
   */
  bool Open();

  /**
   * Closes connection to the database
   */
  void Close();

  /**
   * Begins a transaction on the database
   * @return true if successfully
   */
  bool BeginTransaction();

  /**
   * Commits a transaction to the database
   * @return true if successfully
   */
  bool CommitTransaction();

  /**
   * Rolls back a transaction on the database
   * @return true if successfully
   */
  bool RollbackTransaction();

  /**
   * Gets information about the last error that occurred on the database
   * @return last error
   */
  SQLError LastError() const;

  /**
   * Sets path to database
   * If the database is already opened then need reopen it
   */
  void set_path(const std::string& path);

  /**
   * @brief get_path databse location path.
   *
   * @return the path to the database location
   */
  std::string get_path() const;

  /**
}  // namespace dbms
}  // namespace utils

   * Checks if database is read/write
   * @return true if database is read/write
   */
  bool IsReadWrite();

  /**
   * Call backup for opened DB
   */
  bool Backup();

 protected:
  /**
   * Gets connection to the SQLite database
   * @return pointer to connection
   */
  sqlite3* conn() const;

 private:
  /**
   * The connection to the SQLite database
   */
  sqlite3* conn_;

  /**
   * The file path of database
   */
  std::string path_;

  /**
   * The filename of database
   */
  std::string databasename_;

  /**
   * The last error that occurred on the database
   */
  int error_;

  /**
   *  The temporary in-memory database
   *  @see SQLite manual
   */
  static const std::string kInMemory;

  /**
   * The extension of filename of database
   */
  static const std::string kExtension;

  /**
   * Execs query for internal using in this class
   * @param query sql query without return results
   * @return true if query was executed successfully
   */
  inline bool Exec(const std::string& query);

  friend class SQLQuery;
};

#endif  // COMPONENTS_UTILS_SQLITE_WRAPPER_SQL_DATABASE_H
