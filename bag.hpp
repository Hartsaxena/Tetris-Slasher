#pragma once

#include "Tetris.hpp"
#include "Blocks.hpp"
#include <queue>

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

    void AddToQueue(PieceQueue& initialQueue);

private:
    std::queue<Piece*> savedQueue;
    Piece* heldPiece;
    bool isPieceHeld;
};