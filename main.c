#include <stdlib.h>
#include <time.h>

#include "domain/monsters/monsters.h"
#include "domain/fight/fight.h"
#include "domain/repository.h"
#include "ihm/ihm.h"
#include "domain/map/map.h"

int main() {
    srand(time(NULL));

    Map map = basic_map(); // TODO put in game state (save and restore)
    display_map(map);
    GameState state = open_start_menu();
    Fight fight = {
            state.turn,
            state.player,
            state.monsters_list,
    };

    fight = start_fight(fight);

    if(!player_is_alive(fight.player)) {
        display_game_over();
    }

    free_fight(fight);
    free_inventory(fight.player.inventory);
    free_map(map);
    return EXIT_SUCCESS;
}
