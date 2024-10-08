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
    TetrisGrid(SDL_Renderer* renderer);
    TetrisGrid(Canvas* canvas);
    ~TetrisGrid();
    void Update();
    void Render();
    void ClearLines();
    void GeneratePiece();
    bool MovePiece(int dx, int dy);
    bool RotatePiece();
    bool CheckCollision(int dx, int dy, const RotationalState& state) const;
    void PlacePiece();
    bool isGameOver() const;

private:
    Canvas* canvas;
    SDL_Renderer* renderer;
    Block* currentPiece;
    RotationalState currentPieceState;
    int grid[GRID_HEIGHT][GRID_WIDTH]; // Tetris grid
    Position piecePosition; // Current position of the piece
    bool gameOver;
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
