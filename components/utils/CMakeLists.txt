
set(TARGET utils)

set(SOURCES
  file_system.cpp
  sqlite_wrapper/sql_database.cc
  sqlite_wrapper/sql_query.cc
  sqlite_wrapper/sql_error.cc
)

set(LIBRARIES
  sqlite3
)
add_library(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} ${LIBRARIES})
