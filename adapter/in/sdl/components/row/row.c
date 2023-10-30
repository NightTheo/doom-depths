
//
// Created by Theo OMNES on 15/10/2023.
//

#include "row.h"
#include "log/log_error.h"
#include "log/log_info.h"

#include "in/sdl/sdl_controller.h"
#include "in/sdl/components/event/event.h"

int get_cell_height(RowCell param);

Row update_row_rect(Row row);

RowCell button_row_cell(Button button);

void draw_row_cell(RowCell cell, SDL_Renderer *renderer);

ButtonEvent cell_handle_event(SDL_IHM ihm, SDL_Event event, RowCell cell);

Row row_with_cell_at_index(Row row, RowCell cell, int index);

Row row_handle_aria_next(SDL_IHM ihm, SDL_Event event, Row row);

Row select_button_by_id(const char *id, Row row);

Row create_row_with_indexes(int length, ...) {
    Row row;
    row.length = length;
    row.cells = malloc(sizeof(RowCell) * length);
    row.spacing = 0;
    row.rect = (SDL_Rect) {.x = 0, .y = 0, .w = 0, .h = 0};
    row.aria = create_aria(length);

    va_list args;
    va_start(args, length);
    for (int i = 0; i < length; ++i) {
        int index = va_arg(args, int);
        row.cells[index] = row_cell_by_type(va_arg(args, CellType), va_arg(args, Button));
        int cell_height = get_cell_height(row.cells[index]);
        if(cell_height > row.rect.h) row.rect.h = cell_height;
        row.rect.w += get_cell_width(row.cells[index]);
    }
    va_end(args);

    for(int i = 0; i < length; i++) {
        aria_add(row.aria, row.cells[i].cell.button.id);
    }
    return row;
}

Cell cell_by_type(CellType cellType, void* data) {
    switch (cellType) {
        case BUTTON: return (Cell) {.button = *((Button*) data)};
        default: {
            log_error("cell_by_type: unknown cell type [%d]", cellType);
            return (Cell) {.error = {.message = "Unknown cell type"}};
        }
    }
}

RowCell row_cell_by_type(CellType cellType, Button cell) {
    switch (cellType) {
        case BUTTON: return (RowCell) {.cellType = cellType, .cell.button = cell};
        default: {
            log_error("row_cell_by_type: unknown cell type [%d]", cellType);
            return (RowCell) {.cellType = BUTTON, .cell = cell};
        }
    }
}

int get_cell_width(RowCell param) {
    switch (param.cellType) {
        case BUTTON: {
            return param.cell.button.button_rect.w;
        }
        default: {
            log_error("get_cell_width: unknown cell type [%d]", param.cellType);
            return 0;
        }
    }
}

int get_cell_height(RowCell param) {
    switch (param.cellType) {
        case BUTTON: return param.cell.button.size.height;
        default: {
            log_error("get_cell_height: unknown cell type [%d]", param.cellType);
            return 0;
        }
    }
}


Row row_with_row_button_at_index(Row row, Button button, uint16_t index) {
    if(index >= row.length) {
        log_error("row_with_row_button_at_index: index [%d] out of bounds", index);
        return row;
    }
    row.cells[index] = button_row_cell(button);
    return update_row_rect(row);
}

RowCell button_row_cell(Button button) {
    return (RowCell) {
        .cellType = BUTTON,
        .cell = button,
    };
}

Row update_row_rect(Row row) {
    row.rect.w = 0;
    for(int i = 0; i < row.length; i++) {
        int cell_height = get_cell_height(row.cells[i]);
        if(cell_height > row.rect.h) row.rect.h = cell_height;
        row.rect.w += get_cell_width(row.cells[i]);
    }
    return row;
}

RowCell get_button_in_row_at_index(Row row, uint16_t index) {
    RowCell cell = row.cells[index];
    if(cell.cellType != BUTTON) {
        return (RowCell) {.cellType = CELL_ERROR};
    }
    return cell;
}


Row spacing_row(uint8_t spacing, Row row) {
    row.spacing = spacing;
    row.rect.w += (row.length - 1) * spacing;
    return row;
}

Row update_row_position_in_zone(Row row, SDL_Rect zone) {
    return position_row(row.position, row, zone);
}

void draw_row(SDL_Renderer *renderer, Row row) {
    for(int i = 0; i < row.length; i++) {
        draw_row_cell(get_button_in_row_at_index(row, i), renderer);
    }
}

void draw_row_cell(RowCell cell, SDL_Renderer *renderer) {
    switch (cell.cellType) {
        case BUTTON: {
            draw_button(renderer, cell.cell.button);
            break;
        }
        default: {
            log_error("draw_row: unknown cell type [%d]", cell.cellType);
        }
    }
}

Row row_handle_event(SDL_Event event, SDL_IHM ihm, Row row) {
    row = row_handle_aria_next(ihm, event, row);

    for(int i = 0; i < ihm.page.fight.buttons.length; i++) {
        RowCell row_cell = row.cells[i];
        ButtonEvent e = cell_handle_event(ihm, event, row_cell);
        ihm = e.ihm;
        row_cell = row_cell_by_type(row_cell.cellType, e.button);
        row = row_with_cell_at_index(row, row_cell, i);
    }
    return row;
}

Row row_handle_aria_next(SDL_IHM ihm, SDL_Event event, Row row) {
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_TAB) {
        row.aria = aria_next(row.aria);
    }
    const char *selected_id = row.aria.selected->id;
    if(selected_id == NULL) return row;

    return select_button_by_id(selected_id, row);
}

Row select_button_by_id(const char *id, Row row) {
    for(int i = 0; i < row.length; i++) {
        if(strcmp(id, row.cells[i].cell.button.id) == 0) {
            row.cells[i].cell.button = select_button(row.cells[i].cell.button);
        } else {
            row.cells[i].cell.button = unselect_button(row.cells[i].cell.button);
        }
    }
    return row;
}

Row row_with_cell_at_index(Row row, RowCell cell, int index) {
    if(index >= row.length) {
        log_error("row_with_row_button_at_index: index [%d] out of bounds", index);
        return row;
    }
    row.cells[index] = cell;
    return update_row_rect(row);
}

// TODO Generify events
ButtonEvent cell_handle_event(SDL_IHM ihm, SDL_Event event, RowCell cell) {
    switch (cell.cellType) {
        case CELL_ERROR: return button_event_not_handled(ihm, cell.cell.button);
        case BUTTON: return button_handle_event(ihm, event, cell.cell.button);
        default: {
            log_error("cell_handle_event: unknown cell type [%d]", cell.cellType);
            return button_event_not_handled(ihm, cell.cell.button);
        }
    }
}
