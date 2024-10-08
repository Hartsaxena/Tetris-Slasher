#ifndef BAG_HPP
#define BAG_HPP

#include "Tetris.hpp"
#include "Blocks.hpp"
#include <queue>

class Bag {
public:
    // Constructor
    Bag();

    // Hold the current block and return the previously held block
    Block* holdBlock(Block* currentBlock);

    // Check if there is a block currently held
    bool hasHeldBlock() const;

    // Retrieve the currently held block
    Block* getHeldBlock() const;

    // Get the next block from the queue
    Block* getNextBlock();

    // pull a Block from the initial Queue to store
    void pullFromQueue(std::queue<Block*>& initialQueue);

    void AddToQueue(std::queue<Block*>& initialQueue);

private:
    std::queue<Block*> SavedQueue;
    Block* heldBlock;
    bool isBlockHeld;
};

#endif