#!/bin/bash

cd ..
mkdir -p build
cd build

cmake ..
cmake --build . --config Release
