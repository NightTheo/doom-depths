#include <stdio.h>

#include <stdlib.h>
#include <time.h>

#include "monsters/monsters.h"

int main() {
    srand(time(NULL));
    Monster a = random_monster();
    Monster b = random_monster();
    Monster c = random_monster();
    Monster d = random_monster();

    char* a_s = stringify_monster(a);
    char* b_s = stringify_monster(b);
    char* c_s = stringify_monster(c);
    char* d_s = stringify_monster(d);

    printf("%s\n", a_s);
    printf("%s\n", b_s);
    printf("%s\n", c_s);
    printf("%s\n", d_s);

    free(a_s);free(b_s); free(c_s); free(d_s);
    return 0;
}
