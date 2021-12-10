cmake_minimum_required(VERSION 3.20)
project(abstract_factory_drink)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

add_executable(abstract_factory_drink main.cpp drinks.h)
