project(DoomDepthsInfrastructure C)

add_library(INFRASTRUCTURE
        custom_file_repository/restore_last_game.c
        custom_file_repository/save_game_state.c
        ihm/cli/cli_display_loot.c
        in_memory_intern_game_state/in_memory_intern_game_state.c
        ihm/cli/cli_display_game_over.c
)

target_include_directories(INFRASTRUCTURE PUBLIC ".")

target_link_libraries(INFRASTRUCTURE UTILS)
target_link_libraries(INFRASTRUCTURE APPLICATION)