#include <iostream>
#include "Tetris.hpp"
#include "Blocks.hpp"


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