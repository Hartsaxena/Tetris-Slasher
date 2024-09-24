#pragma once
#include "Blocks.hpp"

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

class TetrisGrid {
public:
	TetrisGrid();
	~TetrisGrid();

private:
	const int xDimension = 10;
	const int yDimension = 20;

	// 2D array of booleans, representing whether a cell is filled with a block or not
	bool grid[10][20]; // Dimensions: 10(x) by 20(y)

	// Pointer to the current moving piece
	Block* curr;
	int currX, currY; // Representing top left of piece

	bool getGridCell(int row, int col) const { return this->grid[row][col]; }
	bool checkCollision();
	bool checkWallCollision(int pieceX, int pieceY) const;
};