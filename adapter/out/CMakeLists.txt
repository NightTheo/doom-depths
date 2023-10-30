project(DoomDepthsInfrastructure C)

add_library(INFRASTRUCTURE
        out/custom_file_repository/restore_last_game.c
        out/custom_file_repository/save_game_state.c
        out/ihm/cli/cli_display_loot.c
        out/in_memory_intern_game_state/in_memory_intern_game_state.c
        out/ihm/cli/cli_display_game_over.c
)

target_include_directories(ADAPTER PUBLIC ".")