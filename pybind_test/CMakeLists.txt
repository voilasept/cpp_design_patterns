cmake_minimum_required(VERSION 3.21)
project(pybind_test)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/Cellar/python@3.9/3.9.9/Frameworks/Python.framework/Versions/3.9/include/python3.9)
include_directories(/usr/local/cpplib/pybind11/include)
add_executable(pybind_test main.cpp hello_world.cpp)
