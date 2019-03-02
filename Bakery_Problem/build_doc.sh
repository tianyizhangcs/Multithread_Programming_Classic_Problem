#!/bin/bash
rm -r build
mkdir build
cd build
cmake ..
make -j2
./CH2_bakery
