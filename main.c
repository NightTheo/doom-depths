#include <stdlib.h>
#include <time.h>

#include "domain/monsters/monsters.h"
#include "domain/fight/fight.h"
#include "domain/repository.h"
#include "ihm/ihm.h"

int main() {
    srand(time(NULL));

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

    free(fight.monsters_list.monsters);
    free_inventory(fight.player.inventory);
    return EXIT_SUCCESS;
}
