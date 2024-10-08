#pragma once

#include <iostream>
#include <SDL.h>

typedef struct MouseState {
    bool ButtonStates[5];
    int x, y;
} MouseState;


// Forward declarations of classes so that they can reference each other.
class FrontendManager;
class InputManager;


class InputManager
{
/*
The purpose of this class is to manage inputs of the game.
*/

public:
    InputManager();
    ~InputManager();

    bool HandleInputs();
    void InitMouseState();
    bool getKeyState(SDL_Scancode keyCode) const { return this->inputKeys[keyCode]; }

private:
    MouseState* mouseState;
    SDL_Event* inputEvent;
    bool inputKeys[286];
};


class FrontendManager
{
    /*
    The purpose of this class is to manage the frontend of the game.
    */

public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect winRect;

    FrontendManager(int screenW, int screenH, int fps, const std::string windowTitle);
    ~FrontendManager();

    void PresentRenderer() const;
    void PauseDelay() const;

    int getScreenW() const { return this->screenW; }
    int getScreenH() const { return this->screenH; }
    int getScreenX() const { return this->screenX; }
    int getScreenY() const { return this->screenY; }

private:
    int screenW, screenH;
    int& screenX = screenW; // Alias to screenW
    int& screenY = screenH; // Alias to screenH
    int fps = 60;
    int framePauseDelay = 1000 / fps;
    std::string windowTitle;
};
