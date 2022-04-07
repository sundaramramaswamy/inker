file(DOWNLOAD
  https://github.com/raysan5/raylib/releases/download/4.0.0/raylib-4.0.0_win64_msvc16.zip
  ${CMAKE_BINARY_DIR}/raylib-4.0.0_win64_msvc16.zip
  EXPECTED_HASH MD5=1ac0fbe4b14d656bbe7879642cb178e8)

file(ARCHIVE_EXTRACT INPUT
  "${CMAKE_BINARY_DIR}/raylib-4.0.0_win64_msvc16.zip")
add_library(raylib STATIC IMPORTED GLOBAL)
set_target_properties(raylib PROPERTIES
  IMPORTED_LOCATION
  "${CMAKE_BINARY_DIR}/raylib-4.0.0_win64_msvc16/lib/raylib.lib")
target_include_directories(raylib
  INTERFACE "${CMAKE_BINARY_DIR}/raylib-4.0.0_win64_msvc16/include")
target_link_libraries(raylib INTERFACE winmm)
target_link_options(raylib
  INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/NODEFAULTLIB:MSVCRT>)
