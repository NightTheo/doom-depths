#include <stdlib.h>
#include <time.h>

#include "application/port/in/command/start_ihm.h"

int main() {
    srand(time(NULL));

    /* TODO
     * [ ] NO LEAKS
     * [ ] specials traits in each zone
     *
     * THEN
     * [x] Port & Adapters architecture
     * [ ] log variatique (format,...)
     * [x] Refactoring loop engine
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
