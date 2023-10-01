#include <stdlib.h>
#include <time.h>

#include "application/port/in/start_ihm.h"

int main() {
    srand(time(NULL));

    /* TODO
     * [ ] NO LEAKS
     * [ ] specials traits in each zone
     *
     * THEN
     * [x] Port & Adapters architecture
     * [ ] Refactoring loop engine
     * [ ] Write beautiful readme
     * [ ] parser JSON ? yeah
     *
     * THEN
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
