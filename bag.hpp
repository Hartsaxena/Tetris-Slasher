#ifndef BAG_HPP
#define BAG_HPP

#include "Tetris.hpp"
#include "Blocks.hpp"
#include <queue>

class Bag {
public:
    // Constructor
    Bag();

    // Hold the current piece and return the previously held piece
    Block* holdBlock(Block* currentBlock);

    // Check if there is a piece currently held
    bool hasHeldBlock() const;

    // Retrieve the currently held piece
    Block* getHeldBlock() const;

    // Get the next piece from the queue
    Block* getNextBlock();

    void pullFromQueue(std::queue<Block*>& initialQueue);

private:
    std::queue<Block*> BlockQueue;
    Block* heldBlock;
    bool isBlockHeld;
};

#endif