#include <iostream>
#include <SDL.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Blocks.hpp"
#include "Render.hpp"
#include "Colors.hpp"
#include <algorithm>
#include <random>
#include <queue>
#pragma once 

class BlockQueueNode;
class BlockQueue;
class Bag;

const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 20;

class BlockQueueNode {
public:
    explicit BlockQueueNode(Block* val) : val(val), next(nullptr) {}
    Block* val;  // Pointer to Block
    BlockQueueNode* next;
};

class BlockQueue {
public:
    BlockQueue();
    ~BlockQueue();

    void enqueue(Block* val);
    Block* dequeue();
    int getLength() const { return this->length; }
    bool isEmpty() const;
    void refillQueue();
    Block* getFirstBlock() const;
private:
    BlockQueueNode* first = nullptr;
    BlockQueueNode* last = nullptr;
    int length = 0;

    void generateBag();
    void fillQueueFromBag();
    std::vector<BlockType> blockBag; // Store block types for the bag
};


class TetrisGrid {
public:
    explicit TetrisGrid(Canvas* canvas, BlockQueue* blockQueue); // Use pointer to BlockQueue
    ~TetrisGrid();

    bool update();
    void render();
    void clearLines();
    void generatePiece();
    void generateSavedPiece();
    bool rotatePiece();
    bool forceRotate();
    bool checkCollision() const;
    bool checkFloorCollision() const;
    bool checkWallCollision() const;
    int pointCalculator(int lineAmount);
    bool moveRight() { return movePiece(1, 0); }
    bool moveLeft() { return movePiece(-1, 0); }
    bool moveDown() { return movePiece(0, 1); }
    void instantDown();

    void placePiece();
    bool isGameOver() const;
    bool getGridCell(int cellX, int cellY) const { return this->grid[cellY][cellX]; }
    void echoState() const;
    void setBag(Bag* bag);

    int pointCount = 0;
    int lineFilled;
    Block* currentPiece;
    Block* nextBlock;

private:
    Canvas* canvas;
    BlockQueue* blockQueue;  // Use pointer to BlockQueue
    Bag* bag;
    int maxFrameTimer = 30;
    int frameTimer = maxFrameTimer;
    int grid[GRID_HEIGHT][GRID_WIDTH]; // Tetris grid
    Position piecePosition; // Current position of the piece
    int& currX = piecePosition.x;
    int& currY = piecePosition.y;

    bool gameOver = false;

    bool movePiece(int dx = 0, int dy = 0);
};

