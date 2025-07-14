cmake_minimum_required(VERSION 3.10)
project(2048Puzzle CXX)

include_directories(src/include)

add_executable(server src/include/server.cpp)
add_executable(client src/include/client.cpp)