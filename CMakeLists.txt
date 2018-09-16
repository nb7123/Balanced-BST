cmake_minimum_required(VERSION 3.10)
project(BalancedBTree)

set(CMAKE_CXX_STANDARD 11)

add_executable(BalancedBTree
        src/BBTree.cpp
        src/BBTree.h
        src/Node.cpp
        src/Node.h
        main.cpp)