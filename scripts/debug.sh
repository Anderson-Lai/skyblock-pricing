#!/bin/bash

cd ..
mkdir -p build
cd build

cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug
