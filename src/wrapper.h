#include "color.h"

#ifndef WINAPI_NCURSES_LIBRARY_H
#define WINAPI_NCURSES_LIBRARY_H
    void screen_setup();
    void print(unsigned int x, unsigned int y, const char* string);
    bool move_cursor(unsigned int x, unsigned int y);
    void change_color(short color);
    void refresh_screen();
    void clear_screen();
    void close_window();
    void _sleep(unsigned int ms);
    int raw_input();
#endif // WINAPI_NCURSES_LIBRARY_H