#include <curses.h>

#ifndef WINAPI_NCURSES_COLORS_H
#define WINAPI_NCURSES_COLORS_H
    // my attempt to make predefined colors "cross platform"
    #ifdef __linux__
        class Color {
        public:
            short black = COLOR_BLACK;
            short blue = COLOR_BLUE;
            short red = COLOR_RED;
            short green = COLOR_GREEN;
            short yellow = COLOR_YELLOW;
            short magenta = COLOR_MAGENTA;
            short white = COLOR_WHITE;
        };
    #elif _WIN32
        class Color {
        public:
            short black = 0;
            short blue = 1;
            short red = 4;
            short green = 2;
            short yellow = 14;
            short magenta = 5;
            short white = 15;
        };
    #endif
#endif //WINAPI_NCURSES_COLORS_H
