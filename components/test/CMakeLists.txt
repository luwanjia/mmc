
set(TARGET test_filefilter)

include_directories(
  ${CMAKE_SOURCE_DIR}/filefilter
  ${CMAKE_SOURCE_DIR}/utils
)

set(SOURCES
  test_filefilter.cc
)

set(LIBRARIES
  filefilter
  utils
)
add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} ${LIBRARIES})
