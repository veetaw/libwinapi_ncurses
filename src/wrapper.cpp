#ifdef __linux__
    #include <curses.h>
#elif _WIN32
    #include "" // todo include winapi
#endif

#include "wrapper.h"
#include "colors.h"

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

/* \brief Moves cursor.
 *
 * @param x x axis coord
 * @param y y axis coord
 */
void move_cursor(int x, int y) {
    #ifdef __linux__
        wmove(stdscr, y, x);
    #elif _WIN32
        // todo
    #endif
}

void change_color() {

}

/* \brief Refreshes screen
 *
 * ncurses:
 * this function must be called every action that modifies the ui, like printing.
 */
void refresh_screen() {
    #ifdef __linux__
        wrefresh(stdscr);
    #elif _WIN32
        // todo
    #endif
}

/* \brief Fill screen with blank characters.
 *
 * ncurses:
 * The method calls clear() that fills screen with blank
 * characters and ensures that on the next refresh the
 * windows is repainted from zero.
 */
void clear_screen() {
    #ifdef __linux__
        clear();
    #elif _WIN32
        // todo
    #endif

    refresh_screen();
}

/* \brief Clears garbage and closes window
 *
 * winAPI:
 * no actions needed.
 */
void close_window() {
    #ifdef __linux__
        endwin();
    #elif _WIN32
        // todo
    #endif
}


