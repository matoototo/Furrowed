#!/bin/bash

clang++ ./src/*.cpp -o furrowed -O3 -Wno-c++17-extensions
./furrowed
rm furrowed
