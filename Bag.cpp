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
    if (SavedQueue.empty()) {
        return nullptr;
    }

    Block* nextBlock = SavedQueue.front();
    SavedQueue.pop();
    return nextBlock;
}

void Bag::pullFromQueue(std::queue<Block*>& initialQueue) {
    if (!initialQueue.empty()) {
        Block* pulledBlock = initialQueue.front(); // Grab the Block from the Queue
        initialQueue.pop(); // Remove the Block
        SavedQueue.push(pulledBlock); // Add the Block
        std::cout << "Pulled From Queue" << std::endl;
    }
}

void Bag::AddToQueue(std::queue<Block*>& initialQueue) {
    if (!initialQueue.empty()) {
        Block* pulledBlock = SavedQueue.front();
        SavedQueue.pop();
        initialQueue.push(pulledBlock);
        std::cout << "Added From Queue" << std::endl;
    }
}