cmake_minimum_required(VERSION 3.10)
project(5DayGameChalleng)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debuge)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g")
set(CMAKE_C_FLAGS_DEBUG "-O0 -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE"-O3")
set(CMAKE_C_FLAGS_RELEASE "-O0 -Wall")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

aux_source_directory(src SRC)
include_directories(include)

#add SDL
include_directories("/usr/local/include/SDL2")
link_libraries("-L/usr/local/lib -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2")

add_executable(play main.cpp ${SRC})
add_custom_command(TARGET play
            POST_BUILD 
            COMMAND cp ./compile_commands.json ../compile_commands.json)

add_subdirectory(test)
