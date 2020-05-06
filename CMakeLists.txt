cmake_minimum_required(VERSION 3.10)
project("ChaoseDungeon")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g")
set(CMAKE_C_FLAGS_DEBUG "-O0 -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE"-O3")
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

aux_source_directory(${CMAKE_SOURCE_DIR}/src/Common SRC)
include_directories(${CMAKE_SOURCE_DIR}/include/Common)
include_directories(${CMAKE_SOURCE_DIR}/include)

#add SDL2, SDL2_image, SDL2_mixer
include_directories("${CMAKE_SOURCE_DIR}/include/deps/SDL")
link_directories("${CMAKE_SOURCE_DIR}/libs/SDL")
link_directories("${CMAKE_SOURCE_DIR}/libs/SDL_image")
link_directories("${CMAKE_SOURCE_DIR}/libs/SDL_mixer")
link_libraries(mingw32 SDL2main SDL2 SDL2_image SDL2_mixer)
add_definitions(-Dmain=SDL_main)


#add glew and glm
set(GLEW_USE_STATIC_LIBS ON)
include_directories("./include/deps/OpenGL")
link_directories("./libs/glew")
link_libraries(glew32.lib glew32s.lib)

#add OpenGL
find_package(OpenGL)
if(OpenGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    link_libraries(${OPENGL_LIBRARIES})
    message(STATUS "found OpenGL")
else()
    message(FATAL_ERROR "can't find OpenGL")
endif()

#link myself lib
add_library(common STATIC ${SRC})
link_libraries("-L${CMAKE_BINARY_DIR} -lcommon")

#generate executable
set(APP_NAME "Chaose_Dungeon")
aux_source_directory(src/GameBody DEP_SRC)
aux_source_directory(src/Sprite DEP_SRC)
add_executable(${APP_NAME} main.cpp ${DEP_SRC})
target_link_libraries(${APP_NAME} "common")
add_custom_command(TARGET ${APP_NAME}
    POST_BUILD 
    COMMAND cp ./compile_commands.json ../compile_commands.json)

install(
    TARGETS ${APP_NAME}
    DESTINATION ${CMAKE_SOURCE_DIR}/Chaose_Dungeon
    )
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/resources
    DESTINATION ${CMAKE_SOURCE_DIR}/Chaose_Dungeon
    )
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/shader
    DESTINATION ${CMAKE_SOURCE_DIR}/Chaose_Dungeon
    )

add_subdirectory(test)
