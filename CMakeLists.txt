cmake_minimum_required( VERSION 3.30 )
project( agile1-game CXX )

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./build/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ./build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./build/bin)

file( GLOB_RECURSE FILES src/*.cpp )

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(main ${FILES})
target_link_libraries(main ${CURSES_LIBRARIES})