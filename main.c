#include <stdlib.h>
#include <time.h>

#include "application/port/in/command/start_ihm.h"

int main() {
    srand(time(NULL));

    /* TODO
     * [ ] NO LEAKS
     * [ ] specials traits in each zone
     * [ ] log variatique (format,...)
     * [x] Refactoring loop engine
     * [ ] Write beautiful readme
     * [ ] parser JSON ? yeah
     * [ ] fix start at turn 2, Player choose action "[Open grim",
     * [ ] fix restore
     * [ ] Boost CLI
     *
     * THEN
     * [ ] SDL
     *
     * [ ] multi language ? by factory
    */

    start_ihm();

    return EXIT_SUCCESS;
}
