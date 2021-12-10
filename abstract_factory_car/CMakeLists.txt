cmake_minimum_required(VERSION 3.20)
project(abstract_factory_car)

set(CMAKE_CXX_STANDARD 17)

add_executable(abstract_factory_car main.cpp car.h car_factory.h)
