cmake_minimum_required(VERSION 3.19)
project(hw5)

set(CMAKE_CXX_STANDARD 14)

add_executable(hw5
        main.cpp BoardGame2D.cpp BoardGame2D.h PegSolitaire.h PegSolitaire.cpp EightGame.cpp EightGame.h Klotski.cpp Klotski.h)
