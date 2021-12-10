cmake_minimum_required(VERSION 3.20)
project(shared_ptr)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/cpplib/boost)
add_executable(shared_ptr main.cpp)
