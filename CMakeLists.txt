cmake_minimum_required(VERSION 3.17)
project(assignments)

set(CMAKE_CXX_STANDARD 20)

add_executable(assignments main.cpp Graph.h Graph.cpp)
add_executable(maintest main.cpp)