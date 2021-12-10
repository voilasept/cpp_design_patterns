cmake_minimum_required(VERSION 3.20)
project(adapter_hash_cached)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/cpplib/boost)
add_executable(adapter_hash_cached main.cpp)
