
cmake_minimum_required(VERSION 3.16)
project(SpaceShooter)

set(CMAKE_CXX_STANDARD 20)
file(GLOB SRC "src/*.cpp")
add_executable(${PROJECT_NAME} ${SRC})

# SFML paths
set(SFML_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third_party/SFML-3.0.2")
include_directories("${SFML_ROOT}/include")
link_directories("${SFML_ROOT}/lib")
set(SFML_LIB_DIR "${SFML_ROOT}/lib")
# Link manually (adjust names if using static libraries)
# target_link_libraries(${PROJECT_NAME}
#     "${SFML_LIB_DIR}/libsfml-graphics.a"
#     "${SFML_LIB_DIR}/libsfml-window.a"
#     "${SFML_LIB_DIR}/libsfml-system.a"
# )
if(WIN32)
    # Windows linking
    target_link_libraries(${PROJECT_NAME}
        "${SFML_ROOT}/lib/libsfml-graphics.a"
        "${SFML_ROOT}/lib/libsfml-window.a"
        "${SFML_ROOT}/lib/libsfml-system.a"
    )
elseif(UNIX AND NOT APPLE)
    # Linux linking
    target_link_libraries(${PROJECT_NAME}
        sfml-graphics
        sfml-window
        sfml-system
    )
endif() 
