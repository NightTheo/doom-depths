#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include <application/port/in/command/start_ihm.h>

#include "SDL2/SDL.h"

/* TODO
 * [ ] NO LEAKS
 * [ ] specials traits in each zone
 * [ ] Write beautiful readme
 * [ ] parser JSON ? yeah
 * [ ] display stuff without log
 * [ ] Boosted CLI
 * [ ] inventory in Union, not allocated
 *
 * THEN
 * [ ] SDL
 * [ ] Tests
 *
 * [ ] multi language ? by factory
*/


int main() {
    srand(time(NULL));

    start_ihm();
    return EXIT_SUCCESS;
}