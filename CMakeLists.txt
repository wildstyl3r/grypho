cmake_minimum_required(VERSION 3.14...3.18)

project(
  grypho
  VERSION 0.0.1
  DESCRIPTION "Simple graph class"
  LANGUAGES CXX)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  option(BUILD_DEMO "Build the demo" ON)
  option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
endif()

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(
    STATUS
      "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE
      "${default_build_type}"
      CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
                                               "MinSizeRel" "RelWithDebInfo")
endif()

add_subdirectory(src)
add_subdirectory(nodesoup)

include(GNUInstallDirs)
install(
  TARGETS grypho
  EXPORT grypho-targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  INCLUDES
  DESTINATION include
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/grypho)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  grypho-config-version.cmake
  VERSION ${PACKAGE_VERSION}
  COMPATIBILITY AnyNewerVersion)

install(
  EXPORT grypho-targets
  FILE grypho-config.cmake
#  NAMESPACE nodesoup::
  DESTINATION lib/cmake/grypho)

export(
  TARGETS grypho
#  NAMESPACE nodesoup::
  FILE grypho-targets.cmake)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CPACK_PACKAGE_VENDOR "wildstyl3r")
  #set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
  #set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
  set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
  set(CPACK_SOURCE_IGNORE_FILES /.clang-format /compile_commands.json /.git
                                /dist /.*build.* /\\\\.DS_Store)
  include(CPack)
endif()

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR grypho_BUILD_DEMO)
   AND BUILD_DEMO)
  add_subdirectory(demo)
endif()
