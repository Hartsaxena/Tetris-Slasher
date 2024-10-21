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

    while (isRunning) {

        // Handle Events and update keyboard
        isRunning = inputter.HandleInputs();

        // Handle keyboard inputs for WASD movement
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL); // Get current state of the keyboard

        if (inputter.getKeyState(SDL_SCANCODE_A) == True || inputter.getKeyState(SDL_SCANCODE_LEFT) == True) {
            std::cout << "Moving LEFT\n";
            grid.moveLeft(); // Move left
        }
        if (inputter.getKeyState(SDL_SCANCODE_D) == True || inputter.getKeyState(SDL_SCANCODE_RIGHT) == True) {
            std::cout << "Moving RIGHT\n";
            grid.moveRight(); // Move right
        }
        if (inputter.getKeyState(SDL_SCANCODE_S) == True || inputter.getKeyState(SDL_SCANCODE_DOWN) == True) {
            std::cout << "Moving DOWN\n";
            grid.moveDown(); // Move down
        }
        if (inputter.getKeyState(SDL_SCANCODE_W) == Subjective || inputter.getKeyState(SDL_SCANCODE_R) == True || inputter.getKeyState(SDL_SCANCODE_UP) == True) {
             grid.rotatePiece(); // Rotate
        }

        canvas.BlankScreen();
        grid.render();
        frontend.PresentRenderer();
        if (!grid.update()) {
            break;
        }

        frontend.PauseDelay();
    }

    return 0;
}
