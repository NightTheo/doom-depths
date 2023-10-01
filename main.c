#include <stdlib.h>
#include <time.h>

#include "domain/monsters/monsters.h"

#include "application/port/in/start_fight.h"

#include "application/port/out/persistence/intern_game_state/game_state.h"
#include "application/port/out/ihm/display_leave_town_actions.h"
#include "application/port/out/ihm/display_game_over.h"
#include "application/port/out/ihm/display_map.h"
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
