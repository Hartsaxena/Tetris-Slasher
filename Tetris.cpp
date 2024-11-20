#include <iostream>
#include "Tetris.hpp"
#include "Blocks.hpp"
#include "Front.hpp"
#include "Render.hpp"
#include "Colors.hpp"
#include "Bag.hpp"



TetrisGrid::TetrisGrid(Canvas* canvas, BlockQueue* blockQueue) {
    this->canvas = canvas;
    this->blockQueue = blockQueue;  
    this->bag = bag;
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
    if (blockQueue->getLength() == 3) {
        std::cout << "Queue is empty! Regenerating..." << std::endl;
        blockQueue->refillQueue();
    }

    Block* nextPiece = blockQueue->getFirstBlock();
    std::cout << nextPiece->getType() << std::endl;
    currentPiece = blockQueue->dequeue();

    piecePosition = { 4, 0 };
    ghostPosition = { 4, 0 };
    if (checkCollision()) {
        gameOver = true;
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
    bag->resetHoldStatus();
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
        ghostPosition = calculateLandingPosition();
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
            if (grid[y][x] != 0) {
                Rectangle rect = { x * 30, y * 30, 30, 30, Color{GRAY} };
                canvas->DrawRect(&rect);
            }
            else {
                Rectangle emptyRect = { x * 30, y * 30, 30, 30, Color{WHITE} };
                canvas->DrawEmptyRect(&emptyRect);
            }
        }
    }

    // Render the current piece
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (RotationalStates::getCell(currentPiece->getCurrentState(), row, col)) {
                Rectangle rect = { (piecePosition.x + col) * 30, (piecePosition.y + row) * 30, 30, 30, Color{RED} };
                canvas->DrawRect(&rect);
            }
        }
    }
    // Render the ghosty piece
    Position ghostPosition = calculateLandingPosition();
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (RotationalStates::getCell(currentPiece->getCurrentState(), row, col)) {
                Rectangle ghostRect = {
                    (ghostPosition.x + col) * 30,
                    (ghostPosition.y + row) * 30,
                    30,
                    30,
                    Color{192, 192, 192, 128} // Light gray with transparency
                };
                canvas->DrawRect(&ghostRect);
            }
        }
    }
    // Render the next three pieces in the queue
    std::vector<Block*> nextPieces = blockQueue->peekNextPieces(3);
    int previewStartX = 400;
    int previewStartY = 50;
    int blockSize = 20;
    int previewSpacing = 100;

    // Clear the preview area
    Rectangle previewClearRect = { previewStartX, previewStartY, blockSize * 4, previewSpacing * 3, Color{BLACK} };
    canvas->DrawRect(&previewClearRect);

    for (int i = 0; i < nextPieces.size(); ++i) {
        Block* piece = nextPieces[i];
        RotationalState previewState = piece->rotationalStates.getHead()->data;

        int offsetY = previewStartY + i * previewSpacing;

        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                if (RotationalStates::getCell(previewState, row, col)) {
                    Rectangle previewRect = {
                        previewStartX + col * blockSize,
                        offsetY + row * blockSize,
                        blockSize,
                        blockSize,
                        Color{RED}
                    };
                    canvas->DrawRect(&previewRect);
                }
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


bool TetrisGrid::checkGhostCollision() const {
    RotationalState pieceState = this->currentPiece->getCurrentState();
    for (int row = 0; row < 4; row++) {    // Row
        for (int col = 0; col < 4; col++) { // Column
            bool cell = RotationalStates::getCell(pieceState, row, col);
            if (!cell) {
                continue;
            }

            int ghostRelativeX = ghostPosition.x + col;
            int ghostRelativeY = ghostPosition.y + row;


            // Check if out of bounds or if there is a filled cell at the grid position
            if (ghostRelativeX < 0 || ghostRelativeX >= GRID_WIDTH || this->ghostY < 0 || (this->getGridCell(ghostRelativeX, ghostRelativeY))) {
                 return true;
            }
            return false;
        }
    }
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

Position TetrisGrid::calculateLandingPosition() {
    ghostPosition = piecePosition;

    // Move down until a collision is detected
    while (!checkGhostCollision()) {
        ghostPosition.y += 1; // Move the ghost piece down
    }

    ghostPosition.y -= 2;
    return ghostPosition;
}



// this is where TetrisGrid ends and BlockQueue Starts

void TetrisGrid::setBag(Bag* bag) {
    this->bag = bag;
}

BlockQueue::BlockQueue() {
    std::cout << "CREATING A NEW BLOCKQ" << std::endl;
    generateBag();
    fillQueueFromBag();
}

BlockQueue::~BlockQueue() {
    BlockQueueNode* curr = first;
    while (curr != nullptr) {
        BlockQueueNode* last = curr;
        curr = curr->next;
        delete last->val; // Delete the Block gaming
        delete last;
    }

}

void BlockQueue::enqueue(Block* val) {
    BlockQueueNode* newFirst = new BlockQueueNode(val);

    newFirst->next = first;

    first = newFirst;

    if (last == nullptr) {
        last = newFirst;
    }

    length++;
}

Block* BlockQueue::dequeue() {
    if (this->first == nullptr) {
        std::cout << "Queue is empty, generating new blocks...\n";
        refillQueue();
    }

    Block* val = this->first->val;
    BlockQueueNode* temp = this->first;
    this->first = this->first->next;
    delete temp;
    this->length--;

    std::cout << "Dequeuing block: " << val->getType() << "\n";

    std::cout << "Current BlockQueue state: ";
    BlockQueueNode* current = this->first;
    while (current != nullptr) {
        std::cout << current->val->getType() << " ";
        current = current->next;
    }
    std::cout << std::endl;

    return val;
}


void BlockQueue::generateBag() { // generate the bazg w/ 14 pieces
    blockBag = {
        I_BLOCK, I_BLOCK,
        O_BLOCK, O_BLOCK,
        S_BLOCK, S_BLOCK,
        Z_BLOCK, Z_BLOCK,
        L_BLOCK, L_BLOCK,
        T_BLOCK, T_BLOCK,
        J_BLOCK, J_BLOCK
    };

    // Shuffle the bag
    std::shuffle(blockBag.begin(), blockBag.end(), std::mt19937(std::random_device()()));
}

void BlockQueue::fillQueueFromBag() {
    for (BlockType type : blockBag) {
        Block* newBlock = new Block(type);
        enqueue(newBlock);
    }
}


void BlockQueue::refillQueue() {
    generateBag();
    fillQueueFromBag();
}

std::vector<Block*> BlockQueue::peekNextPieces(int count) {
    std::vector<Block*> nextPieces;
    BlockQueueNode* current = first;
    int i = 0;

    // Collect the next `count` pieces or fewer if the queue is shorter
    while (current != nullptr && i < count) {
        nextPieces.push_back(current->val);
        current = current->next;
        i++;
    }

    return nextPieces;
}
Block* BlockQueue::getFirstBlock() const {
    if (first != nullptr) {
        return first->val;  // Return the first block
    }
    return nullptr;
}