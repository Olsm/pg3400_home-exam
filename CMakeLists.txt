cmake_minimum_required(VERSION 3.6)
project(pg3400_home_exam)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

set(SOURCE_FILES main.c board.c game.c)
add_executable(pg3400_home_exam ${SOURCE_FILES})