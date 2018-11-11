cmake_minimum_required(VERSION 3.12)
project(winapi_ncurses)

set(CMAKE_CXX_STANDARD 14)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_library(winapi_ncurses SHARED src/wrapper.cpp src/wrapper.h src/color.h)

target_link_libraries(winapi_ncurses ${CURSES_LIBRARIES})

