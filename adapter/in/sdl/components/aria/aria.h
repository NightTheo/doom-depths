
//
// Created by Theo OMNES on 20/10/2023.
//

#ifndef DOOMDEPTHS_ARIA_H
#define DOOMDEPTHS_ARIA_H

#include <stdint.h>

typedef struct AriaNode AriaNode;
struct AriaNode {
    const char* id;
    AriaNode *next;
};

typedef struct {
    uint8_t size;
    AriaNode *selected;
} Aria;


Aria create_aria(uint8_t nb_elements);

AriaNode * aria_node(const char* id, AriaNode *next);

void aria_add(Aria aria, const char *id);

Aria aria_next(Aria aria);

#endif //DOOMDEPTHS_ARIA_H
