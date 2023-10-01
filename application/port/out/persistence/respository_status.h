
//
// Created by Theo OMNES on 30/09/2023.
//

#ifndef DOOMDEPTHS_RESPOSITORY_STATUS_H
#define DOOMDEPTHS_RESPOSITORY_STATUS_H

typedef enum RepositoryStatus {
    REPOSITORY_NOT_USED,
    RESTORE_LAST_GAME_SUCCEEDED,
    RESTORE_LAST_GAME_FAILED,
    SAVE_LAST_GAME_SUCCEEDED,
    SAVE_LAST_GAME_FAILED,
} RepositoryStatus;

const char *repository_status_to_string(RepositoryStatus status);

#endif //DOOMDEPTHS_RESPOSITORY_STATUS_H
