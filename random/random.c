
//
// Created by Theo OMNES on 11/09/2023.
//

#include "random.h"

#include <stdlib.h>

int random_between_included(int min, int max) {
    if(max <= min) return min;
    return rand() % (max+1 - min) + min;
}