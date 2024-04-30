#!/bin/bash

echo "=== Started the Unit testing ==="

mkdir -p ./build/
cd ./build/
cmake ..
cmake --build .
echo "===== Running Tests ====="
ctest --output-on-failure || exit 1

echo "=== Unit testing ended gracefully ==="
