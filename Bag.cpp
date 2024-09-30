#include "bag.hpp"
#include <iostream>

Bag::Bag() : heldBlock(nullptr), isBlockHeld(false) {}

Block* Bag::holdBlock(Block* currentBlock) {
    Block* previousHeldBlock = nullptr;

    if (isBlockHeld) {
        previousHeldBlock = heldBlock;
    }

    heldBlock = currentBlock;
    isBlockHeld = true;

    return previousHeldBlock;
}

bool Bag::hasHeldBlock() const {
    return isBlockHeld;
}

Block* Bag::getHeldBlock() const {
    return heldBlock;
}

Block* Bag::getNextBlock() {
    if (BlockQueue.empty()) {
        return nullptr;
    }

    Block* nextBlock = BlockQueue.front();
    BlockQueue.pop();
    return nextBlock;
}

void Bag::pullFromQueue(std::queue<Block*>& initialQueue) {
    if (!initialQueue.empty()) {
        Block* pulledBlock = initialQueue.front(); // Grab the Block from the Queue
        initialQueue.pop(); // Remove the Block
        BlockQueue.push(pulledBlock); // Add the Block
    }
}

void Bag::AddToQueue(std::queue<Block*>& initialQueue) {
    if (!initialQueue.empty()) {
        Block* pulledBlock = BlockQueue.front();
        BlockQueue.pop();
        initialQueue.push(pulledBlock);
    }
}
