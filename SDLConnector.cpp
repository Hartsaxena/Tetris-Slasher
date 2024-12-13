#include "SDL.h"
#include "SDLConnector.hpp"
#include "Tetris.hpp"
#include "Colors.hpp"
#include "Render.hpp"


void SDLConnector::clear() {
	this->canvas->blankScreen();
}

void SDLConnector::render(bool menuMode) {
	this->clear();
	if (menuMode) {
		this->renderMainMenu();
	}
	else {
		this->renderGame();
	}
}

void SDLConnector::renderMainMenu() {
	this->drawButton(this->menu->getTitle(), "Tetritis", *this->font, WHITE);
	this->drawButton(this->menu->getStartButton(), "Start", *this->font, WHITE);
	this->drawButton(this->menu->getExitButton(), "Exit", *this->font, WHITE);
}

void SDLConnector::renderGame() {
	this->drawGridLines();
	this->drawBlocks();
	this->drawActiveBlocks();
}

void SDLConnector::drawButton(Rectangle rect, std::string text, Font& font, Color textColor) {
	this->canvas->drawRect(&rect);
	this->canvas->renderTextCenter(text, &font, rect.x, rect.y, textColor);
}

void SDLConnector::drawGridLines() {
	int maxX = this->grid->GRID_HEIGHT;
	// Draw the grid lines
	for (int i = 0; i < this->grid->GRID_WIDTH + 1; i++) {
		// Draw vertical lines
		this->canvas->drawLine({ i * BLOCK_SIZE, 0 }, { i * BLOCK_SIZE, this->canvas->yDimension }, GRID_COLOR);
	}
	for (int i = 0; i < this->grid->GRID_HEIGHT + 1; i++) {
		// Draw horizontal lines
		this->canvas->drawLine({ 0, i * BLOCK_SIZE }, { this->canvas->xDimension, i * BLOCK_SIZE }, GRID_COLOR);
	}

}
void SDLConnector::drawBlocks() {
	for (const Block& block : this->grid->getBlocks()) {
		if (!block.immortal) this->drawBlock(block, BLOCK_COLOR);
	}
}

void SDLConnector::drawActiveBlocks() {
	for (const Block& block : this->grid->getPieceBlocks()) {

		this->drawBlock(block, ACTIVE_BLOCK_COLOR);
	}
}

void SDLConnector::drawBlock(Block block, Color color) {
	Rectangle rect;
	rect.x = block.x * BLOCK_SIZE;
	rect.y = block.y * BLOCK_SIZE;
	rect.w = BLOCK_SIZE;
	rect.h = BLOCK_SIZE;
	rect.color = BLOCK_COLOR;
	this->canvas->drawRect(&rect);
}