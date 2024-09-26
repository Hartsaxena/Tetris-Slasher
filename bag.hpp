#ifndef BAG_HPP
#define BAG_HPP

#include "Tetris.hpp"
#include "Blocks.hpp"
#include <queue>

class Bag {
public:
    // Constructor
    Bag();

    // Hold the current piece and return the previously held piece
    Block* holdPiece(Block* currentPiece);

    // Check if there is a piece currently held
    bool hasHeldPiece() const;

    // Retrieve the currently held piece
    Block* getHeldPiece() const;

    // Get the next piece from the queue
    Block* getNextPiece();

private:
    std::queue<Block*> pieceQueue;
    Block* heldPiece;
    bool isPieceHeld;
};

#endif