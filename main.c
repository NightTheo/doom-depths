#include <stdlib.h>
#include <time.h>

#include "domain/monsters/monsters.h"
#include "domain/fight/fight.h"
#include "domain/repository.h"
#include "ihm/ihm.h"
#include "domain/map/map.h"

int main() {
    srand(time(NULL));

    /* TODO
     * [x] global struct with Map and player
     * [x] change GameState to contain this struct
     * [ ] save this struct
     * [ ] restore this struct
     * [x] display map and select a zone
     * [ ] specials traits in each zone
     * start fight
     * until player change zone
     * [ ] automatic save when change zone
     *
     * THEN
     * [ ] Port & Adapters architecture
     * [ ] Write beautiful readme
     *
     * THEN
     * [ ] Boost CLI
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
        state.game.map.playerPosition = enter_map(state.game.map);
    }


    free_doom_depths(state.game);
    return EXIT_SUCCESS;
}
