#!/bin/bash

CONAN_USER_HOME="/opt/conan_home"

source ~/.venv/dyntopiclib/bin/activate

conan install . --output-folder=build --build=missing -oarrow/*:parquet=True

mkdir -p build
cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake" #-DCMAKE_BUILD_TYPE=Release

make && ./parquet_writer 