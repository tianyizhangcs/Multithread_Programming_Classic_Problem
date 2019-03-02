#!/bin/bash
mkdir build_ch7_
cd build_ch7_
cmake ..
make -j

for i in 1 2 3
do
echo "Running $i times using tas"
./CH7_lock_tas $i
done

for i in 1 2 3
do
echo "Running $i times using ttas"
./CH7_lock_ttas $i
done
