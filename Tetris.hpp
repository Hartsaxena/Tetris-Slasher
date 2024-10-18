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
    TetrisGrid(Canvas* canvas);
    ~TetrisGrid();
    void update();
    void render();
    void clearLines();
    void generatePiece();
    bool movePiece(int dx, int dy);
    bool rotatePiece();
    bool checkCollision();
    bool checkWallCollision(int pieceX, int pieceY) const;
    void placePiece();
    bool isGameOver() const;
    bool getGridCell(int cellX, int cellY) const { return this->grid[cellY][cellX]; }

private:
    Canvas* canvas;
    SDL_Renderer* renderer;
    Block* currentPiece;
    RotationalState currentPieceState;
    int grid[GRID_HEIGHT][GRID_WIDTH]; // Tetris grid
    Position piecePosition; // Current position of the piece
    int& currX = piecePosition.x;
    int& currY = piecePosition.y;
    bool gameOver = false;
};




typedef struct BlockQueueNode {
	explicit BlockQueueNode(Block val) { this->val = val; }

	Block val;
	BlockQueueNode* next;
} BlockQueueNode;

class BlockQueue {
public:
	template<typename... Blocks>
	BlockQueue(Blocks... blockData) {
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