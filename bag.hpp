#ifndef BAG_HPP
#define BAG_HPP

#include "Tetris.hpp"
#include "Blocks.hpp"
#include <queue>

class Bag {
public:

    Bag(BlockQueue& blockQueue, TetrisGrid* tetrisGrid);
    ~Bag();

    Block* holdBlock(Block* currentBlock);

    bool hasHeldBlock() const;

    Block* getHeldBlock() const;

    Block* getNextBlock();

    int getBagSize() const;

    void pullFromQueue(BlockQueue* blockQueue);

    void AddToQueue(BlockQueue& initialQueue);

    Block* getSavedBlock();

    void printSavedQueue() const;

private:
    TetrisGrid* tetrisGrid;
    std::queue<Block*> SavedQueue;
    Block* heldBlock;
    bool isBlockHeld;
};

#endif