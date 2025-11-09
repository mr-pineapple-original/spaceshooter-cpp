cmake_minimum_required(VERSION 3.10)
project(SpaceshooterCPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- SFML 3.x syntax ---
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(game src/main.cpp)

target_link_libraries(game PRIVATE SFML::Graphics SFML::Window SFML::System)

