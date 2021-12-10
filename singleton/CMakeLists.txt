cmake_minimum_required(VERSION 3.20)
project(singleton)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(LIBDIR /usr/local/cpplib)

include_directories(${LIBDIR}/boost)
add_executable(singleton main.cpp)
