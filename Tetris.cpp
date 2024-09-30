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


TetrisGrid::TetrisGrid(SDL_Renderer* renderer) : renderer(renderer), gameOver(false) {
    // Initialize the grid to 0 (empty)
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            grid[y][x] = 0; // 0 means empty
        }
    }
    GeneratePiece();
}

TetrisGrid::~TetrisGrid() {
    delete currentPiece; // Clean up the current piece
}

void TetrisGrid::GeneratePiece() {
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
    if (CheckCollision(0, 0, currentPieceState)) {
        gameOver = true; // Game over if the new piece cannot be placed
    }
}

bool TetrisGrid::MovePiece(int dx, int dy) {
    if (!CheckCollision(dx, dy, currentPieceState)) {
        piecePosition.x += dx;
        piecePosition.y += dy;
        return true;
    }
    return false;
}

bool TetrisGrid::RotatePiece() {
    RotationalState newState = currentPieceState; // Create a copy of the current state
    // Attempt to rotate the piece
    // how the hell do i do rotation with these stupid numbers

    if (!CheckCollision(0, 0, newState)) {
        currentPieceState = newState;
        return true;
    }
    return false;
}

bool TetrisGrid::CheckCollision(int dx, int dy, const RotationalState& state) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (RotationalStates::getCell(state, row, col)) {
                int x = piecePosition.x + col + dx;
                int y = piecePosition.y + row + dy;
                if (x < 0 || x >= GRID_WIDTH || y >= GRID_HEIGHT || (y >= 0 && grid[y][x] != 0)) {
                    return true; // collide
                }
            }
        }
    }
    return false; // noo collide
}

void TetrisGrid::PlacePiece() {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (RotationalStates::getCell(currentPieceState, row, col)) {
                grid[piecePosition.y + row][piecePosition.x + col] = 1; // Mark the grid as filled
            }
        }
    }
    ClearLines(); // clears full filled line on grid
    GeneratePiece(); // gives new piece when placed
}

void TetrisGrid::ClearLines() {
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

bool TetrisGrid::isGameOver() {
    return gameOver;
}

void TetrisGrid::Update() {
    if (!isGameOver()) {
        // Move piece down automatically
        if (!MovePiece(0, 1)) {
            PlacePiece(); // Place piece if it cannot move down
        }
    }
    else {
        std::cout << "Game Over!" << std::endl;
    }
}

void TetrisGrid::Render() {
    // Draw the grid
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[y][x] != 0) { // If not empty
                Rectangle rect = { x * 30, y * 30, 30, 30, Color{255, 0, 0, 255} }; // Example color for filled for now
                canvas->DrawRect(&rect);
            }
        }
    }

    // Render the current piece
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (RotationalStates::getCell(currentPieceState, row, col)) {
                Rectangle rect = { (piecePosition.x + col) * 30, (piecePosition.y + row) * 30, 30, 30, Color{0, 255, 0, 255} }; // Example color for now
                canvas->DrawRect(&rect);
            }
        }
    }

    // renderer
    SDL_RenderPresent(renderer);
}