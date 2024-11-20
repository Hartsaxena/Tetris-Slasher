/*
Driver file.
*/

#include <SDL.h>
#include <iostream>
#include "Front.hpp"
#include "Blocks.hpp"
#include "Render.hpp" 
#include "Tetris.hpp"
#include "SDLConnector.hpp"

int main(int argc, char* argv[]) {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    FrontendManager frontend(1000, 1000, 60, "Tetris Game");
    Canvas canvas = Canvas(frontend.renderer);
    TetrisGrid grid = TetrisGrid();
    InputManager inputter = InputManager();
	SDLConnector connector = SDLConnector(&canvas, &grid);
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
        if (inputter.getKeyPress(SDL_SCANCODE_DOWN)) {
            std::cout << "Moving DOWN\n";
            grid.moveDown(); // Move down
        }
        if (inputter.getKeyPress(SDL_SCANCODE_UP) || inputter.getKeyPress(SDL_SCANCODE_R)) {
            std::cout << "UP or R pressed. Rotate.\n";
            grid.rotate(); // Rotate
        }
        if (inputter.getKeyPress(SDL_SCANCODE_SPACE)) {
            std::cout << "SPACE pressed. Snap downwards.\n";
            grid.snapDown();
        }

        
        //canvas.displayInt(grid.pointCount, 30);
        connector.clear();
        connector.render();
        frontend.PresentRenderer();
        grid.update();
        if (grid.getGameOver()) {
            std::cout << "Game Over\n";
            isRunning = false;
        }

        frontend.PauseDelay();
    }
    return 0;
}