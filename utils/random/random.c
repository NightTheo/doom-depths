
//
// Created by Theo OMNES on 11/09/2023.
//

#include <stdlib.h>

#include "random.h"
#include "utils.h"

int8_t random_between_included(int8_t a, int8_t b) {
    if (a == b) return a;
    int8_t minimum = min(a, b);
    int8_t maximum = max(a, b);
    return (rand() % (maximum + 1 - minimum)) + minimum;
}