
# Game Engine Project

This repository contains a basic C++ game engine with Python bindings and SDL2 for window rendering. The project is set up with a CMake build system for easy compilation and management of dependencies.

## Installation

Before building and running the game, you need to install the following packages:

### Packages needed:
- **g++**: C++ compiler  
  ```bash
  sudo apt-get install g++
  ```
- **CMake**: Build system generator  
  ```bash
  sudo apt-get install cmake
  ```
- **pybind11**: Python to C++ bindings (install via pip)  
  ```bash
  pip install pybind11
  ```
- **SDL2 development library**: For windowing, rendering, and handling input  
  ```bash
  sudo apt install libsdl2-dev
  ```

## File Structure

The project is organized into separate folders for header files (`src/header/`) and source files (`src/cpp/`):

```
.
├── src/
|   ├── main.cpp               # The main entry point of the program. It contains the game loop and integrates all modules.
|   ├── header/
│       ├── GameState.h        # Contains the declaration of GameState class, which manages the game state.
│       ├── Input.h            # Contains the function declaration to handle mouse input.
│       ├── Renderer.h         # Contains the declarations for rendering the chessboard and pieces.
|   ├── cpp/         
│       ├── GameState.cpp      # Defines the game state logic, including initializing the board and handling piece moveme
│       ├── Input.cpp          # Handles user input like mouse clicks and converts to board coordinates.
│       ├── Renderer.cpp       # Implements rendering logic for drawing the chessboard and pieces using SDL2.
├── CMakeLists.txt         # CMake configuration file that describes how to build the project.
└── README.md              # Project documentation.
```

## Build Instructions

Follow these steps to build the game executable:

1. **Clone the repository:**
   ```bash
   git clone https://github.com/ohuweih/gameEngine.git
   cd gameEngine
   ```

2. **Create a build directory:**
   ```bash
   mkdir build
   cd build
   ```

3. **Run CMake to configure the project:**
   ```bash
   cmake ..
   ```

4. **Build the project using make:**
   ```bash
   make
   ```

5. **Run the executable:**
   ```bash
   ./gameEngine
   ```

This will launch the game window with the main game loop.

## How it Works

### Core Components:
- **GameState:** Manages the current game state, including the position of chess pieces and turn-based logic.
- **Renderer:** Responsible for rendering the chessboard and pieces using SDL2.
- **Input:** Handles user input (e.g., mouse clicks) to select and move pieces on the board.

### Future Features:
- Implementation of Python bindings using `pybind11` for scripting support.
- Advanced game logic and mini-games for piece captures.

---

Enjoy working with the game engine! Feel free to contribute, suggest features, or report issues.
