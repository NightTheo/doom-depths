
//
// Created by Theo OMNES on 30/09/2023.
//

#include <stdio.h>
#include "respository_status.h"
#include "../../utils/log/log.h"

const char* repository_status_to_string(RepositoryStatus status) {
    char log[64];
    switch (status) {
        case REPOSITORY_NOT_USED: return "REPOSITORY_NOT_USED";
        case RESTORE_LAST_GAME_SUCCEEDED: return "RESTORE_LAST_GAME_SUCCEEDED";
        case RESTORE_LAST_GAME_FAILED: return "RESTORE_LAST_GAME_FAILED";
        case SAVE_LAST_GAME_SUCCEEDED: return "SAVE_LAST_GAME_SUCCEEDED";
        case SAVE_LAST_GAME_FAILED: return "SAVE_LAST_GAME_FAILED";
        default:
            snprintf(log, 64, "Unknown RepositoryStatus [%d]", status);
            log_error(log);
            return "?";
    }
}

void log_repository_status(RepositoryStatus status) {
    char log[64];
    const char* status_str = repository_status_to_string(status);
    snprintf(log, 64, "Repository status: [%s]", status_str);
}