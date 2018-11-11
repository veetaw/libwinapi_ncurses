cmake_minimum_required(VERSION 3.12)
project(winapi_ncurses)

set(CMAKE_CXX_STANDARD 14)

add_library(winapi_ncurses src/wrapper.cpp src/wrapper.h src/color.h)