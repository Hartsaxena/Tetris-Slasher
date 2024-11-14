#include "bag.hpp"
#include <iostream>

Bag::Bag(BlockQueue& blockQueue, TetrisGrid* tetrisGrid)
    : heldBlock(nullptr), isBlockHeld(false), tetrisGrid(tetrisGrid) {
}
Bag::~Bag() {
    std::cout << "Bag destructor called." << std::endl;
}

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
int Bag::getBagSize() const {
    return SavedQueue.size();
}

void Bag::pullFromQueue(BlockQueue* blockQueue) {
    std::cout << "Bag instance: " << this << ", TetrisGrid pointer in Bag: " << this->tetrisGrid << std::endl;

    if (SavedQueue.size() <= 2) {
        if (tetrisGrid == nullptr) {
            std::cerr << "Error: tetrisGrid is null in pullFromQueue!" << std::endl;
            return;
        }

        Block* currentBlock = tetrisGrid->nextBlock;

        if (currentBlock != nullptr) {
            SavedQueue.push(currentBlock);
            std::cout << "Pulled From Queue: " << currentBlock->getType() << std::endl;
        }
    }

    printSavedQueue();
}

void Bag::AddToQueue(BlockQueue& blockQueue) {
    // Step 1: Enqueue the currentBlock from TetrisGrid (this is the "current piece" in play)
    if (tetrisGrid != nullptr && tetrisGrid->nextBlock != nullptr) {
        Block* currentBlock = tetrisGrid->nextBlock;
        blockQueue.enqueue(currentBlock);
        std::cout << "Added Current Block to Queue: " << currentBlock->getType() << std::endl;
    }

    // Step 2: Enqueue the saved block from SavedQueue
    if (!SavedQueue.empty()) {
        Block* savedBlock = SavedQueue.front();
        SavedQueue.pop();
        blockQueue.enqueue(savedBlock);
        std::cout << "Added Saved Block to Queue: " << savedBlock->getType() << std::endl;
    }

    printSavedQueue();
}

Block* Bag::getSavedBlock() {
    if (!SavedQueue.empty()) {
        return SavedQueue.front();
    }
    std::cout << "No saved block available." << std::endl;
    return nullptr;
}

void Bag::printSavedQueue() const {
    std::cout << "Current SavedQueue state: ";
    std::queue<Block*> tempQueue = SavedQueue;
    while (!tempQueue.empty()) {
        Block* block = tempQueue.front();
        std::cout << block->getType() << " ";
        tempQueue.pop();
    }
    std::cout << std::endl;
}
