#!/bin/bash
# Compile main.cpp using g++

g++ src/main.cpp -o src/main -I/usr/include -L/usr/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Check if compilation succeeded
if [ $? -ne 0 ]; then
    echo
    echo "Compilation failed!"
    exit 1
fi

echo
echo "Compilation successful. Running program..."
echo

# Run the compiled program
./src/main

echo

