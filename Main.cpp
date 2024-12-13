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
#include <SDL_mixer.h>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! Mix_Error: " << Mix_GetError() << std::endl;
        return 1;
    }

    Mix_Music* bgMusic = Mix_LoadMUS("C:\\GLP\\Tetris\\Resources\\Anamanaguchi - Miku (Instrumental).mp3");
    if (!bgMusic) {
        std::cerr << "Failed to load music! Mix_Error: " << Mix_GetError() << std::endl;
        return 1;
    }

    if (Mix_PlayMusic(bgMusic, -1) == -1) { 
        std::cerr << "Failed to play music! Mix_Error: " << Mix_GetError() << std::endl;
        return 1;
    }
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    FrontendManager frontend(800, 600, 60, "Tetris Game");
    Canvas canvas = Canvas(frontend.renderer);
    BlockQueue blockQueue;
    TetrisGrid grid(&canvas, &blockQueue);
    Bag bag(blockQueue, &grid);
    grid.setBag(&bag);
    InputManager inputter = InputManager();

    bool isRunning = true;
    bool storeKeyPressed = false;
    bool unstoreKeyPressed = false;
    


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
        if (inputter.getKeyPress(SDL_SCANCODE_C)) {
            if (!storeKeyPressed) {
                if (!bag.canHold) {
                    std::cout << "Hold action already done." << std::endl;
                }
                else {
                    if (bag.getBagSize() < 2) {
                        bag.pullFromQueue(&blockQueue);
                        grid.generatePiece();
                    }
                    storeKeyPressed = true;
                }

            }
        }
        else { storeKeyPressed = false; }

        if (inputter.getKeyPress(SDL_SCANCODE_V)) {
            if (!unstoreKeyPressed) {
                if (bag.getBagSize() > 0) {
                    bag.AddToQueue(blockQueue);     
                    grid.generatePiece();
                }
                unstoreKeyPressed = true;
            }
        }
        else { unstoreKeyPressed = false; }

        
        canvas.displayInt(grid.pointCount, 30);
        canvas.BlankScreen();
        grid.render();
        frontend.PresentRenderer();
        if (!grid.update()) {
            std::cout << "ERROR: Grid Update returned false.\n";
            return 1;
        }
        frontend.PauseDelay();
    }
    Mix_FreeMusic(bgMusic); // Free the music
    Mix_CloseAudio();
    SDL_Quit();
    return 0;
}