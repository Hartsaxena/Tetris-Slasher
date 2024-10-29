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

        if (inputter.getKeyPress(SDL_SCANCODE_LEFT)) {
            std::cout << "Moving LEFT\n";
            grid.moveLeft(); // Move left
        }
        if (inputter.getKeyPress(SDL_SCANCODE_RIGHT)) {
            std::cout << "Moving RIGHT\n";
            grid.moveRight(); // Move right
        }
        if (inputter.getKeyState(SDL_SCANCODE_DOWN)) {
            std::cout << "Moving DOWN\n";
            grid.moveDown(); // Move down
        }
        if (inputter.getKeyPress(SDL_SCANCODE_UP) || inputter.getKeyPress(SDL_SCANCODE_R)) {
            std::cout << "UP or R pressed. Rotate.\n";
            grid.rotatePiece(); // Rotate
        }
        if (inputter.getKeyPress(SDL_SCANCODE_SPACE)) {
            std::cout << "SPACE pressed. Snap downwards.\n";
            grid.instantDown();
        }

        canvas.BlankScreen();
        grid.render();
        frontend.PresentRenderer();
        if (!grid.update()) {
            std::cout << "ERROR: Grid Update returned false.\n";
            return 1;
        }
        frontend.PauseDelay();
    }
    return 0;
}