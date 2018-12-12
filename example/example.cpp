#include <iostream>
#include <ctime>
#include "../src/wrapper.h"
#include "../src/color.h"
#include "../src/keys.h"

int main(){
    screen_setup();
    srand(time(nullptr));

    // get window terminal size
    term_size ts = get_term_size();

    // fill the whole terminal window with dots
    for(int i=0; i<ts.width; ++i)
        for(int j=0; j<ts.height; ++j)
            print(i, j, ".");

    // print a yellow "A" to a random position and change color back to white
    Color color = Color();
    change_color(color.yellow);
    print(rand() % (ts.width + 1), rand() % (ts.height + 1), "A");
    change_color(color.white);

    // sleep for a second then clear screen
    _sleep(1000);
    clear_screen();

    // move a char (esc or q to exit)
    bool running = true;
    struct {
        int x = 0, y = 0;
    } pos;
    while(running) {
        switch(input()) {
            case -1:  // no input given
                break;
            case ARROW_UP:
                pos.y != 0 ? pos.y -= 1 : 0;
                break;
            case ARROW_DOWN:
                pos.y != ts.height ? pos.y += 1 : 0;
                break;
            case ARROW_LEFT:
                pos.x != 0 ? pos.x -= 1 : 0;
                break;
            case ARROW_RIGHT:
                pos.x != ts.width ? pos.x += 1 : 0;
                break;
            case 'q':
            case ESC_KEY:
                running = false;
                break;
        }        
        clear_screen();
        print(pos.x, pos.y, ".");
    }

    std::cin.get();
    close_window();
    return 0;
}
