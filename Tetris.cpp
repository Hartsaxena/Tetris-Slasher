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
    currentPiece = new Block(static_cast<BlockType>(randomBlockType));

    piecePosition = { 4, 0 }; // top of piece grid
    if (checkCollision()) {
        gameOver = true; // Game over if the new piece cannot be placed
    }
}

/*
Notice: dx and dy represent changes (delta) in those values. For example, moving 2 squares to the right would be dx = 2, dy = 0.
*/
bool TetrisGrid::movePiece(int dx, int dy) {
    piecePosition.x += dx;
    piecePosition.y += dy;
    bool wallCollision = checkWallCollision();
    bool floorCollision = checkFloorCollision();
    bool collision = checkCollision();

    if (wallCollision || collision || floorCollision) {
        if (dy == 0) {
            std::cout << "";
        }

        piecePosition.x -= dx;
        piecePosition.y -= dy;

        if (floorCollision || (collision && dy != 0)) {
            // Only place the piece if its touching the floor or if its colliding with the existing structure AND its not moving to the side.
            placePiece();
        }

        return false;
    }

    return true;
}

void TetrisGrid::instantDown() {
    bool status = true;
    while (status) {
        status = moveDown();
    }

}

bool TetrisGrid::rotatePiece() {
    // Save the current piece's rotational state before attempting to rotate
    currentPiece->rotate();

    // Check if the new rotated state causes a collision
    if (!(checkCollision() || checkWallCollision())) {
        // No collision, rotation successful
        return true;
    }

    this->forceRotate();

    return false;
}


bool TetrisGrid::forceRotate() {
    // Force a rotate, but move the block inwards so it fits in the grid.

    // Detect which side of the grid the piece is on (and thus which wall is being collided with)
    bool closestWall = (GRID_WIDTH - this->currX) < this->currX; // false = left, true = right

    while (checkCollision() || checkWallCollision()) {
        if (closestWall)
            moveLeft();
        else
            moveRight();
    }

    return true;
}


void TetrisGrid::placePiece() {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (RotationalStates::getCell(currentPiece->getCurrentState(), row, col)) {
                grid[piecePosition.y + row][piecePosition.x + col] = 1; // Mark the grid as filled
            }
        }
    }
    clearLines(); // clears full filled line on grid
    generatePiece(); // gives new piece when placed
}

void TetrisGrid::clearLines() {
    int lineFilled = 0;
    for (int y = 0; y < GRID_HEIGHT; y++) {
        lineFilled++;

        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[y][x] == 0) {
                lineFilled = 0;
                break;
            }
        }
        if (lineFilled >= 1) {
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
            // call our point calculator
            pointCalculator(lineFilled);
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
        moveDown();
        this->frameTimer = maxFrameTimer;
    }

    return true;
}

void TetrisGrid::render() {
    // Render points
    canvas->displayInt(this->pointCount, 30);

    // Render grid
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[y][x] != 0) { // If not empty
                Rectangle rect = { x * 30, y * 30, 30, 30, Color{GRAY} };// Example color for filled for now
                canvas->DrawRect(&rect);
            }
            else {
                Rectangle emptyrect{ x * 30, y * 30, 30, 30, Color{WHITE} };
                canvas->DrawEmptyRect(&emptyrect);
            }
        }
    }

    // Render the current piece
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (RotationalStates::getCell(currentPiece->getCurrentState(), row, col)) {
                Rectangle rect = { (piecePosition.x + col) * 30, (piecePosition.y + row) * 30, 30, 30, Color{RED} }; // Example color for now
                canvas->DrawRect(&rect);
            }
        }
    }
}


/*
Returns true if there is collision between the current piece and the grid.
*/
bool TetrisGrid::checkCollision() const {
	RotationalState pieceState = this->currentPiece->getCurrentState();
	for (int y = 3; y >= 0; y--) {    // Row
		for (int x = 0; x < 4; x++) { // Column
			bool val = RotationalStates::getCell(pieceState, y, x);
			if (val == 0) {
				continue;
			}

			int gridRelativeX = this->currX + x;
			int gridRelativeY = this->currY + y;

			// Check collision with other grid cells
			if (this->getGridCell(gridRelativeX, gridRelativeY)) {
				return true;
			}
		}
	}

	return false;
}

bool TetrisGrid::checkFloorCollision() const {
    return this->currY < 0;
}

bool TetrisGrid::checkWallCollision() const {
    RotationalState pieceState = this->currentPiece->getCurrentState();
    for (int y = 3; y >= 0; y--) {    // Row
        for (int x = 0; x < 4; x++) { // Column
            bool val = RotationalStates::getCell(pieceState, y, x);
            if (val == 0) {
                continue;
            }

            int gridRelativeX = this->currX + x;
            int gridRelativeY = this->currY + y;

            if (gridRelativeX < 0 || gridRelativeX >= GRID_WIDTH) {
                return true;
            }
        }
    }

    return false;
}


int TetrisGrid::pointCalculator(int lineAmount) {
    if (lineAmount == 1) {
        pointCount += (lineAmount * 100);
    }
    else if (lineAmount == 2) {
        pointCount += (lineAmount * 300);
    }
    else if (lineAmount == 3) {
        pointCount += (lineAmount * 500);
    }
    else if (lineAmount == 4) {
        pointCount += (lineAmount * 800);
    }
    lineFilled = 0;
    return pointCount;
}