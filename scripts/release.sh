#!/bin/bash

cd ..
mkdir -p build
cd build

cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release -j $(nproc)
