#pragma once

#include <SDL.h>
#include "Colors.hpp"

typedef struct Rectangle {
    /* Rectangle structure */
    SDL_Rect rect;
    Color color;
    int& x = rect.x;
    int& y = rect.y;
    int& w = rect.w;
    int& h = rect.h;

    bool snap(int minX, int minY, int maxX, int maxY);
    bool snap(int maxX, int maxY);
} Rectangle;

typedef struct Position {
    int x;
    int y;
} Position;


// Class Declarations
class Canvas;
class Surface;

class Canvas
{
/*
The purpose of this class is to manage the rendering of the game.
*/


public:
    explicit Canvas(SDL_Renderer* renderer);
    ~Canvas() {}

    void FillScreenColor(Color color) const;
    void BlankScreen() const;
    void DrawRect(Rectangle* rect) const;

    void BlitSurface(Surface* surface, Position position) {};

private:
    SDL_Renderer* renderer;
};