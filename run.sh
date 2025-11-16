#!/bin/bash
# Compile main.cpp using g++

g++ src/main.cpp src/obstacle.cpp src/alien.cpp -o src/main -I/usr/include -L/usr/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Check if compilation succeeded
if [ $? -ne 0 ]; then
    echo
    echo -e "\e[31mCompilation failed!\e[0m"

    exit 1
fi

echo
echo -e "\e[32mCompilation successful. Running program...e[0m"
echo

# Run the compiled program
./src/main

echo
