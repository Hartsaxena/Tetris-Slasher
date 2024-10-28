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

void Bag::pullFromQueue(BlockQueue& blockQueue) {
    if (blockQueue.getLength() > 0) { 
        if (SavedQueue.size() < 2) {
            Block* pulledBlock = blockQueue.dequeue();
            SavedQueue.push(pulledBlock);
            std::cout << "Pulled From Queue" << std::endl;
        }
        else {
            std::cout << "Cannot store more than 2 blocks in the saved queue." << std::endl;
        }
    }
}

void Bag::AddToQueue(BlockQueue& blockQueue) {
    if (!SavedQueue.empty()) {  
        Block* savedBlock = SavedQueue.front();  
        SavedQueue.pop();  
        blockQueue.enqueue(savedBlock);  
        std::cout << "Added Back to Queue" << std::endl;
    }
}