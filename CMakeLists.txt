cmake_minimum_required(VERSION 3.10)
project(7DayGameChalleng)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debuge)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g")
set(CMAKE_C_FLAGS_DEBUG "-O0 -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE"-O3")
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options("-g")

aux_source_directory(${CMAKE_SOURCE_DIR}/src/Common SRC)
include_directories(${CMAKE_SOURCE_DIR}/include/Common)
include_directories(${CMAKE_SOURCE_DIR}/include)

#add SDL
include_directories("/usr/local/include/SDL2")
link_libraries("-L/usr/local/lib -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2")
#add glew
include_directories("/usr/local/Cellar/glew/2.1.0_1/include")
link_libraries("-L/usr/local/Cellar/glew/2.1.0_1/lib -lGLEW")
#add OpenGL
find_package(OpenGL)
if(OpenGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    link_libraries(${OPENGL_LIBRARIES})
    message(STATUS "found OpenGL")
else()
    message(FATAL_ERROR "can't find OpenGL")
endif()
#add glm
include_directories("/usr/local/Cellar/glm/0.9.9.5/include")

#link myself lib
add_library(common STATIC ${SRC})
link_libraries("-L${CMAKE_BINARY_DIR} -lcommon")

#generate executable
aux_source_directory(${CMAKE_SOURCE_DIR}/src/GameBody DEP_SRC)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/Sprite DEP_SRC)
add_executable(play main.cpp ${DEP_SRC})
target_link_libraries(play "common")
add_custom_command(TARGET play
            POST_BUILD 
            COMMAND cp ./compile_commands.json ../compile_commands.json)

add_subdirectory(test)
