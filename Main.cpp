/*
Driver file.
*/

#include <iostream>
#include <string>
#include <SDL.h>

#include "Front.hpp"
#include "Render.hpp"
#include "Colors.hpp"
#include "Bag.hpp"
#include "Tetris.hpp"


int main(int argc, char* argv[])
{
    // Initializing Frontend Variables
    FrontendManager front(1240, 960, 60, "Tetris Slasher!");
    InputManager input;
    Canvas gameRenderer(front.renderer);

    // Initializing Game Variables
    Bag bag; 

    std::queue<Block*> blockQueue;  // Create an initial block queue
    // Testing Variables
    Rectangle testRectangle = { 100, 100, 33, 33, RED };


    std::cout<<"Finished Loading! Starting Game Loop\n\n"; // Separate game errors from initializing errors.

    // Main Game Loop
    bool IsRunning = true;
    while (IsRunning) {

        // Handle Input Events
        IsRunning = input.HandleInputs();

        // Update code here

        /*
        Some filler movement code for a rectangle.
        This isn't meant for the final game, just for testing the input manager.
        */
        int cubeSpeed = 3;
        if (input.getKeyState(SDL_SCANCODE_W))
            testRectangle.rect.y -= cubeSpeed;
        if (input.getKeyState(SDL_SCANCODE_S))
            testRectangle.rect.y += cubeSpeed;
        if (input.getKeyState(SDL_SCANCODE_A))
            testRectangle.rect.x -= cubeSpeed;
        if (input.getKeyState(SDL_SCANCODE_D))
            testRectangle.rect.x += cubeSpeed;
        if (input.getKeyState(SDL_SCANCODE_R))
            bag.pullFromQueue(blockQueue);
            std::cout << "Pulled From Queue";
        if (input.getKeyState(SDL_SCANCODE_T))
            bag.AddToQueue(blockQueue);
            std::cout << "Added From Queue";
        // Boundary Checking
        testRectangle.snap(front.getScreenX(), front.getScreenY());

        // Rendering Code Here
        gameRenderer.BlankScreen();

        gameRenderer.DrawRect(&testRectangle);

        front.PresentRenderer();
        front.PauseDelay();
    }

    // Quitting the game
    return 0;
}