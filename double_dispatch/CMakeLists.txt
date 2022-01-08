cmake_minimum_required(VERSION 3.21)
project(double_dispatch)

set(CMAKE_CXX_STANDARD 17)

# --------------- GOOGLE TEST -----------------
# git clone as project subdirectory
set(PATH_TO_GOOGLETEST /Users/hanchen/CLionProjects/double_dispatch/googletest)

#Add the google test subdirectory
add_subdirectory(${PATH_TO_GOOGLETEST})

#include googletest/include dir
include_directories(${PATH_TO_GOOGLETEST}/googletest/include)

#include the googlemock/include dir
include_directories(${PATH_TO_GOOGLETEST}/googlemock/include)
# ---------------------------------------------

add_executable(double_dispatch main.cpp visitor.h visitor.cpp expression.h expression.cpp)


# --------------- GOOGLE TEST -----------------
#Link with GoogleTest
target_link_libraries(double_dispatch gtest gtest_main)

#Link with GoogleMock
target_link_libraries(double_dispatch gmock gmock_main)
# ---------------------------------------------
