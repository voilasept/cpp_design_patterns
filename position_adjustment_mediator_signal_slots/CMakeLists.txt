cmake_minimum_required(VERSION 3.21)
project(position_adjustment_mediator_signal_slots)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/cpplib/boost)
add_executable(position_adjustment_mediator_signal_slots main.cpp position_mediator.h strategy.h postion_mediator.cpp strategy.cpp)
