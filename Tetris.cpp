#include <iostream>
#include "Tetris.hpp"
#include "Blocks.hpp"
#include "Front.hpp"
#include "Render.hpp"
#include "Colors.hpp"

PieceQueue::~PieceQueue() {
    PieceQueueNode* curr = first;
    PieceQueueNode* last;
    while (curr != nullptr) {
        last = curr;
        curr = curr->next;
        delete last;
    }
}

void PieceQueue::enqueue(Piece val) {
    if (this->first == nullptr) { // First entry in list
        this->first = new PieceQueueNode(val);
        this->last = this->first;
        this->last->next = nullptr;
        return;
    }

    PieceQueueNode* newLast = new PieceQueueNode(val);
    this->last->next = newLast;
    this->last = newLast;
    this->length++;
}

Piece PieceQueue::dequeue() {
    if (this->last == nullptr) {
        std::cout << "Can't dequeue from empty queue!\n";
        exit(-1);
    }

    Piece val = this->first->val;
    PieceQueueNode* temp = this->first;
    this->first = this->first->next;
    delete temp;
    this->length--;
    return val;
}

TetrisGrid::TetrisGrid() {
    this->newPiece();

    // Initialize the walls of the grid.
	for (int y = 0; y < GRID_HEIGHT; y++) {
		this->blocks.push_back(Block(-1, y, true));
		this->blocks.push_back(Block(GRID_WIDTH, y, true));
	}
    // Initialize the floor of the grid.
    for (int x = 0; x < GRID_WIDTH; x++) {
		this->blocks.push_back(Block(x, GRID_HEIGHT, true));
    }
}

TetrisGrid::~TetrisGrid() {
    delete this->currentPiece;
}

void TetrisGrid::update() {
	if (frameTimer > 0) {
		frameTimer--;
		return;
	}

	frameTimer = maxFrameTimer;

    this->moveDown();
}

bool TetrisGrid::moveDown() {
    this->currentPiece->moveDown();

    if (this->checkCollision()) {
        this->currentPiece->moveUp(); // This will never collide
        this->newPiece();
        this->clearLines();
        return false;
    }

    return true;
}

bool TetrisGrid::moveLeft() {
    this->currentPiece->moveLeft();

    if (this->checkCollision()) {
        this->moveRight(); // Because we're moving back to the original position, this should never return false
        return false;
    }

    return true;
}

bool TetrisGrid::moveRight() {
    this->currentPiece->moveRight();

    if (this->checkCollision()) {
        this->moveLeft();
        return false;
    }

    return true;
}

bool TetrisGrid::rotate() {
    this->currentPiece->rotate();

    if (this->checkCollision()) {
        for (int i = 0; i < 3; i++) {
            this->currentPiece->rotate();
        }
        return false;
    }
    
    return true;
}

void TetrisGrid::snapDown() {
    while (this->moveDown()) {}
}

bool TetrisGrid::checkCollision() const {
	// An admittedly slow way to check for collisions, but it's the most straightforward.
    // Efficiency doesn't matter too much when Tetris is so small-scale.
	for (const Block& block : this->getPieceBlocks()) {
		for (const Block& placedBlock : this->blocks) {
			if (block.x == placedBlock.x && block.y == placedBlock.y) {
				return true;
			}
		}
	}

	return false;
}

void TetrisGrid::clearLines() {
	for (int y = 0; y < GRID_HEIGHT; y++) {
		int count = 0;
		for (const Block& block : this->blocks) {
			if (block.y == y && !block.immortal) {
				count++;
			}
		}

		if (count == GRID_WIDTH) {
			// Clear the line
			for (auto it = this->blocks.begin(); it != this->blocks.end();) {
				if (it->y == y) {
					it = this->blocks.erase(it);
				}
				else {
					it++;
				}
			}

			// Move all blocks above the cleared line down
			for (Block& block : this->blocks) {
				if (block.y < y) {
					block.y++;
				}
			}
		}
	}
}

void TetrisGrid::newPiece() {
	if (this->currentPiece != nullptr) {
        this->setPiece();
		delete this->currentPiece;
	}

    PieceType newPieceType = static_cast<PieceType>(rand() % 7);
	this->currentPiece = new Piece(NEW_PIECE_X, NEW_PIECE_Y, newPieceType);

    return; // debug breakpoint
}

void TetrisGrid::setPiece() {
    for (const Block& block : this->getPieceBlocks()) {
        this->blocks.push_back(block);
    }
}