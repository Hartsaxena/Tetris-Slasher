#pragma once

#include "Blocks.hpp"
#include <queue>


class PieceQueueNode {
public:
    explicit PieceQueueNode(Piece* val) : val(val), next(nullptr) {}
    Piece* val;  // Pointer to Piece object
    PieceQueueNode* next;
};

class PieceQueue {
public:
    PieceQueue();
    ~PieceQueue();

    void enqueue(Piece* val);
    Piece dequeue();
    void refillQueue();

    /********* ACCESSOR METHODS **********/

    int getLength() const { return this->length; }
    bool isEmpty() const { return first == nullptr; }
    Piece* getFirstPiece() const { return this->first->val; }
    std::vector<Piece*> peekNextPieces(int count) const;

private:
    PieceQueueNode* first = nullptr;
    PieceQueueNode* last = nullptr;

    int length = 0;

    void generateBag();
    void fillQueueFromBag();

    std::vector<PieceType> blockBag; // Store block types for the bag
};


class Bag {
public:
    // Constructor
    Bag();

    // Hold the current block and return the previously held block
    Piece* holdPiece(Piece* currentPiece);

    // Check if there is a block currently held
    bool hasHeldPiece() const;

    // Retrieve the currently held block
    Piece* getHeldPiece() const;

    // Get the next block from the queue
    Piece* getNextPiece();

    void addToQueue(PieceQueue& initialQueue);

private:
    std::queue<Piece*> savedQueue;
    Piece* heldPiece;
    bool isPieceHeld;
};