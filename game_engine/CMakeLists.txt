cmake_minimum_required(VERSION 3.10)

# Set the project Name and Version
project(gameEngine VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SDL2 library
find_package(SDL2 REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})

# Add the executable
add_executable(gameEngine src/main.cpp src/cpp/SpecialState.cpp src/cpp/GameState.cpp src/cpp/ChessPiece.cpp src/cpp/Input.cpp src/cpp/Renderer.cpp)

# Link SDL2 to the executable
target_link_libraries(gameEngine ${SDL2_LIBRARIES})

