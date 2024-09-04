#!/bin/bash

cd ..
mkdir -p build
cd build

cmake ..
mv compile_commands.json ../
