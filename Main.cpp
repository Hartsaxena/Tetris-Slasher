/*
Driver file.
*/

#include <SDL.h>
#include <iostream>
#include "Front.hpp"
#include "Blocks.hpp"
#include "Render.hpp" 
#include "Tetris.hpp"

int main(int argc, char* argv[]) {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    FrontendManager frontend(800, 600, 60, "Tetris Game");
    TetrisGrid tetrisGrid(frontend.renderer);
    Canvas canvas(frontend.renderer);
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        // Handle inputs
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Handle keyboard inputs for WASD movement
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL); // Get current state of the keyboard

        if (currentKeyStates[SDL_SCANCODE_A]) {
            tetrisGrid.MovePiece(-1, 0); // Move left
        }
        if (currentKeyStates[SDL_SCANCODE_D]) {
            tetrisGrid.MovePiece(1, 0); // Move right
        }
        if (currentKeyStates[SDL_SCANCODE_S]) {
            tetrisGrid.MovePiece(0, 1); // Move down
        }
        if (currentKeyStates[SDL_SCANCODE_W]) {
            tetrisGrid.RotatePiece(); // Rotate
        }

        tetrisGrid.Update();
        tetrisGrid.Render();
        SDL_Delay(100); // Control game speed
    }

    return 0;
}
