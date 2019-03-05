cmake_minimum_required(VERSION 3.10)
project(programming)

set(CMAKE_CXX_STANDARD 11)

add_executable(dining_philosophers EX1_dining_philosophers.cpp)
TARGET_LINK_LIBRARIES(dining_philosophers pthread)

add_executable(producer-consumer EX3_producer-consumer.cpp)
TARGET_LINK_LIBRARIES(producer-consumer pthread)

add_executable(hat_color EX5_hat_color.cpp)