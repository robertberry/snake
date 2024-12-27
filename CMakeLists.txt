cmake_minimum_required(VERSION 3.30)
project(snake)

set(CMAKE_CXX_STANDARD 20)

set(SDL2_DIR "D:\\cpp\\SDL2-2.30.10\\x86_64-w64-mingw32")
include_directories("${SDL2_DIR}\\include")
link_directories("${SDL2_DIR}\\lib")

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

target_link_libraries(snake SDL2)
