cmake_minimum_required(VERSION 3.30)
project(SYH_DA_CA3_Stage_1_Bugs)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)


add_executable(SYH_DA_CA3_Stage_1_Bug
        Bug.cpp
        Board.cpp
        Crawler.cpp
        Hopper.cpp
        Zigzagger.cpp
        main.cpp)

