
//
// Created by Theo OMNES on 15/10/2023.
//


#include "screen_position.h"
#include "application/port/out/log/log_error.h"
#include "application/port/out/log/log_info.h"
#include "in/sdl/components/button/button.h"
#include "in/sdl/components/row/row.h"

SDL_Rect position_rect(PositionInScreen position, SDL_Rect rect, SDL_Rect zone);

int position_rect_x(HorizontalPosition position, SDL_Rect rect, SDL_Rect zone);

int position_rect_y(VerticalPosition position, SDL_Rect rect, SDL_Rect zone);

RowCell position_row_cell_at_index(Row row, int index);

RowCell set_row_cell_rect(RowCell cell, UpdateRect rect);

SDL_Rect update_rect(SDL_Rect rect, UpdateRect update);


PositionInScreen position_in_screen(VerticalPosition v, HorizontalPosition h) {
    return (PositionInScreen) {
            .vertical = v,
            .horizontal = h,
    };
}

Button position_button(PositionInScreen position, Button button, SDL_Rect zone) {
    button.position = position;
    button.button_rect = position_rect(position, button.button_rect, zone);
    PositionInScreen centered = {.horizontal = POSITION_CENTER, .vertical = POSITION_CENTER};
    button.texture_rect = position_rect(centered, button.texture_rect, button.button_rect);
    return button;
}

SDL_Rect position_rect(PositionInScreen position, SDL_Rect rect, SDL_Rect zone) {
    rect.x = position_rect_x(position.horizontal, rect, zone);
    rect.y = position_rect_y(position.vertical, rect, zone);
    return rect;
}

int position_rect_x(HorizontalPosition position, SDL_Rect rect, SDL_Rect zone) {
    switch (position) {
        case POSITION_START:
            return zone.x;
        case POSITION_END:
            return zone.x + zone.w - rect.w;
        case POSITION_CENTER:
            return zone.x + ((zone.w - rect.w) / 2);
        case NOT_POSITIONED:
            return rect.x;
        default: {
            log_error("Unknown horizontal position [%d]", position);
            return rect.x;
        }
    }
}

int position_rect_y(VerticalPosition position, SDL_Rect rect, SDL_Rect zone) {
    switch (position) {
        case POSITION_START:
            return zone.y;
        case POSITION_END:
            return zone.y + zone.h - rect.h;
        case POSITION_CENTER:
            return zone.y + ((zone.h - rect.h) / 2);
        case NOT_POSITIONED:
            return rect.y;
        default: {
            log_error("Unknown vertical position [%d]", position);
            return rect.y;
        }
    }
}

Row position_row(PositionInScreen position, Row row, SDL_Rect zone) {
    row.position = position;

    row.rect = position_rect(position, row.rect, zone);
    for (int i = 0; i < row.length; i++) {
        row.cells[i] = position_row_cell_at_index(row, i);
    }
    return row;
}

RowCell position_row_cell_at_index(Row row, int index) {
    if (index >= row.length) {
        log_error("Index out of bounds [%d] in row (length = %d)", index, row.length);
        return (RowCell) {.cellType = CELL_ERROR};
    }
    int x = row.rect.x;
    for (int i = 0; i < index; i++) {
        x += get_cell_width(row.cells[i]);
        x += row.spacing;
    }
    UpdateRect update_rect = {.x = &x, .y = &row.rect.y, .w = NULL, .h = NULL};
    return set_row_cell_rect(row.cells[index], update_rect);
}

RowCell set_row_cell_rect(RowCell cell, UpdateRect rect) {
    switch (cell.cellType) {
        case CELL_ERROR:
            return cell;
        case BUTTON: {
            cell.cell.button.button_rect = update_rect(cell.cell.button.button_rect, rect);
            cell.cell.button.texture_rect = position_rect(
                    (PositionInScreen) {.horizontal = POSITION_CENTER, .vertical = POSITION_CENTER},
                    cell.cell.button.texture_rect,
                    cell.cell.button.button_rect
            );
            return cell;
        }
        default: {
            log_error("Unknown cell type [%d]", cell.cellType);
            return cell;
        }
    }
}


SDL_Rect update_rect(SDL_Rect rect, UpdateRect update) {
    if (update.x != NULL) rect.x = *update.x;
    if (update.y != NULL) rect.y = *update.y;
    if (update.y != NULL) rect.y = *update.y;
    if (update.y != NULL) rect.y = *update.y;

    return rect;
}

SDL_Rect window_rect(SDL_Window *window) {
    SDL_Rect window_zone = {.x = 0, .y = 0};
    SDL_GetWindowSize(window, &window_zone.w, &window_zone.h);
    return window_zone;
}

SDL_Rect safe_area_of(SDL_Rect rect, int top, int bottom) {
    return (SDL_Rect) {.x = 0, .y = top, .w = rect.w, .h = rect.h - (top + bottom)};
}

SDL_Rect default_safe_area(SDL_Rect rect) {
    return safe_area_of(rect, 40, 40);
}