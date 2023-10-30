
//
// Created by Theo OMNES on 30/09/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "time_util.h"


char *now_to_str() {
    time_t timestamp = time(NULL);
    struct tm *now = localtime(&timestamp); // DO NOT FREE THIS POINTER
    char *s = malloc(32);
    if (s == NULL) {
        return NULL;
    }
    sprintf(s, "%4d-%02d-%02d %02d:%02d:%02d",
            now->tm_year + 1900, now->tm_mon + 1, now->tm_mday,
            now->tm_hour, now->tm_min, now->tm_sec);

    return s;
}