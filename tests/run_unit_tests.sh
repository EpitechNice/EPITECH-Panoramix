#!/bin/bash

echo "=== Started the Unit testing ==="

# Run tests
mkdir -p ./build/
cd ./build/
cmake ..
cmake --build .
echo "===== Running Tests ====="
ctest --output-on-failure || echo "=== Unit testing failed ===" && exit 1

echo "=== Unit testing ended gracefully ==="
