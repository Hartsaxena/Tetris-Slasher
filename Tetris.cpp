#include <iostream>
#include <random>
#include "Tetris.hpp"
#include "Blocks.hpp"


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
    delete currentPiece; // Clean up the current piece
}

void TetrisGrid::newPiece() {
    if (this->currentPiece != nullptr) {
        this->setPiece();
        delete this->currentPiece;
    }

    if (this->pieceQueue->getLength() == 3) {
        std::cout << "Queue is empty! Regenerating..." << std::endl;
        pieceQueue->refillQueue();
    }

    *currentPiece = pieceQueue->dequeue();

    if (checkCollision()) {
        gameOver = true;
    }
}

void TetrisGrid::setPiece() {
	for (const Block& block : this->getPieceBlocks()) {
		this->blocks.push_back(block);
	}
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

bool TetrisGrid::moveGhostDown() {
    this->ghostPiece->moveDown();

    if (this->checkCollision()) {
        this->ghostPiece->moveUp(); // This will never collide
        return false;
    }

    return true;
}

bool TetrisGrid::checkGhostCollision() const {
    // An admittedly slow way to check for collisions, but it's the most straightforward.
    // Efficiency doesn't matter too much when Tetris is so small-scale.
    for (const Block& block : this->getGhostBlocks()) {
        for (const Block& placedBlock : this->blocks) {
            if (block.x == placedBlock.x && block.y == placedBlock.y) {
                return true;
            }
        }
    }

    return false;
}

PieceQueue::PieceQueue() {
    std::cout << "CREATING A NEW BLOCKQ" << std::endl;
    generateBag();
    fillQueueFromBag();
}

PieceQueue::~PieceQueue() {
    PieceQueueNode* curr = first;
    while (curr != nullptr) {
        PieceQueueNode* last = curr;
        curr = curr->next;
        delete last->val; // Delete the Block gaming
        delete last;
    }

}

void PieceQueue::enqueue(Piece* val) {
    PieceQueueNode* newFirst = new PieceQueueNode(val);

    newFirst->next = first;

    first = newFirst;

    if (last == nullptr) {
        last = newFirst;
    }

    length++;
}

Piece PieceQueue::dequeue() {
    if (this->first == nullptr) {
        std::cout << "Queue is empty, generating new blocks...\n";
        refillQueue();
    }

    Piece val = *this->first->val;
    PieceQueueNode* temp = this->first;
    this->first = this->first->next;
    delete temp;
    this->length--;

    std::cout << "Dequeuing block: " << val.getType() << "\n";

    std::cout << "Current BlockQueue state: ";
    PieceQueueNode* current = this->first;
    while (current != nullptr) {
        std::cout << current->val->getType() << " ";
        current = current->next;
    }
    std::cout << std::endl;

    return val;
}


void PieceQueue::generateBag() { // generate the bazg w/ 14 pieces
    blockBag = {
        I_PIECE, I_PIECE,
        O_PIECE, O_PIECE,
        S_PIECE, S_PIECE,
        Z_PIECE, Z_PIECE,
        L_PIECE, L_PIECE,
        T_PIECE, T_PIECE,
        J_PIECE, J_PIECE
    };

    // Shuffle the bag
    std::shuffle(blockBag.begin(), blockBag.end(), std::mt19937(std::random_device()()));
}

void PieceQueue::fillQueueFromBag() {
    for (PieceType type : blockBag) {
		Piece* newBlock = new Piece(0, 0, type);
        enqueue(newBlock);
    }
}


void PieceQueue::refillQueue() {
    generateBag();
    fillQueueFromBag();
}

std::vector<Piece*> PieceQueue::peekNextPieces(int count) {
    std::vector<Piece*> nextPieces;
    PieceQueueNode* current = first;
    int i = 0;

    // Collect the next `count` pieces or fewer if the queue is shorter
    while (current != nullptr && i < count) {
        nextPieces.push_back(current->val);
        current = current->next;
        i++;
    }

    return nextPieces;
}