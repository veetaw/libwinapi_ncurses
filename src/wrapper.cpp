#ifdef __linux__
    #include <curses.h>
    #include <unistd.h>
#elif _WIN32
    #include <windows.h>
    #include <conio.h>
    #include <iostream>
    #include <climits>
#endif

#include "wrapper.h"

/*!\brief Initial configurations to setup the screen
 *
 * ncurses:
 * The function sets up a new ncurses screen and calls
 * some ncurses functions in order to suppress the echoing
 * of the pressed keys, hiding cursor and to enable special keys like arrows.
 *
 * winAPI:
 * no setup needed, just clear the screen.
 */
void screen_setup() {
    #ifdef __linux__
        initscr();
        start_color();
        noecho();
        curs_set(0);
        keypad(stdscr, true);
    #elif _WIN32
        clear_screen();
    #endif
}

/*!\brief Print string to screen
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
        move_cursor(x, y);
        std::cout << string;
    #endif

    refresh_screen();
}

/*!\brief Moves cursor.
 *
 * @param x x axis coord
 * @param y y axis coord
 */
void move_cursor(int x, int y) {
    #ifdef __linux__
        wmove(stdscr, y, x);
    #elif _WIN32
        if(x > SHRT_MAX || y > SHRT_MAX)
            return /* overflow detected, just don't do anything */
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) {(short) x, (short) y})
    #endif
}

/*!\brief changes text color
 *
 * ncurses:
 * Creates a new pair, overriding the first
 * and using always black as background.
 *
 * @param color Color from colors.h
 */
void change_color(short color) {
    #ifdef __linux__
        if(has_colors()) {
            // workaround: use color as color pair id because it must be different for every pair
            init_pair(color , color, COLOR_BLACK);
            attron(COLOR_PAIR(color));
        }
    #elif _WIN32
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    #endif
}

/*!\brief Refreshes screen
 *
 * ncurses:
 * this function must be called every action that modifies the ui, like printing.
 *
 * winAPI:
 * no actions needed.
 */
void refresh_screen() {
    #ifdef __linux__
        wrefresh(stdscr);
    #elif _WIN32
    #endif
}

/*!\brief Fill screen with blank characters.
 *
 * ncurses:
 * The method calls clear() that fills screen with blank
 * characters and ensures that on the next refresh the
 * window is repainted from zero.
 */
void clear_screen() {
    #ifdef __linux__
        clear();
    #elif _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD chars_written;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        FillConsoleOutputCharacter(
                GetStdHandle(STD_OUTPUT_HANDLE),
                (TCHAR) ' ',
                csbi.dwSize.X * csbi.dwSize.Y,
                (COORD) {0, 0},
                &chars_written
         );
        FillConsoleOutputAttribute(
                GetStdHandle(STD_OUTPUT_HANDLE),
                csbi.wAttributes,
                csbi.dwSize.X * csbi.dwSize.Y,
                (COORD) {0, 0},
                &chars_written
        );

        move_cursor(0, 0);
    #endif

    refresh_screen();
}

/*!\brief Clears garbage and closes window
 *
 * winAPI:
 * no actions needed, so just clear the screen.
 */
void close_window() {
    #ifdef __linux__
        endwin();
    #elif _WIN32
        clear_screen();
    #endif
}

/*!\brief cross platform sleep
 *
 * @param ms milliseconds to sleep
 */
void _sleep(unsigned int ms) {
    #ifdef __linux__
        usleep(ms * 1000);
    #elif _WIN32
        Sleep(ms);
    #endif
}

/*!\brief get an int from input
 *
 * ncurses:
 * wrap getch from ncurses lib
 *
 * winapi
 * wrap _getch from conio.h
 */
int raw_input() {
    #ifdef __linux__
        return getch();
    #elif _WIN32
        return _getch();
    #endif
}
