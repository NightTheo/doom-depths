#include <stdlib.h>
#include <time.h>

#include "monsters/monsters.h"
#include "fight/fight.h"
#include "utils/random/random.h"

int main() {
    srand(time(NULL));
    Fight fight = {
            1,
            player(100),
            random_list_of_monsters(random_between_included(2, 5))
    };

    fight = start_fight(fight);

    free(fight.monsters_list.monsters);
    free_inventory(fight.player.inventory);
    return EXIT_SUCCESS;
}
