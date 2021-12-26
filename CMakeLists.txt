cmake_minimum_required(VERSION 3.14...3.18)

project(
  grypho
  VERSION 0.1.0
  DESCRIPTION "Simple graph class"
  LANGUAGES CXX)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  option(BUILD_DEMO "Build the demo" ON)
  option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
endif()

add_subdirectory(src)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR grypho_BUILD_DEMO)
   AND BUILD_DEMO)
  add_subdirectory(demo)
endif()
