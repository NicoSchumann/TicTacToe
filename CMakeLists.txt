cmake_minimum_required(VERSION 3.22.1)

project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(include)

link_libraries(sfml-window sfml-system sfml-graphics)

file(GLOB project_SRCS ./src/*.cpp)

project(TicTacToe)


add_executable(tictactoe ${project_SRCS})