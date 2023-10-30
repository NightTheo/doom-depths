project(DoomDepthsUtils C)


add_library(UTILS
        utils.c
        random/random.c
        time/time_util.c
)

target_include_directories(UTILS PUBLIC ".")
