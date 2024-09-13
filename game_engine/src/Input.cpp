#include "Input.h"

// Function to conver mouse click to coordinates to the board coordinates
bool get_board_coordinates(int mouse_x, int mouse_y, int& row, int& col) {
    const int TILE_SIZE = 75;
    if (mouse_x >= 0 && mouse_x < 8 * TILE_SIZE && mouse_y >= 0 && mouse_y < 8 * TILE_SIZE) {
        col = mouse_x / TILE_SIZE;
        row = mouse_y / TILE_SIZE;
        return true;
    }
    return false;
}
