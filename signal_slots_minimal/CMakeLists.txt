cmake_minimum_required(VERSION 3.21)
project(signal_slots_minimal)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

include_directories(/usr/local/cpplib/boost)

add_executable(signal_slots_minimal main.cpp)
