
//
// Created by Theo OMNES on 28/09/2023.
//

#include <stdio.h>

#include <domain/map/map.h>
#include <domain/map/position/position.h>

#include <application/port/out/log/log_error.h>
#include <application/port/out/log/log_info.h>

Position ask_player_zone_position_to_go(Map map);

void display_map(Map m);


Position enter_map(Map m) {
    Position p;
    do {
        display_map(m);
        p = ask_player_zone_position_to_go(m);
    } while (player_can_move_to_position_in_map(p, m) == false);
    return p;
}

bool can_display_position_in_map(Position p, Map m) {
    if (position_is_in_map_and_not_empty(p, m) == false) return false;
    if (positions_a_equals_b(m.spawn, p)) return true;
    if (position_is_finished(p, m)) return true;

    return position_is_finished(up_from(p), m)
           || position_is_finished(down_from(p), m)
           || position_is_finished(right_from(p), m)
           || position_is_finished(left_from(p), m);
}

void display_map(Map m) {
    for (int i = 0; i < m.width + 1; i++) {
        if (i == 0) fputs("\t", stdout);
        else fprintf(stdout, " %c\t", 'a' + i - 1);
    }
    fputc('\n', stdout);
    for (int row = 0; row < m.height; row++) {
        fprintf(stdout, "%d\t", row + 1);
        for (int col = 0; col < m.width; col++) {
            Position p = position(col, row);
            Zone z = get_zone_in_map_by_position(m, p);
            if (!can_display_position_in_map(p, m)) {
                fputc('\t', stdout);
                continue;
            }
            switch (z.status) {
                case ZONE_EMPTY:
                    fputc('\t', stdout);
                    break;
                case ZONE_NOT_DISCOVERED:
                    fputs("[ ]\t", stdout);
                    break;
                case ZONE_FINISHED:
                    fputs("[x]\t", stdout);
                    break;
                default: {
                    log_error("Unknown ZoneStatus");
                    fputs("???\t", stdout);
                }
            }
        }
        fputc('\n', stdout);
    }
    fputc('\n', stdout);
}

Position ask_player_zone_position_to_go(Map map) {
    fprintf(stdout, "Select zone column[a-%c] and row[1-%d]", 'a' + map.width - 1, map.height);
    fputs("\ncolumn: ", stdout);
    char column = -1;
    while (column < 'a' || column >= 'a' + map.width) {
        fflush(stdin);
        column = fgetc(stdin);
    }
    uint16_t row = -1;
    fputs("row: ", stdout);
    while (row < 1 || row > map.height) {
        fflush(stdin);
        scanf("%hd", &row);
    }

    Position p = position(column - 'a', row - 1);
    char *position_str = position_to_string(p);
    log_info(position_str);
    free(position_str);

    return p;
}