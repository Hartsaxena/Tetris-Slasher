#include <iostream>
#include <SDL.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Blocks.hpp"
#include "Render.hpp"
#include "Colors.hpp"

const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 20;

class TetrisGrid {
public:
    explicit TetrisGrid(Canvas* canvas);
    ~TetrisGrid();
    bool update();
    void render();
    void clearLines();
    void generatePiece();
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

    int pointCount = 0;
    int lineFilled;

private:
    Canvas* canvas;
    Block* currentPiece;
    int maxFrameTimer = 30;
    int frameTimer = maxFrameTimer;
    int grid[GRID_HEIGHT][GRID_WIDTH]; // Tetris grid
    Position piecePosition; // Current position of the piece
    int& currX = piecePosition.x;
    int& currY = piecePosition.y;

    bool gameOver = false;

    bool movePiece(int dx = 0, int dy = 0);
};


typedef struct BlockQueueNode {
	explicit BlockQueueNode(Block val) { this->val = val; }

	Block val;
	BlockQueueNode* next;
} BlockQueueNode;

class BlockQueue {
public:
	template<typename... Blocks>
	explicit BlockQueue(Blocks... blockData) {
		static_assert((std::is_same_v<Blocks, Block> && ...), "All entries in BlockQueue must be of type Block\n");
		(this->enqueue(Blocks), ...);
	}
    ~BlockQueue();
    void enqueue(Block);
    Block dequeue();
    int getLength() const { return this->length; }

private:
    BlockQueueNode* first = nullptr;
    BlockQueueNode* last = nullptr;
    int length = 0;
};