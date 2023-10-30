cmake_minimum_required(VERSION 3.26)
set(CMAKE_C_STANDARD 23)
project(DoomDepths C)

execute_process( COMMAND /bin/bash -c "conan install ${CMAKE_SOURCE_DIR} --build=missing" )

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/build/Release/generators/conan_toolchain.cmake")
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_COMPILER_VERSION 15)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)


add_subdirectory("domain")
add_subdirectory("utils")
add_subdirectory("application")
add_subdirectory("adapter/in/cli")
add_subdirectory("adapter/in/sdl")
add_subdirectory("adapter/out")

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})

add_executable(DoomDepths main.c)

target_include_directories(DoomDepths PUBLIC "${CMAKE_SOURCE_DIR}")

target_link_libraries(DoomDepths DOMAIN)
target_link_libraries(DoomDepths APPLICATION)
target_link_libraries(DoomDepths BASIC_CLI)
target_link_libraries(DoomDepths SDL)
target_link_libraries(DoomDepths INFRASTRUCTURE)
target_link_libraries(DoomDepths UTILS)
