#include <iostream>
#include "Tetris.hpp"
#include "Blocks.hpp"
#include "Front.hpp"
#include "Render.hpp"


BlockQueue::~BlockQueue() {
	BlockQueueNode* curr = first;
	BlockQueueNode* last;
	while (curr != nullptr) {
		last = curr;
		curr = curr->next;
		delete last;
	}
}

void BlockQueue::enqueue(Block val) {
	if (this->first == nullptr) { // First entry in list
		this->first = new BlockQueueNode(val);
		this->last = this->first;
		this->last->next = nullptr;
		return;
	}

	BlockQueueNode* newLast = new BlockQueueNode(val);
	this->last->next = newLast;
	this->last = newLast;
	this->length++;
}

Block BlockQueue::dequeue() {
	if (this->last == nullptr) {
		std::cout << "Can't dequeue from empty queue!\n";
		exit(-1);
	}

	Block val = this->first->val;
	BlockQueueNode* temp = this->first;
	this->first = this->first->next;
	delete temp;
	this->length--;
	return val;
}


/*
Returns true if there is collision between the current piece and the grid.
*/
bool TetrisGrid::checkCollision() {
	RotationalState pieceState = this->curr->getCurrentState();
	for (int y = 3; y >= 0; y--) {    // Row
		for (int x = 0; x < 4; x++) { // Column
			bool val = RotationalStates::getCell(pieceState, y, x);
			if (val == 0) {
				continue;
			}

			int gridRelativeX = this->currX + x;
			int gridRelativeY = this->currY + y;

			//// NOTE: I'm not sure if checking collision with the sides of the grid should be in this method.
			//// Check collision with sides of grid
			//(this->checkWallCollision(gridRelativeX, gridRelativeY)) {
			//	return true;
			//}

			// Check collision with other grid cells
			if (this->getGridCell(y, x)) {
				return true;
			}
		}
	}

	return false;
}

bool TetrisGrid::checkWallCollision(int pieceX, int pieceY) const {
	return (pieceX < 0 || pieceX >= this->xDimension);
}


TetrisGrid::~TetrisGrid() {
	SDL_DestroyRenderer("insert renderer");
	SDL_DestroyWindow("insert window");
	SDL_Quit();
}

void TetrisGrid::displayGrid() {
	bool running = true;
	while (running) {
		processEvents();
		update();
		render();
		SDL_Delay(100); // frame rate
	}
}

void TetrisGrid::processEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			exit(0);
		}
	}
}

void TetrisGrid::update() {
	// this is for like block movement and ig the queue
}

void TetrisGrid::render() {
	SDL_SetRenderDrawColor("insert renderer", 0, 0, 0, 255); // Black background
	SDL_RenderClear("insert renderer");

	renderGrid(); // Render the grid
	renderBlock(curr, currX, currY); // Render the current block

	SDL_RenderPresent("insert renderer");
}

void TetrisGrid::renderGrid() {
	SDL_SetRenderDrawColor("insert renderer", 255, 255, 255, 255); // White grid lines

	for (int x = 0; x < GRID_WIDTH; ++x) {
		for (int y = 0; y < GRID_HEIGHT; ++y) {
			SDL_Rect cell;
			cell.x = x * CELL_SIZE;
			cell.y = y * CELL_SIZE;
			cell.w = CELL_SIZE;
			cell.h = CELL_SIZE;

			if (getGridCell(x, y)) {
				SDL_SetRenderDrawColor("insert renderer", 255, 0, 0, 255); // Red for filled cells
				SDL_RenderFillRect("insert renderer", &cell);
			}

			SDL_SetRenderDrawColor("insert renderer", 255, 255, 255, 255); // White grid lines
			SDL_RenderDrawRect("insert renderer", &cell);
		}
	}
}

void TetrisGrid::renderBlock(Block* block, int currX, int currY) {
	RotationalState pieceState = block->getCurrentState();

	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			if (RotationalStates::getCell(pieceState, y, x)) {
				SDL_Rect cell;
				cell.x = (currX + x) * CELL_SIZE;
				cell.y = (currY + y) * CELL_SIZE;
				cell.w = CELL_SIZE;
				cell.h = CELL_SIZE;

				SDL_SetRenderDrawColor("insert renderer", 0, 255, 0, 255); // Green for active block
				SDL_RenderFillRect("insert renderer", &cell);
			}
		}
	}
}

