cmake_minimum_required(VERSION 3.9)
project(producer_consumer_ex C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS -pthread)

add_executable(producer_consumer_ex main.c)