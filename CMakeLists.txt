cmake_minimum_required(VERSION 3.23.1)

project(tetri VERSION 1.0)

set(SOURCES
    source/window.cpp
    main.cpp)

add_executable(tetris ${SOURCES})

target_include_directories(tetris
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include)