#!/bin/bash

# Script to build and run tests

# Create build directory if it doesn't exist
mkdir -p build

# Navigate to build directory
cd build

# Run CMake
echo "Running CMake..."
cmake ..

# Build the tests
echo "Building tests..."
cmake --build . --target run_tests

# Run the tests
echo "Running tests..."
./run_tests

# Return to original directory
cd ..
