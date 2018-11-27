cmake_minimum_required(VERSION 3.12)
project(winapi_ncurses)

set(CMAKE_CXX_STANDARD 14)

if(UNIX AND NOT APPLE) # can't test if it works on mac os
    message(STATUS "Linux detected.")
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})

    add_library(winapi_ncurses SHARED src/wrapper.cpp src/wrapper.h src/color.h src/keys.h)

    target_link_libraries(winapi_ncurses ${CURSES_LIBRARIES})
elseif(WIN32 AND MINGW) # todo support more windows compilers
    message(STATUS "Windows detected.")

    add_library(winapi_ncurses SHARED src/wrapper.cpp src/wrapper.h src/color.h src/keys.h)
endif()
