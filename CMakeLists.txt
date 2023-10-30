cmake_minimum_required(VERSION 3.26)
set(CMAKE_C_STANDARD 23)
project(DoomDepths C)

# CONAN - package manager
execute_process( COMMAND /bin/bash -c "conan install ${CMAKE_SOURCE_DIR} --build=missing" )
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/build/Release/generators/conan_toolchain.cmake")
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_COMPILER_VERSION 15)

add_subdirectory("domain")
add_subdirectory("utils")
add_subdirectory("application")
add_subdirectory("adapter/in/cli")
add_subdirectory("adapter/in/sdl")
add_subdirectory("adapter/out")

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})

# CLI
add_executable(DoomDepthsCLI main.c)
target_include_directories(DoomDepthsCLI PUBLIC "${CMAKE_SOURCE_DIR}")
target_link_libraries(DoomDepthsCLI BASIC_CLI)

# SDL
add_executable(DoomDepthsSDL main.c)
target_include_directories(DoomDepthsSDL PUBLIC "${CMAKE_SOURCE_DIR}")
target_link_libraries(DoomDepthsSDL SDL)
