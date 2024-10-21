#include <iostream>
#include "Tetris.hpp"
#include "Blocks.hpp"
#include "Front.hpp"
#include "Render.hpp"
#include "Colors.hpp"

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


TetrisGrid::TetrisGrid(Canvas* canvas) {
    this->canvas = canvas;
    // Initialize the grid to 0 (empty)
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            grid[y][x] = 0; // 0 means empty
        }
    }
    generatePiece();
}

TetrisGrid::~TetrisGrid() {
    delete currentPiece; // Clean up the current piece
}

void TetrisGrid::generatePiece() {
    int randomBlockType = rand() % 7; // Randomly select a block type
    switch (randomBlockType) {
    case I_BLOCK: currentPiece = new IBlock(); break;
    case O_BLOCK: currentPiece = new OBlock(); break;
    case S_BLOCK: currentPiece = new SBlock(); break;
    case Z_BLOCK: currentPiece = new ZBlock(); break;
    case L_BLOCK: currentPiece = new LBlock(); break;
    case T_BLOCK: currentPiece = new TBlock(); break;
    case J_BLOCK: currentPiece = new JBlock(); break;
    }

    currentPieceState = currentPiece->getCurrentState();
    piecePosition = { 4, 0 }; // top of piece grid
    if (checkCollision()) {
        gameOver = true; // Game over if the new piece cannot be placed
    }
}

/* 
Notice: dx and dy represent changes (delta) in those values. For example, moving 2 squares to the right would be dx = 2, dy = 0.
*/
bool TetrisGrid::movePiece(int dx, int dy) {
    std::cout << "Checking movepiece collision\n";
    piecePosition.x += dx;
    piecePosition.y += dy;
    bool collision = checkCollision();

    if (!collision) {
        return true;
    }
    else {
        piecePosition.x -= dx;
        piecePosition.y -= dy;
        return false;
    }
}

bool TetrisGrid::rotatePiece() {
    // Save the current piece's rotational state before attempting to rotate
    RotationalState oldState = currentPieceState;

    // Rotate the piece
    currentPiece->rotate();

    // Check if the new rotated state causes a collision
    if (!checkCollision()) {
        // No collision, rotation successful
        currentPieceState = currentPiece->getCurrentState(); // Commit to the new state
        return true;
    }
    else {
        // Collision detected, revert to the old rotational state
        currentPiece->rotationalStates.cycleCurr();
        return false;
    }
}

void TetrisGrid::placePiece() {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (RotationalStates::getCell(currentPieceState, row, col)) {
                grid[piecePosition.y + row][piecePosition.x + col] = 1; // Mark the grid as filled
            }
        }
    }
    clearLines(); // clears full filled line on grid
    generatePiece(); // gives new piece when placed
}

void TetrisGrid::clearLines() {
    for (int y = 0; y < GRID_HEIGHT; y++) {
        bool lineFilled = true;
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[y][x] == 0) {
                lineFilled = false;
                break;
            }
        }
        if (lineFilled) {
            // Clear the line
            for (int row = y; row > 0; row--) {
                for (int col = 0; col < GRID_WIDTH; col++) {
                    grid[row][col] = grid[row - 1][col]; // Move down
                }
            }
            // Clear the top line
            for (int col = 0; col < GRID_WIDTH; col++) {
                grid[0][col] = 0;
            }
        }
    }
}

bool TetrisGrid::isGameOver() const {
    return gameOver;
}

void TetrisGrid::echoState() const {
    // For debugging

    std::cout << "Canvas pointer: " << this->canvas << "\n";

    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            std::cout << " " << this->grid[y][x];
        }
        std::cout << "\n";
    }

    std::cout << "Current piece position: " << this->piecePosition.x << ", " << this->piecePosition.y << "\n";
}

bool TetrisGrid::update() {
    //this->echoState();

    if (isGameOver()) {
        std::cout << "Game Over!\n";
        return false;
    }

    if (this->frameTimer-- == 0) {
        // Move piece down automatically
        if (!movePiece(0, 1)) {
            placePiece(); // Place piece if it colllides
        }

        this->frameTimer = maxFrameTimer;
    }

    return true;
}

void TetrisGrid::render() {
    // Draw the grid
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[y][x] != 0) { // If not empty
                Rectangle rect = { x * 30, y * 30, 30, 30, Color{WHITE} }; // Example color for filled for now
                canvas->DrawRect(&rect);
            }
            else {
                Rectangle rect = { x * 30, y * 30, 30, 30, Color{BLUE} }; // Example color for filled for now
                canvas->DrawRect(&rect);
            }
        }
    }

    // Render the current piece
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (RotationalStates::getCell(currentPieceState, row, col)) {
                Rectangle rect = { (piecePosition.x + col) * 30, (piecePosition.y + row) * 30, 30, 30, Color{RED} }; // Example color for now
                canvas->DrawRect(&rect);
            }
        }
    }
}


/*
Returns true if there is collision between the current piece and the grid.
*/
bool TetrisGrid::checkCollision() {
	RotationalState pieceState = this->currentPiece->getCurrentState();
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
			if (this->getGridCell(gridRelativeX, gridRelativeY)) {
				return true;
			}
		}
	}

	return false;
}

bool TetrisGrid::checkWallCollision(int pieceX, int pieceY) const {
	return (pieceX < 0 || pieceX >= GRID_WIDTH);
}