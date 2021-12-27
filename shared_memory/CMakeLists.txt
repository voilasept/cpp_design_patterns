cmake_minimum_required(VERSION 3.21)
project(shared_memory)

set(CMAKE_CXX_STANDARD 17)
include_directories(/usr/local/cpplib/boost)
add_executable(shared_memory main.cpp)
