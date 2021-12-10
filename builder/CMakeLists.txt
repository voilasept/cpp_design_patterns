cmake_minimum_required(VERSION 3.20)
project(builder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror" )

add_executable(builder main.cpp)