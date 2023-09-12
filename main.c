#include <stdio.h>

#include <stdlib.h>
#include <time.h>

#include "monsters/monsters.h"
#include "player/player.h"

int main() {
    srand(time(NULL));

    Player p = player(100, 4);

    Monster m = random_monster();
    char* m_s = stringify_monster(m);

    printf("%s\n", m_s);

    free(m_s);
    return EXIT_SUCCESS;
}
