
//
// Created by Theo OMNES on 15/10/2023.
//

#ifndef DOOMDEPTHS_ROW_H
#define DOOMDEPTHS_ROW_H

#include <stdint.h>
#include "in/sdl/components/button/button.h"
#include "in/sdl/components/aria/aria.h"

typedef enum {
    CELL_ERROR,
    BUTTON,
} CellType;

typedef struct {
    const char *message;
} CellError;

typedef union {
    Button button;
    CellError error;
} Cell;

typedef struct {
    CellType cellType;
    Cell cell;
} RowCell;

typedef struct {
    uint16_t length;
    RowCell *cells;
    SDL_Rect rect;
    PositionInScreen position;
    uint8_t spacing;
    Aria aria;
} Row;

typedef struct {
    int *x;
    int *y;
    int *w;
    int *h;
} UpdateRect;

Row create_row_with_indexes(int length, ...);

Row row_with_row_button_at_index(Row row, Button button, uint16_t index);

RowCell row_cell_by_type(CellType cellType, Button cell);

RowCell get_button_in_row_at_index(Row row, uint16_t index);

int get_cell_width(RowCell param);

Row position_row(PositionInScreen position, Row row, SDL_Rect zone);

Row spacing_row(uint8_t spacing, Row row);

Row update_row_position_in_zone(Row row, SDL_Rect zone);

void draw_row(SDL_Renderer *renderer, Row row);

Row row_handle_event(SDL_Event event, SDL_IHM ihm, Row row);

#endif //DOOMDEPTHS_ROW_H
