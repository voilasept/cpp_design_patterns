cmake_minimum_required(VERSION 3.21)
project(multi_thread_signal_slots)

set(CMAKE_CXX_STANDARD 17)
include_directories(/usr/local/cpplib/boost)
add_executable(multi_thread_signal_slots main.cpp)
