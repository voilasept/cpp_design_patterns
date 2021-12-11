cmake_minimum_required(VERSION 3.21)
project(flyweight_manual)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

include_directories(/usr/local/cpplib/boost)
include_directories(/usr/local/cpplib/fplus/FunctionalPlus/include)

add_executable(flyweight_manual main.cpp)
