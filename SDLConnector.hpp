#pragma once

#include "Tetris.hpp"
#include "Render.hpp"


/**
 * @brief A Connector class that is responsible for rendering the Tetris grid to the screen.
 * Uses the SDL2 library
 */
class SDLConnector {
public:
	SDLConnector(Canvas* canvas, TetrisGrid* grid) { this->canvas = canvas; this->grid = grid; }

	void clear();
	void render();

private:
	Canvas* canvas;
	TetrisGrid* grid;

	/********* RENDERING CONFIGURATION **********/
	const int BLOCK_SIZE = 30;
	const Color GRID_COLOR = WHITE;
	const Color BLOCK_COLOR = GRAY;
	const Color ACTIVE_BLOCK_COLOR = CYAN;

	void drawGridLines();
	void drawBlocks();
	void drawActiveBlocks();

	void drawBlock(Block, Color color);
};