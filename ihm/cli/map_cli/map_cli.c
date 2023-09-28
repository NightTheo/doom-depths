
//
// Created by Theo OMNES on 28/09/2023.
//

#include <stdio.h>
#include "../../../domain/map/map.h"

/*
     0   1   2
0           [x]
1   [x] [x] [x]
2   [x]
*/
void display_map(Map m) {
    for(int i = 0; i < m.width+1; i++) {
        if(i == 0) fputs("\t", stdout);
        else fprintf(stdout, " %d\t", i-1);
    }
    fputc('\n', stdout);
    for(int row = 0; row < m.height; row++) {
        fprintf(stdout, "%d\t", row);
        for(int col = 0; col < m.width; col++) {
            Position p = position(col, row);
            Zone z = get_zone_in_map_by_position(m, p);
            switch (z.status) {
                case ZONE_EMPTY:
                    fputs("\t", stdout);
                    break;
                case NOT_DISCOVERED:
                    fputs("[x]\t", stdout);
                    break;
                case DISCOVERED:
                    fputs("[ ]\t", stdout);
                    break;
            }
        }
        fputc('\n', stdout);
    }
    fputc('\n', stdout);
}