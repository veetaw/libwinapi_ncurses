#include "color.h"

#ifndef WINAPI_NCURSES_LIBRARY_H
#define WINAPI_NCURSES_LIBRARY_H
    void screen_setup();
    void print(int x, int y, const char* string);
    bool move_cursor(int x, int y);
    void change_color(short color);
    void refresh_screen();
    void clear_screen();
    void close_window();
    void _sleep(unsigned int ms);
    int raw_input();
    int input();
#endif // WINAPI_NCURSES_LIBRARY_H