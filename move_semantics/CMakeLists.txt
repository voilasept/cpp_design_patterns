cmake_minimum_required(VERSION 3.20)
project(study)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors" )

add_executable(study holder.h main.cpp)

set(LIBDIR /usr/local/cpplib)
set(PROJDIR /Users/hanchen/CLionProjects)
include_directories(${LIBDIR}/boost)
include_directories(${PROJDIR})