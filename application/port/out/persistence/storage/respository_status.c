
//
// Created by Theo OMNES on 30/09/2023.
//

#include "respository_status.h"
#include "utils/log/log_error.h"
#include "utils/log/log_repository_status.h"

const char *repository_status_to_string(RepositoryStatus status) {
    switch (status) {
        case REPOSITORY_NOT_USED:
            return "REPOSITORY_NOT_USED";
        case RESTORE_LAST_GAME_SUCCEEDED:
            return "RESTORE_LAST_GAME_SUCCEEDED";
        case RESTORE_LAST_GAME_FAILED:
            return "RESTORE_LAST_GAME_FAILED";
        case SAVE_LAST_GAME_SUCCEEDED:
            return "SAVE_LAST_GAME_SUCCEEDED";
        case SAVE_LAST_GAME_FAILED:
            return "SAVE_LAST_GAME_FAILED";
        default:
            log_error("Unknown RepositoryStatus [%d]", status);
            return "?";
    }
}