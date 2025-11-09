
cmake_minimum_required(VERSION 3.16)
project(SpaceShooter)

set(CMAKE_CXX_STANDARD 20)

# Add source files
file(GLOB SRC "src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC})

# Set SFML paths
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/SFML/lib/cmake/SFML")

# Tell CMake to use local SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

# Optional: copy DLLs to output folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/third_party/SFML/bin"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

