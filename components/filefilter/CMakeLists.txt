
set(TARGET filefilter)

include_directories(
  ${CMAKE_SOURCE_DIR}/utils
)

set(SOURCE
  file_scanner.cc
)

set(LIBRARIES

)

add_library(${TARGET} ${SOURCE})
target_link_libraries(${TARGET} ${LIBRARIES})
