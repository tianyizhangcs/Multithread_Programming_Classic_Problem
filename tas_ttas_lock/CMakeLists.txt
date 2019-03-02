# Copyright (c) 2018 Tianyi Zhang
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
cmake_minimum_required(VERSION 3.10)
project(programming CXX)
add_executable(CH7_lock_tas CH7_lock_tas.cpp)
add_executable(CH7_lock_ttas CH7_lock_ttas.cpp)
TARGET_LINK_LIBRARIES(CH7_lock_tas pthread)
TARGET_LINK_LIBRARIES(CH7_lock_ttas pthread)
