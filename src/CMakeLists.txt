add_library(grypho grypho.cpp grypho_fileio.cpp)

target_include_directories(
  grypho
  PUBLIC
    $<BUILD_INTERFACE:${grypho_SOURCE_DIR}/include>
  PRIVATE $<BUILD_INTERFACE:${grypho_SOURCE_DIR}/src>)

target_compile_features(grypho PUBLIC cxx_std_17)

set_target_properties(
  grypho PROPERTIES POSITION_INDEPENDENT_CODE ON
                      PUBLIC_HEADER ${grypho_SOURCE_DIR}/include/grypho.hpp)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(grypho PRIVATE -Wall -Wextra)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(grypho PRIVATE -Wall -Wextra)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(grypho PRIVATE /W4)
  target_compile_definitions(grypho PUBLIC _USE_MATH_DEFINES)
endif()
