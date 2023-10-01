#include <stdlib.h>
#include <time.h>

#include "domain/monsters/monsters.h"
#include "ihm/ihm.h"
#include "application/port/in/start_fight.h"

int main() {
    srand(time(NULL));

    /* TODO
     * [ ] NO LEAKS
     * [ ] specials traits in each zone
     *
     * THEN
     * [~] Port & Adapters architecture
     * [ ] Write beautiful readme
     *
     * THEN
     * [ ] Boost CLI
     * [ ] parser JSON ? yeah
     *
     * THEN
     * [ ] SDL
     */

    GameState state = open_start_menu();
    while (true) {
        state.game = start_fight(state.game);
        if(player_is_dead(state.game.player)) {
            display_game_over();
            break;
        }
        state.game.map.spawn = enter_map(state.game.map);
        state.game.map = spawn_player_on_map_at_position(state.game.player, state.game.map, state.game.map.spawn);
    }

    free_doom_depths(state.game);
    return EXIT_SUCCESS;
}
