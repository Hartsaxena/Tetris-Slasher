#include "SDL.h"
#include "SDLConnector.hpp"
#include "Tetris.hpp"


void SDLConnector::clear() {
	this->canvas->blankScreen();
}

void SDLConnector::render() {
	this->clear();
	this->drawGridLines();
	this->drawBlocks();
	this->drawActiveBlocks();
}

void SDLConnector::drawGridLines() {
	int maxX = this->grid->GRID_HEIGHT;
	// Draw the grid lines
	for (int i = 0; i < this->grid->GRID_WIDTH; i++) {
		// Draw vertical lines
		this->canvas->drawLine({ i * BLOCK_SIZE, 0 }, { i * BLOCK_SIZE, this->canvas->yDimension }, GRID_COLOR);
	}
	for (int i = 0; i < this->grid->GRID_HEIGHT; i++) {
		// Draw horizontal lines
		this->canvas->drawLine({ 0, i * BLOCK_SIZE }, { this->canvas->xDimension, i * BLOCK_SIZE }, GRID_COLOR);
	}

}
void SDLConnector::drawBlocks() {
	for (const Block& block : this->grid->getBlocks()) {
		this->drawBlock(block, BLOCK_COLOR);
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