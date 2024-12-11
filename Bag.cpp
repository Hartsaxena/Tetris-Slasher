#include <iostream>
#include <random>
#include "Bag.hpp"

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

void Bag::addToQueue(PieceQueue& pieceQueue) {
	if (!savedQueue.empty()) {  // If there is a piece in the saved queue
        Piece* savedPiece = savedQueue.front();  
        savedQueue.pop();  
        pieceQueue.enqueue(savedPiece);  
        std::cout << "Added Bag to PieceQueue" << std::endl;
    }
}

PieceQueue::PieceQueue() {
    std::cout << "Creating new PieceQueue..." << std::endl;
    generateBag();
    fillQueueFromBag();
    std::cout << "You'll never see it comingggg...\n";
}

PieceQueue::~PieceQueue() {
    PieceQueueNode* curr = first;
    while (curr != nullptr) {
        PieceQueueNode* last = curr;
        curr = curr->next;
        delete last->val; // Delete the Block gaming
        delete last;
    }

}

void PieceQueue::enqueue(Piece* val) {
    PieceQueueNode* newFirst = new PieceQueueNode(val);

    newFirst->next = first;

    first = newFirst;

    if (last == nullptr) {
        last = newFirst;
    }

    length++;
}

Piece PieceQueue::dequeue() {
    if (this->first == nullptr) {
        std::cout << "Queue is empty, generating new pieces...\n";
        refillQueue();
    }

    Piece val = *(this->first->val);
    PieceQueueNode* temp = this->first;
    this->first = this->first->next;
    delete temp;
    this->length--;

    std::cout << "Dequeuing piece: " << val.getType() << "\n";

    std::cout << "Current PieceQueue state: ";
    PieceQueueNode* curr = this->first;
    while (curr != nullptr) {
        std::cout << curr->val->getType() << " ";
        curr = curr->next;
    }
    std::cout << std::endl;

    return val;
}


void PieceQueue::generateBag() { // generate the bag w/ 14 pieces
    blockBag = {
        I_PIECE, I_PIECE,
        O_PIECE, O_PIECE,
        S_PIECE, S_PIECE,
        Z_PIECE, Z_PIECE,
        L_PIECE, L_PIECE,
        T_PIECE, T_PIECE,
        J_PIECE, J_PIECE
    };

    // Shuffle the bag
    std::shuffle(blockBag.begin(), blockBag.end(), std::mt19937(std::random_device()()));
}

void PieceQueue::fillQueueFromBag() {
    for (PieceType type : blockBag) {
        Piece* newBlock = new Piece(0, 0, type);
        enqueue(newBlock);
    }
}


void PieceQueue::refillQueue() {
    generateBag();
    fillQueueFromBag();
}

std::vector<Piece*> PieceQueue::peekNextPieces(int count) const {
    std::vector<Piece*> nextPieces;
    PieceQueueNode* current = first;
    int i = 0;

    // Collect the next `count` pieces or fewer if the queue is shorter
    while (current != nullptr && i < count) {
        nextPieces.push_back(current->val);
        current = current->next;
        i++;
    }

    return nextPieces;
}