#include "bag.hpp"
#include <iostream>

Bag::Bag() : heldPiece(nullptr), isPieceHeld(false) {}

Block* Bag::holdPiece(Block* currentPiece) {
    Block* previousHeldPiece = nullptr;

    if (isPieceHeld) {
        previousHeldPiece = heldPiece;
    }

    heldPiece = currentPiece;
    isPieceHeld = true;

    return previousHeldPiece;
}

bool Bag::hasHeldPiece() const {
    return isPieceHeld;
}

Block* Bag::getHeldPiece() const {
    return heldPiece;
}

Block* Bag::getNextPiece() {
    if (pieceQueue.empty()) {
        // If the queue is empty do something idk
        return nullptr;
    }

    Block* nextPiece = pieceQueue.front();
    pieceQueue.pop();
    return nextPiece;
}