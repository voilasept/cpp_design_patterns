cmake_minimum_required(VERSION 3.21)
project(mediator_chatroom)

set(CMAKE_CXX_STANDARD 17)

add_executable(mediator_chatroom main.cpp person.h chatroom.h chatroom.cpp person.cpp)
