cmake_minimum_required(VERSION 3.20)
project(lambda_expression)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

add_executable(lambda_expression main.cpp)
