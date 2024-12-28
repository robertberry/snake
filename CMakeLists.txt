cmake_minimum_required(VERSION 3.30)
project(snake)

set(CMAKE_CXX_STANDARD 20)

set(SDL2_DIR "D:\\cpp\\SDL2-2.30.10\\x86_64-w64-mingw32")
include_directories("${SDL2_DIR}\\include")
# This is because the TTF path for some reason has a direct '#include "SDL.h"' ... who knows why.
include_directories("${SDL2_DIR}\\include\\SDL2")
link_directories("${SDL2_DIR}\\lib")

set(SDL2_TTF_DIR "D:\\cpp\\SDL2_ttf-2.22.0\\x86_64-w64-mingw32")
include_directories("${SDL2_TTF_DIR}\\include")
link_directories("${SDL2_TTF_DIR}\\lib")

add_executable(snake main.cpp
        RingBuffer.h
        FrameTimer.h
        Vector2i.h
        constants.h
        SnakeRenderer.h
        Grid.h
        Snake.h
        GameState.h
        SnakeRenderer.cpp
        GameState.cpp
)

target_link_libraries(snake SDL2 SDL2_ttf)

# Define the path to the font file in your source directory
set(FONT_FILE ${CMAKE_SOURCE_DIR}/resources/Silkscreen-Regular.ttf)

# Specify the destination directory for the font file in your build directory
set(DEST_FONT_DIR ${CMAKE_BINARY_DIR}/resources)

# Copy the font file during the build process
add_custom_command(TARGET snake POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${FONT_FILE} ${DEST_FONT_DIR}/Silkscreen-Regular.ttf
)
