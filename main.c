#include <stdlib.h>
#include <time.h>

#include "monsters/monsters.h"
#include "fight/fight.h"
#include "utils/random/random.h"

int main() {
    srand(time(NULL));
    Fight f = {
            1,
            player(100, 4),
            random_list_of_monsters(random_between_included(2, 5))
    };

    start_fight(f);

    free(f.monsters_list.monsters);
    free_inventory(f.player.inventory);
    return EXIT_SUCCESS;
}
