cmake_minimum_required(VERSION 3.20)
project(dependency_principal)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror" )

add_executable(dependency_principal main.cpp)
