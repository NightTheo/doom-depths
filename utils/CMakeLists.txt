project(DoomDepthsUtils C)


add_library(UTILS
        utils.c
        random/random.c
        time/time_util.c
        log/cli_log.c
)

target_include_directories(UTILS PUBLIC ".")

target_link_libraries(UTILS DOMAIN)
