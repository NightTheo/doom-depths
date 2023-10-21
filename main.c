#include <stdlib.h>
#include <time.h>

#include <application/port/in/command/start_ihm.h>

#include "SDL2/SDL.h"

/* TODO
 * [ ] NO LEAKS
 * [ ] specials traits in each zone
 * [ ] Write beautiful readme
 * [ ] parser JSON ? yeah
 * [ ] cli: display stuff without log
 * [ ] Boosted CLI
 * [ ] inventory in Union, not allocated
 *
 * SDL
 * [ ] navigate by TAB & ENTER (bool is_selected in button, selected_color)
 * [ ] bug fight page : at first event (mouse move) buttons row shift to the right
 *
 * THEN
 * [ ] Tests
 *
 * [ ] multi language ? by factory
*/


int main() {
    srand(time(NULL));

    start_ihm();
    return EXIT_SUCCESS;
}