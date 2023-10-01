
//
// Created by Theo OMNES on 01/10/2023.
//

#include <stdlib.h>
#include "random.h"
#include "../utils.h"


/**
 * a: 8, b: 4 -> returns 6
 * a: 4, b: 7 -> returns 5
 * @return ALWAYS the floor average between 'a' and 'b'
 */
int8_t random_between_included(int8_t a, int8_t b) {
    if (a == b) return a;
    int8_t minimum = min(a, b);
    int8_t maximum = max(a, b);
    return ((maximum - minimum) / 2) + minimum;
}