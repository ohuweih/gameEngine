cmake_minimum_required(VERSION 3.10)

# Set the project Name and Version
project(gameEngine VERSION 1.0)

# Specify the C++ standard
set(CAMKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SDL2 library
find_package(SDL2 REQUIRED)

# Inclue SDL2 headers
include_directories(${SDL2_Include_DIRS})

# Add the executable
add_executable(gameEngine src/main.cpp src/GameState.cpp src/Renderer.cpp src/Input.cpp)

# Link SDL2 to the executable
target_link_libraries(gameEngine ${SDL2_LIBRARIES})
