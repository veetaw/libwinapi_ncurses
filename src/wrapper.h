#ifndef WINAPI_NCURSES_LIBRARY_H
#define WINAPI_NCURSES_LIBRARY_H
    void screen_setup();
    void print(int x, int y, const char* string);
    void move_cursor(int x, int y);
    void change_color(/* todo */);
    void refresh_screen();
    void clear_screen();
    void close_window();
#endif // WINAPI_NCURSES_LIBRARY_H