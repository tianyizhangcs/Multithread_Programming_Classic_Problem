cmake_minimum_required(VERSION 3.10)
project(programming)
add_executable(CH2_bakery CH2_bakery.cpp)
TARGET_LINK_LIBRARIES(CH2_bakery pthread)
