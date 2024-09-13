#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "GameState.h"

// Render Chessboard
void render_chessboard(SDL_Renderer* renderer);

// render chess pieces
void render_pieces(SDL_Renderer* renderer, const GameState& game_state);

#endif
