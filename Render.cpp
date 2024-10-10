/*
This file contains methods that render all objects in the game. Calculations for updating positions of objects, and the like, are done in the update.c file. Game updates and rendering should be done separately.
*/
#include <SDL.h>

#include "Front.hpp"
#include "Render.hpp"
#include "Colors.hpp"


bool Rectangle::snap(int minX, int minY, int maxX, int maxY) {
    bool snapped = false;
    if (this->x < minX) { this->x = minX; snapped = true; }
    if (this->y < minY) { this->y = minY; snapped = true; }
    if (this->x + this->w > maxX) { this->x = maxX - this->w; snapped = true; }
    if (this->y + this->h > maxY) { this->y = maxY - this->h; snapped = true; }
    return snapped;
}
bool Rectangle::snap(int maxX, int maxY) {
    return this->snap(0, 0, maxX, maxY);
}

Canvas::Canvas(SDL_Renderer* renderer)
{
    // Constructor
    this->renderer = renderer;
}


void Canvas::FillScreenColor(Color color) const
{
    // Fills the screen with a color.
    SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.alpha);
    SDL_RenderClear(renderer);
}

void Canvas::BlankScreen() const
{
    // Fills the screen with black
    this->FillScreenColor(BLACK);
}

void Canvas::DrawRect(Rectangle* rect) const
{
    Color color = rect->color;
    SDL_RenderDrawRect(renderer, &(rect->rect));
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.alpha);
    SDL_RenderFillRect(renderer, &(rect->rect));
}