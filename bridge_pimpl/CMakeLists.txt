cmake_minimum_required(VERSION 3.21)
project(bridge_pimpl)

set(CMAKE_CXX_STANDARD 17)

add_executable(bridge_pimpl main.cpp person.h person.cpp)
