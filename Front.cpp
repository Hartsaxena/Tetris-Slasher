/*
This file contains methods that manage the SDL2 library, which is used as the frontend of the game. This includes window creation, rendering, and event handling.
*/
#include <iostream>
#include <SDL.h>

#include "Front.hpp"



FrontendManager::FrontendManager(int screenW, int screenH, int fps, const std::string windowTitle)
{
    /*
    This function initializes the SDL2 library. It creates a window and renderer, and returns 0 if successful, or -1 if not.
    */

    this->screenW = screenW;
    this->screenH = screenH;
    this->fps = fps;
    this->windowTitle = windowTitle;
  
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { // Initialize SDL
        std::cout<<"Failed to initialize SDL.\n";
        std::cout<<SDL_GetError();
        SDL_Quit();
        exit(1);
    }

    this->window = SDL_CreateWindow(windowTitle.c_str(),
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    screenW, screenH,
                                    SDL_WINDOW_SHOWN);
    if (this->window == NULL) {
        std::cout<<"FATAL ERROR: Window could not be displayed.\n";
        std::cout<<SDL_GetError();
        SDL_Quit();
        exit(1); // Quit the program
    }
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    this->winRect = { 0, 0, screenW, screenH };
}


FrontendManager::~FrontendManager()
{
    /*
    Destructor for the FrontendManager class.
    Quits SDL2 and frees memory.
    */
    if (this->window != NULL) {
        SDL_DestroyWindow(this->window);
        SDL_DestroyRenderer(this->renderer);
    }
    SDL_Quit();
}

void FrontendManager::PresentRenderer() const
{
    /*
    This function presents the renderer to the window.
    */
    SDL_RenderPresent(this->renderer);
}

void FrontendManager::PauseDelay() const
{
    /*
    This function pauses the game for a short time, to limit the frame rate.
    */
    SDL_Delay(this->framePauseDelay);
}


InputManager::InputManager()
{
    /*
    Constructor for the InputManager class.
    */

    for (int i = 0; i < 286; i++)
        this->inputKeys[i] = False;

    this->inputEvent = new SDL_Event;
    if (this->inputEvent == NULL) {
        std::cout<<"Failed to allocate memory for input event data.\n";
        exit(1);
    }

    this->InitMouseState();
}


InputManager::~InputManager()
{
    /*
    Destructor for the InputManager class.
    Frees memory.
    */
    delete this->inputEvent;
    delete this->mouseState;
}


bool InputManager::HandleInputs()
{
    /*
    This function handles all input events. It returns true if the game should continue running, false if it should quit.
    */
    bool IsRunning = true;
    while (SDL_PollEvent(this->inputEvent) > 0) {
        switch (inputEvent->type) {
            case SDL_KEYDOWN: {
                this->inputKeys[inputEvent->key.keysym.scancode] = Subjective;
                break;
            }
            case SDL_KEYUP: {
                this->inputKeys[inputEvent->key.keysym.scancode] = False;
                break;
            }
            
            case SDL_MOUSEBUTTONDOWN: {
                this->mouseState->ButtonStates[inputEvent->button.button] = True;
                break;
            }
            case SDL_MOUSEBUTTONUP: {
                this->mouseState->ButtonStates[inputEvent->button.button] = False;
                break;
            }
            case SDL_MOUSEMOTION: {
                this->mouseState->x = inputEvent->motion.x;
                this->mouseState->y = inputEvent->motion.y;
                break;
            }

            case SDL_QUIT: {
                IsRunning = false;
                break;
            }
            default: {
                break;
            }
        }
    }
    return IsRunning;
}

void InputManager::InitMouseState() {
    MouseState* currentMouseState = new MouseState;
    if (currentMouseState == NULL) {
        std::cout << "Failed to allocate memory for Mouse State data.\n";
        exit(1);
    }

    for (int i = 0; i < 5; i++)
        currentMouseState->ButtonStates[i] = false;
    currentMouseState->x = 0;
    currentMouseState->y = 0;

    this->mouseState = currentMouseState;
}