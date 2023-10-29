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
 * [ ] display map on drag (with mouse)
 *
 * SDL
 * [ ] ARIA : navigate by TAB & ENTER
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