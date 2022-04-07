cmake_minimum_required(VERSION 3.14)

include(cmake/utils.cmake)
include(cmake/get_raylib.cmake)

project(Inker
  VERSION 0.1.0
  DESCRIPTION "C++ Inking Application"
  LANGUAGES CXX)

add_executable(ink
  src/main.cpp)

# Confirm strictly to C++17.  FlatBuffers needs C++11 or newer.
# https://cliutils.gitlab.io/modern-cmake/chapters/features/cpp11.html
target_compile_features(ink PUBLIC cxx_std_17)
set_target_properties(ink PROPERTIES
  CXX_EXTENSIONS OFF
  CXX_STANDARD_REQUIRED ON)

target_link_libraries(ink PRIVATE
  raylib)
