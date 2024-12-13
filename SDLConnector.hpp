#pragma once

#include "Tetris.hpp"
#include "Render.hpp"
#include "Menu.hpp"

/**
 * @brief A Connector class that is responsible for rendering the Tetris grid to the screen.
 * Uses the SDL2 library
 */
class SDLConnector {
public:
	explicit SDLConnector(Canvas* canvas, TetrisGrid* grid, MainMenu* menu, Font* font) {
		this->canvas = canvas;
		this->grid = grid;
		this->menu = menu;
		this->font = font;
	}

	void clear();
	void render(bool menuMode = false);

private:
	Canvas* canvas;
	TetrisGrid* grid;
	MainMenu* menu;
	Font* font;

	/********* RENDERING CONFIGURATION **********/
	const int BLOCK_SIZE = 30;
	const Color GRID_COLOR = WHITE;
	const Color BLOCK_COLOR = GRAY;
	const Color ACTIVE_BLOCK_COLOR = CYAN;

	void renderMainMenu();
	void renderGame();

	void drawButton(Rectangle rect, std::string text, Font& font, Color textColor);
	void drawGridLines();
	void drawBlocks();
	void drawActiveBlocks();

	void drawBlock(Block, Color color);
};