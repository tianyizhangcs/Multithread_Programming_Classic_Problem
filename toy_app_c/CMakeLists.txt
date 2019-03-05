cmake_minimum_required(VERSION 3.9)
project(multithread_1 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS -pthread)
add_executable(multithread_1 main.c)