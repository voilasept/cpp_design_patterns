cmake_minimum_required(VERSION 3.21)
project(double_dispatch)

set(CMAKE_CXX_STANDARD 17)

add_executable(double_dispatch main.cpp visitor.h visitor.cpp expression.h expression.cpp)
