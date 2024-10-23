/*
This file contains methods that render all objects in the game. Calculations for updating positions of objects, and the like, are done in the update.c file. Game updates and rendering should be done separately.
*/
#include <SDL.h>
#include <string>

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

void Canvas::renderDigit(int digit, int x, int y, int size) {
    // Color for the numbers (white)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Array defining which segments of the digit are "on" (1) or "off" (0)
    // Each digit is represented by 7 segments (like a seven-segment display)
    const int segments[10][7] = {
        {1, 1, 1, 0, 1, 1, 1}, // 0
        {0, 0, 1, 0, 0, 1, 0}, // 1
        {1, 0, 1, 1, 1, 0, 1}, // 2
        {1, 0, 1, 1, 0, 1, 1}, // 3
        {0, 1, 1, 1, 0, 1, 0}, // 4
        {1, 1, 0, 1, 0, 1, 1}, // 5
        {1, 1, 0, 1, 1, 1, 1}, // 6
        {1, 0, 1, 0, 0, 1, 0}, // 7
        {1, 1, 1, 1, 1, 1, 1}, // 8
        {1, 1, 1, 1, 0, 1, 1}  // 9
    };

    // Coordinates and sizes for the 7 segments of the digit
    SDL_Rect segmentRect[7] = {
        {x, y, size, 10},                   // Top
        {x, y, 10, size},                   // Top-left
        {x + size - 10, y, 10, size},       // Top-right
        {x, y + size, size, 10},            // Middle
        {x, y + size, 10, size},            // Bottom-left
        {x + size - 10, y + size, 10, size},// Bottom-right
        {x, y + size * 2, size, 10}         // Bottom
    };

    // Draw the segments that are "on" for the given digit
    for (int i = 0; i < 7; i++) {
        if (segments[digit][i] == 1) {
            SDL_RenderFillRect(renderer, &segmentRect[i]);
        }
    }
}

void Canvas::displayInt(int number, int size) {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Convert the number to a string to break it into individual digits
    std::string numberStr = std::to_string(number);

    // Calculate the starting x position for the first digit (adjust for screen width)
    int xPos = 800 - (numberStr.length() * (size + 10)) - 10;  // 10px padding between digits and from the right edge

    // Draw each digit
    for (char c : numberStr) {
        int digit = c - '0';  // Convert char to corresponding int
        renderDigit(digit, xPos, 10, size);  // 10px padding from the top edge
        xPos += size + 10;  // Move x position for the next digit
    }
}