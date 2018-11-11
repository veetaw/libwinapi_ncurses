#include "wrapper.h"
#ifdef __linux__
    #include <curses.h>
#elif _WIN32
    #include "" // todo include winapi
#endif

/* \brief Initial configurations to setup the screen
 *
 * ncurses:
 * The function sets up a new ncurses screen and calls
 * some ncurses functions in order to suppress the echoing
 * of the pressed keys and to enable special keys like arrows.
 *
 * winAPI:
 * no setup needed.
 */
void screen_setup() {
    #ifdef __linux__
        initscr();
        start_color();
        noecho();
        keypad(stdscr, true);
    #elif _WIN32
        // no setup needed
    #endif
}

/* \brief Print string to screen
 *
 * ncurses, winapi:
 * The function moves the cursor (x, y) and then prints
 * to the screen the string starting from S(x, y) to
 * E(x+length(string), y)
 *
 * @param x x axis coord
 * @param y y axis coord
 * @param string c style string that is going to be
 *        printed, must end with a null terminator (\0 char)
 */
void print(int x, int y, const char *string) {
    #ifdef __linux__
        move_cursor(x, y);
        waddstr(stdscr, string);
    #elif _WIN32
        // todo
    #endif

    refresh_screen();
}

void move_cursor(int x, int y) {

}

void change_color() {

}

// todo doc
// every function that modifies ui must call this
void refresh_screen() {

}

void clear_screen() {

}

void close_window() {

}


