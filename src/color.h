#include <curses.h>

#ifndef WINAPI_NCURSES_COLORS_H
#define WINAPI_NCURSES_COLORS_H
    // my attempt to make predefined Color "cross platform"
    #ifdef __linux__
        enum Color {
            black = COLOR_BLACK,
            blue = COLOR_BLUE,
            red = COLOR_RED,
            green = COLOR_GREEN,
            yellow = COLOR_YELLOW,
            magenta = COLOR_MAGENTA,
            white = COLOR_WHITE,
        };
    #elif _WIN32
        enum Color {
                black = 0,
                blue = 1,
                red = 4,
                green = 2,
                yellow = 14,
                magenta = 5,
                white = 15,
        };
    #endif
#endif //WINAPI_NCURSES_COLORS_H
