cmake_minimum_required(VERSION 3.9)
project(multithread_1_c__)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(multithread_1_c__ main.cpp)