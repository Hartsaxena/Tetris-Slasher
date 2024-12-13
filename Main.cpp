/*
Driver file.
*/

#include <SDL.h>
#include <iostream>
#include "Front.hpp"
#include "Render.hpp"
#include "Colors.hpp"
#include "Bag.hpp"
#include "Tetris.hpp"
#include "Blocks.hpp"
#include "Render.hpp" 
#include "Tetris.hpp"
#include "Menu.hpp"
#include "SDLConnector.hpp"

int main(int argc, char* argv[]) {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    FrontendManager frontend(1000, 1000, 60, "Tetritis");
    Canvas canvas = Canvas(frontend.renderer);
    Font loraRegular = Font("Resources\\fonts\\Lora-Regular.ttf", 30);
    TetrisGrid grid;
    MainMenu menu = MainMenu(canvas.yDimension, canvas.xDimension);
    
    InputManager inputter = InputManager();
	SDLConnector connector = SDLConnector(&canvas, &grid, &menu, &loraRegular);
    bool menuRunning = true;
    bool isRunning = false;

    while (menuRunning) { // Main Menu
        // Handle Events and update keyboard
        menuRunning = inputter.HandleInputs();

		if (inputter.getMouseKeyState(1)) {
            menu.click(inputter.getMouseX(), inputter.getMouseY());
		}

		if (menu.startPressed) {
            menuRunning = false;
            isRunning = true;
        }
        else if (menu.exitPressed) {
            isRunning = false;
        }

        connector.render(true);
        frontend.PresentRenderer();
        frontend.PauseDelay();
    }

	while (isRunning) { // Game Loop
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