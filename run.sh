#!/usr/bin/env bash
set -e

# Project paths
BUILD_DIR="build"
EXECUTABLE="SpaceShooter"

# Create build directory if missing
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

# Enter build directory
cd "$BUILD_DIR"

# Run CMake configuration if no cache exists
if [ ! -f "CMakeCache.txt" ]; then
    echo "[CMake] Configuring project..."
    cmake ..
fi

# Build using all available CPU cores
echo "[Build] Compiling..."
cmake --build . -- -j"$(nproc)"

# Go back to project root
cd ..

# Run the compiled program if it exists
if [ -f "$BUILD_DIR/$EXECUTABLE" ]; then
    echo "[Run] Launching program..."
    "./$BUILD_DIR/$EXECUTABLE"
else
    echo "[Error] Executable not found: $BUILD_DIR/$EXECUTABLE"
    exit 1
fi

