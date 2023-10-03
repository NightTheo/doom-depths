#include <stdlib.h>
#include <time.h>

#include "application/port/in/command/start_ihm.h"

int main() {
    srand(time(NULL));

    /* TODO
     * [ ] NO LEAKS
     * [ ] specials traits in each zone
     * [ ] Write beautiful readme
     * [ ] parser JSON ? yeah
     * [ ] display stuff without log
     * [ ] Boosted CLI
     *
     * THEN
     * [ ] SDL
     * [ ] Tests
     *
     * [ ] multi language ? by factory
    */

    start_ihm();

    return EXIT_SUCCESS;
}
