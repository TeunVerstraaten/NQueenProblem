cmake_minimum_required(VERSION 3.23)
project(NQueen)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-O3 -Werror -Wall -Wextra")

add_executable(NQueen main.cpp src/PartialBoard.h src/NQueen.h src/NumberOfCores.h)

target_link_libraries(NQueen pthread)