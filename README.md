## furrowed

Simple (partially) UCI-compliant chess engine written in C++.

## Features

- Alpha-Beta search augmented with a simple Quiescence search
- 10x12 board representation
- Zobrist hashing

## Building furrowed with CMake

Building the engine locally with the provided CMake configuration is very simple.

First clone the repository and create a build folder:
```bash
git clone https://github.com/matoototo/furrowed.git
cd furrowed
mkdir build
cd build
```

After that, simply call cmake and make in succession:
```bash
cmake ..
make
```

The compiled executable will be in the newly created `./src/` directory.
