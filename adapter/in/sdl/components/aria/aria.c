
//
// Created by Theo OMNES on 20/10/2023.
//

#include <stddef.h>
#include <stdlib.h>
#include "aria.h"


AriaNode *start_aria_node();

Aria create_aria(uint8_t size) {
    Aria aria;
    aria.size = size;
    aria.selected = start_aria_node();
    return aria;
}

AriaNode *start_aria_node() {
    AriaNode *node = malloc(sizeof(AriaNode));
    node->id = NULL;
    node->next = node;
    return node;
}

AriaNode *aria_node(const char* id, AriaNode *next) {
    AriaNode *node = malloc(sizeof(AriaNode));
    *node = (AriaNode) {
            .id = id,
            .next = next,
    };
    return node;
}

void aria_add(Aria aria, const char *id) {
    AriaNode *i = aria.selected;
    while(i->next->id != NULL) {
        i = i->next;
    }
    AriaNode *last_node = i;
    last_node->next = aria_node(id, last_node->next);
}

Aria aria_next(Aria aria) {
    aria.selected = aria.selected->next->id == NULL
             ? aria.selected->next->next
             : aria.selected->next;
    return aria;
}
