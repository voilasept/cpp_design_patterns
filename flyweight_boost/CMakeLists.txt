cmake_minimum_required(VERSION 3.21)
project(flyweight_boost)

set(CMAKE_CXX_STANDARD 17)
include_directories(/usr/local/cpplib/boost)

add_executable(flyweight_boost main.cpp)
