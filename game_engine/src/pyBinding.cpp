#include <pybind11/embed.h>
#include <iostream>
#include <string>
#include <map>

namespace py = pybind11;  // Nickname pybind11 to py

// Function to select a Python function based on game logic
std::string select_function_based_on_game_logic(const std::string& piece, const std::string& action) {
    // Define a map for game logic - mapping piece/action combinations to function names
    std::map<std::pair<std::string, std::string>, std::string> game_logic_map = {
        {{"pawn", "move"}, "pawn_move"},
        {{"pawn", "attack"}, "pawn_attack"},
        {{"knight", "move"}, "knight_move"},
        {{"knight", "attack"}, "knight_attack"},
        // Add the rest of the pieces here...
    };

    // Check if the piece/action combination exists in the map
    auto key = std::make_pair(piece, action);
    if (game_logic_map.find(key) != game_logic_map.end()) {
        return game_logic_map[key];
    } else {
        return ""; // Return an empty string if no match is found
    }
}

int main() {
    py::scoped_interpreter guard{};  // Start the interpreter

    // Load Python scripts dynamically
    try {
        py::exec(R"(
            # Import Python scripts
            import my_script
            from my_script import *
        )");
    } catch (py::error_already_set &e) {
        std::cerr << "Error loading Python script: " << e.what() << std::endl;
        return -1;
    }

    // Get the global Python dictionary
    py::dict globals = py::globals();

    std::string current_piece = "pawn";   // Example piece
    std::string current_action = "move";  // Example action

    // Select the function based on game logic
    std::string function_name = select_function_based_on_game_logic(current_piece, current_action);

    // Check if a function was selected
    if (!function_name.empty() && globals.contains(function_name.c_str())) {
        try {
            py::function func = globals[function_name.c_str()].cast<py::function>();
            std::cout << "Calling function: " << function_name << std::endl;
            func();  // Call the selected function
        } catch (const std::exception &e) {
            std::cerr << "Failed to call function: " << e.what() << std::endl;
        }
    } else {
        std::cerr << "No valid function found for the given game logic." << std::endl;
    }

    return 0;
}
