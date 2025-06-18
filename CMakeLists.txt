cmake_minimum_required(VERSION 3.31)
project(battleship)

add_executable(battleship)

target_include_directories(battleship PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

target_sources(
    battleship
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src/field.c
    ${CMAKE_CURRENT_LIST_DIR}/src/main.c
)

set(CMAKE_C_STANDARD C99)
set(CMAKE_C_FLAGS "-Wall -std=c99")