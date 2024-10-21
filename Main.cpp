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
    Canvas canvas = Canvas(frontend.renderer);
    TetrisGrid grid(&canvas);
    InputManager inputter = InputManager();
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        // Handle inputs
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            // Handle keyboard inputs for WASD movement
            const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL); // Get current state of the keyboard
            inputter.HandleInputs();

            if (inputter.getKeyState(SDL_SCANCODE_A)) {
                std::cout << "Moving LEFT\n";
                grid.moveLeft(); // Move left
            }
            if (inputter.getKeyState(SDL_SCANCODE_D)) {
                std::cout << "Moving RIGHT\n";
                grid.moveRight(); // Move right
            }
            if (inputter.getKeyState(SDL_SCANCODE_S)) {
                std::cout << "Moving DOWN\n";
                grid.moveDown(); // Move down
            }
            if (inputter.getKeyState(SDL_SCANCODE_W) || inputter.getKeyState(SDL_SCANCODE_R)) {
                // grid.RotatePiece(); // Rotate
            }
        }
            canvas.displayInt(grid.pointCount, 30);
            grid.render();
            frontend.PresentRenderer();
            if (!grid.update()) {
                break;
            }
            frontend.PauseDelay();
        }

        
        return 0;
    }