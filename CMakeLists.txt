cmake_minimum_required(VERSION 3.28)
project(yahtzee)

set(CMAKE_CXX_STANDARD 26)

include_directories(src)
include_directories(include)
include_directories(Diagrams)

add_executable(yahtzee main.cpp
        src/dice.cpp
        src/game.cpp
        src/player.cpp
        src/scorecard.cpp)
