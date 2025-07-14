cmake_minimum_required(VERSION 3.10)
project(2048Puzzle CXX)

include_directories(src/include)
include_directories(third_party/Crow/include)
include_directories(third_party/asio-1.30.2/include)

add_compile_definitions(BOOST_ASIO_STANDALONE)

add_executable(game-logic src/game_logic_test.cpp src/game_logic.cpp src/utils.cpp)
add_executable(user-logic src/user_logic_test.cpp src/user_logic.cpp src/utils.cpp)
add_executable(server src/server.cpp src/game_logic.cpp src/game_logic.cpp src/utils.cpp)