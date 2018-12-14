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
#include "keys.h"

/*!\brief Initial configurations to setup the screen
 *
 * ncurses:
 * The function sets up a new ncurses screen and calls
 * some ncurses functions in order to suppress the echoing
 * of the pressed keys, hiding cursor and to enable special
 * keys like arrows. It also calls the nodelay function which
 * makes getch non blocking.
 *
 * winAPI:
 * no setup needed, just clear the screen.
 */
void screen_setup() {
    #ifdef __linux__
        initscr();
        start_color();
        noecho();
        nodelay(stdscr, true);
        curs_set(0);
        keypad(stdscr, true);
    #elif _WIN32
        clear_screen();
    #endif
}

/*!\brief Print string to screen
 *
 * ncurses, winAPI:
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
        if(!move_cursor(x, y)) /* something wrong happened in move_cursor */
            return;
        waddstr(stdscr, string);
    #elif _WIN32
        if(!move_cursor(x, y)) /* something wrong happened in move_cursor */
            return;
        std::cout << string;
    #endif

    refresh_screen();
}

/*!\brief Print char to screen
 *
 * ncurses, winAPI:
 * The function moves the cursor (x, y) and then prints
 * to the screen the char at S(x, y)
 *
 * @param x x axis coord
 * @param y y axis coord
 * @param c char that is going to be printed
 */
void print(int x, int y, const char c) {
    #ifdef __linux__
        if(!move_cursor(x, y)) /* something wrong happened in move_cursor */
            return;
        waddch(stdscr, c);
    #elif _WIN32
        if(!move_cursor(x, y)) /* something wrong happened in move_cursor */
            return;
        std::cout << c;
    #endif

    refresh_screen();
}

/*!\brief Moves cursor.
 *
 * winAPI:
 * coordinates need to be short, so the function checks if
 * the coord is greater than the maximum short value to prevent overflows
 *
 * @param x x axis coord
 * @param y y axis coord
 */
bool move_cursor(int x, int y) {
    if(x < 0 || y < 0)
        return false;
    #ifdef __linux__
        wmove(stdscr, y, x);
        return true;
    #elif _WIN32
        if(x > SHRT_MAX || y > SHRT_MAX)
            return false; /* overflow detected */
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) {(short) x, (short) y});
        return true;
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
 *
 * winAPI:
 * Fill console with spaces
 *
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
 * ncurses:
 * call the endwin function
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

/*!\brief Get terminal window size (max X and max Y)
 *
 * winAPI:
 * code from https://stackoverflow.com/questions/6812224/getting-terminal-size-in-c-for-windows/12642749#12642749
 */
term_size get_term_size() {
    term_size ts;
    #ifdef __linux__
        getmaxyx(stdscr, ts.height, ts.width);
    #elif _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        ts.width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        ts.height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    #endif
    
    return ts;
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
 * winAPI
 * wrap _getch from conio.h
 */
int raw_input() {
    #ifdef __linux__
        return getch();
    #elif _WIN32
        return _getch();
    #endif
}

/*!\brief handle some special keys
 */
int input() {
    int ch = raw_input();
    #ifdef __linux__
        switch(ch) {
            case 258: /* arrow down */
                return ARROW_DOWN;
            case 259: /* arrow up */
                return ARROW_UP;
            case 260: /* arrow left */
                return ARROW_LEFT;
            case 261: /* arrow right */
                return ARROW_RIGHT;
            case 27: /* escape key */
                return ESC_KEY;
            default: /* other characters such as letters */
                return ch;
        }
    #elif _WIN32
        if(ch == 224) { /* mingw escape */
            int k = raw_input();
            switch(k) {
                case 80: /* arrow down */
                    return ARROW_DOWN;
                case 72: /* arrow up */
                    return ARROW_UP;
                case 75: /* arrow left */
                    return ARROW_LEFT;
                case 77: /* arrow right */
                    return ARROW_RIGHT;
                default: /* ??? */
                    return -1;
            }
        } else if(ch == 27) { /* escape key */
            return ESC_KEY;
        } else { /* other characters such as letters */
            return ch;
        }
    #endif
}
