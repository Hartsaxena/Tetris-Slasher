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
};