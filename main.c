#include <stdlib.h>
#include <time.h>

#include "domain/monsters/monsters.h"

#include "application/port/in/start_fight.h"

#include "application/port/out/persistence/game_state.h"
#include "application/port/out/ihm/leave_town.h"
#include "application/port/out/ihm/display_game_over.h"
#include "application/port/out/ihm/display_map.h"

int main() {
    srand(time(NULL));

    /* TODO
     * [ ] NO LEAKS
     * [ ] specials traits in each zone
     *
     * THEN
     * [/] Port & Adapters architecture
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

    GameState state = leave_town();
    while (true) {
        state.game = start_fight(state.game);
        if (player_is_dead(state.game.player)) {
            display_game_over();
            break;
        }
        state.game.map.spawn = enter_map(state.game.map);
        state.game.map = spawn_player_on_map_at_position(state.game.player, state.game.map, state.game.map.spawn);
    }

    free_doom_depths(state.game);
    return EXIT_SUCCESS;
}
