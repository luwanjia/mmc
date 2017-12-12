
option(ENABLE_LOG "Logging feature" ON)

cmake_minimum_required(VERSION 2.8)

project(mmc)

set(CMAKE_CXX_COMPILER   $ENV{CMAKE_CXX_COMPILER})
set(CMAKE_C_COMPILER     $ENV{CMAKE_C_COMPILER})

set(CMAKE_CXX_FLAGS_RELEASE " -DNDEBUG -s -O2")
set(CMAKE_CXX_FLAGS_DEBUG   " -DDEBUG -g3 -ggdb3")

if(ENABLE_LOG)
  add_definitions(-DENABLE_LOG)
endif()

add_subdirectory(filefilter)
add_subdirectory(utils)
