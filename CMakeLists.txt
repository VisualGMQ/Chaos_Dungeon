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

#find pkg-config
find_package(PkgConfig REQUIRED)

#add SDL2, SDL2_image, SDL2_mixer
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
link_libraries(${SDL2_LIBRARIES})
pkg_search_module(SDL2_image REQUIRED sdl2_image)
include_directories("/usr/local/include/SDL2")
link_directories("/usr/local/lib")
link_libraries("SDL2_image")
link_libraries("SDL2_mixer")

#add glm
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
link_libraries("glm")

#add glew use pkg-config
set(GLEW_USE_STATIC_LIBS ON)
pkg_search_module(GLEW REQUIRED glew)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

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
