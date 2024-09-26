/*
Driver file.
*/

#include <iostream>
#include <string>
#include <SDL.h>

#include "Front.hpp"
#include "Render.hpp"
#include "Colors.hpp"
#include "Tetris.hpp"


int main(int argc, char* argv[])
{
    // Initializing Frontend Variables
    FrontendManager front(1240, 960, 60, "Tetris Slasher!");
    InputManager input;
    Canvas gameRenderer(front.renderer);

    // Initializing Game Variables
    TetrisGrid grid = (&gameRenderer);

    std::cout<<"Finished Loading! Starting Game Loop\n\n"; // Separate game errors from initializing errors.

    // Main Game Loop
    bool IsRunning = true;
    while (IsRunning) {

        // Handle Input Events
        IsRunning = input.HandleInputs();

        // Update code here

        // Inputs

        // Rendering Code Here
        gameRenderer.BlankScreen();

        grid.render();

        front.PresentRenderer();
        front.PauseDelay();
    }

    // Quitting the game
    return 0;
}