#include "bag.hpp"
#include <iostream>

Bag::Bag() : heldPiece(nullptr), isPieceHeld(false) {}

Piece* Bag::holdPiece(Piece* currentPiece) {
    Piece* previousHeldPiece = nullptr;

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

Piece* Bag::getHeldPiece() const {
    return heldPiece;
}

Piece* Bag::getNextPiece() {
    if (savedQueue.empty()) {
        return nullptr;
    }

    Piece* nextPiece = savedQueue.front();
    savedQueue.pop();
    return nextPiece;
}

void Bag::AddToQueue(PieceQueue& pieceQueue) {
    if (!savedQueue.empty()) {  
        Piece* savedPiece = savedQueue.front();  
        savedQueue.pop();  
        pieceQueue.enqueue(savedPiece);  
        std::cout << "Added Back to Queue" << std::endl;
    }
}