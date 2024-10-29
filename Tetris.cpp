#include <iostream>
#include "Tetris.hpp"
#include "Blocks.hpp"
#include <string>


BlockQueue::BlockQueue() {
    generateBag();
    fillQueueFromBag();
}

BlockQueue::~BlockQueue() {
    BlockQueueNode* curr = first;
    while (curr != nullptr) {
        BlockQueueNode* last = curr;
        curr = curr->next;
        delete last->val; // Delete the Block gaming
        delete last;
    }
}

void BlockQueue::enqueue(Block* val) {
    BlockQueueNode* newFirst = new BlockQueueNode(val);

    newFirst->next = first;

    first = newFirst;

    if (last == nullptr) {
        last = newFirst;
    }

    length++;
}

Block* BlockQueue::dequeue() {
    if (this->first == nullptr) {  
        std::cout << "Queue is empty, generating new blocks...\n";
        refillQueue();
    }

    Block* val = this->first->val;  
    BlockQueueNode* temp = this->first;  
    this->first = this->first->next;  
    delete temp;  
    this->length--;  
    return val;  
}

void BlockQueue::generateBag() { // generate the bazg w/ 14 pieces
    blockBag = {
        I_BLOCK, I_BLOCK,
        O_BLOCK, O_BLOCK,
        S_BLOCK, S_BLOCK,
        Z_BLOCK, Z_BLOCK,
        L_BLOCK, L_BLOCK,
        T_BLOCK, T_BLOCK,
        J_BLOCK, J_BLOCK
    };

    // Shuffle the bag
    std::shuffle(blockBag.begin(), blockBag.end(), std::mt19937(std::random_device()()));
}

void BlockQueue::fillQueueFromBag() {
    for (BlockType type : blockBag) {
        Block* newBlock = new Block(type); 
        enqueue(newBlock);
    }
}

void BlockQueue::refillQueue() {
    generateBag();           
    fillQueueFromBag();     
}

std::string blockTypeToString(BlockType type) {
    switch (type) {
    case I_BLOCK: return "I_BLOCK";
    case O_BLOCK: return "O_BLOCK";
    case S_BLOCK: return "S_BLOCK";
    case Z_BLOCK: return "Z_BLOCK";
    case L_BLOCK: return "L_BLOCK";
    case T_BLOCK: return "T_BLOCK";
    case J_BLOCK: return "J_BLOCK";
    default: return "UNKNOWN_BLOCK";
    }
}