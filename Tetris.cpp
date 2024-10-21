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
        delete last->val; // Delete the allocated Block
        delete last;
    }
}

void BlockQueue::enqueue(Block* val) {
    if (first == nullptr) { // First entry in list
        first = new BlockQueueNode(val);
        last = first;
    }
    else {
        BlockQueueNode* newLast = new BlockQueueNode(val);
        last->next = newLast;
        last = newLast;
    }
    length++;
}

Block* BlockQueue::dequeue() {
    if (this->first == nullptr) {  // Check if the queue is empty
        std::cout << "Queue is empty, generating new blocks...\n";
        refillQueue();              // Call to refill the queue
    }

    Block* val = this->first->val;  // Retrieve the value at the front
    BlockQueueNode* temp = this->first;  // Store the current front node
    this->first = this->first->next;  // Move the front pointer to the next node
    delete temp;  // Delete the old front node to free memory
    this->length--;  // Decrease the queue length
    return val;  // Return the dequeued block
}

void BlockQueue::generateBag() {
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
        Block* newBlock = new Block(type); // Dynamically allocate Block
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