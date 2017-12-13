#include "sql_error.h"

SQLError::SQLError(Error number, const std::string& text)
    : number_(number), text_(text) {}

Error SQLError::number() const {
  return number_;
}

std::string SQLError::text() const {
  if (!text_.empty()) {
    return text_;
  }
  switch (number_) {
    case OK:
      text_ = "Successful result";
      break;
    case ERROR:
      text_ = "SQL error or missing database";
      break;
    case INTERNAL:
      text_ = "Internal logic error in SQLite";
      break;
    case PERM:
      text_ = "Access permission denied";
      break;
    case ABORT:
      text_ = "Callback routine requested an abort";
      break;
    case BUSY:
      text_ = "The database file is locked";
      break;
    case LOCKED:
      text_ = "A table in the database is locked";
      break;
    case NOMEM:
      text_ = "A malloc() failed";
      break;
    case READONLY:
      text_ = "Attempt to write a readonly database";
      break;
    case INTERRUPT:
      text_ = "Operation terminated by sqlite3_interrupt()";
      break;
    case IOERR:
      text_ = "Some kind of disk I/O error occurred";
      break;
    case CORRUPT:
      text_ = "The database disk image is malformed";
      break;
    case NOTFOUND:
      text_ = "Unknown opcode in sqlite3_file_control()";
      break;
    case FULL:
      text_ = "Insertion failed because database is full";
      break;
    case CANTOPEN:
      text_ = "Unable to open the database file";
      break;
    case PROTOCOL:
      text_ = "Database lock protocol error";
      break;
    case EMPTY:
      text_ = "Database is empty";
      break;
    case SCHEMA:
      text_ = "The database schema changed";
      break;
    case TOOBIG:
      text_ = "String or BLOB exceeds size limit";
      break;
    case CONSTRAINT:
      text_ = "Abort due to constraint violation";
      break;
    case MISMATCH:
      text_ = "Data type mismatch";
      break;
    case MISUSE:
      text_ = "Library used incorrectly";
      break;
    case NOLFS:
      text_ = "Uses OS features not supported on host";
      break;
    case AUTH:
      text_ = "Authorization denied";
      break;
    case FORMAT:
      text_ = "Auxiliary database format error";
      break;
    case RANGE:
      text_ = "2nd parameter to sqlite3_bind out of range";
      break;
    case NOTADB:
      text_ = "File opened that is not a database file";
      break;
    case NOTICE:
      text_ = "Notifications from sqlite3_log()";
      break;
    case WARNING:
      text_ = "Warnings from sqlite3_log()";
      break;
    case ROW:
      text_ = "sqlite3_step() has another row ready";
      break;
    case DONE:
      text_ = "sqlite3_step() has finished executing";
      break;
    default:
      text_ = "Unknown error";
  }
  return text_;
}
