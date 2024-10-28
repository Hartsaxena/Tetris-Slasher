#pragma once
#include "Blocks.hpp"
#include <vector>
#include <algorithm>
#include <random>

std::string blockTypeToString(BlockType type);

class BlockQueueNode {
public:
    explicit BlockQueueNode(Block* val) : val(val), next(nullptr) {}
    Block* val;  // Pointer to Block
    BlockQueueNode* next;
};

class BlockQueue {
public:
    BlockQueue();
    ~BlockQueue(); 

    void enqueue(Block* val);
    Block* dequeue();
    int getLength() const { return this->length; }
    bool isEmpty() const { return first == nullptr; }
    void refillQueue();

private:
    BlockQueueNode* first = nullptr;
    BlockQueueNode* last = nullptr;
    int length = 0;

    void generateBag();
    void fillQueueFromBag();
    std::vector<BlockType> blockBag; // Store block types for the bag
};