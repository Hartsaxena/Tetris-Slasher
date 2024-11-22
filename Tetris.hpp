#pragma once

#include <SDL.h>
#include <vector>
#include "Blocks.hpp"

class PieceQueue;

/**
 * @brief A class that represents the Tetris grid.
 */
class TetrisGrid {
public:

    const int GRID_WIDTH = 10;
    const int GRID_HEIGHT = 20;
 /*   const int NEW_PIECE_X = GRID_WIDTH / 2;
    const int NEW_PIECE_Y = 2;*/

    const int NEW_PIECE_X = 4;
    const int NEW_PIECE_Y = 3;

	/**
	 * @brief Constructs a new TetrisGrid object.
	 */
	explicit TetrisGrid();
	~TetrisGrid();

    /********* MOVEMENT CODE **********/

    /**
     * @brief Updates the grid by one frame
     */
    void update();

    /**
     * @brief Moves the currently active piece down by one.
	 * @return Returns true if the piece is successfully moved down, false if the piece is unable to move down.
     */
    bool moveDown();
    /**
     * @brief Moves the currently active piece left by one.
     * @return Returns true if the piece is successfully moved left, false if the piece is unable to move left.
     */
    bool moveLeft();
    /**
     * @brief Moves the currently active piece right by one.
     * @return Returns true if the piece is successfully moved right, false if the piece is unable to move right.
     */
	bool moveRight();
    /**
     * @brief Rotate the currently active piece clockwise
     * @return Returns true if the piece is successfully rotated, false if otherwise.
     */
    bool rotate();
    /**
     * @brief Instantly moves the active piece down until it can't any longer.
     */
    void snapDown();


    /********* ACCESSOR METHODS **********/

	/**
	 * @brief Getter method for TetrisGrid::gameOver
	 * @return true if the game is over, false if it is not.
	 */
	bool getGameOver() const { return this->gameOver; }
    std::vector<Block> getBlocks() const { return this->blocks; }
    const Piece* getCurrentPiece() const { return this->currentPiece; }
    std::vector<Block> getPieceBlocks() const { return this->getCurrentPiece()->getAbsoluteBlocks(); }
	std::vector<Block> getGhostBlocks() const { return this->ghostPiece->getAbsoluteBlocks(); }

private:
    const int maxFrameTimer = 30; // Move the piece down automatically every _ frames
    int frameTimer = maxFrameTimer;
    bool gameOver = false;

    std::vector<Block> blocks;
    Piece* currentPiece = nullptr;
    Piece* ghostPiece = nullptr;

    PieceQueue* pieceQueue;

    /**
     * @brief Clears all completed lines in the grid.
     */
    void clearLines();

    /**
     * @brief Sets the currently active piece onto the grid, freezing it in place. Then, generates a new
     * currently selected piece.
     */
    void newPiece();

    /**
     * @brief Sets the currently active piece onto the grid.
     */
    void setPiece();

    /**
     * @brief Method for detecting whether the currently selected piece overlaps with the existing blocks on the grid.
	 * @return returns true if the piece is colliding with the walls or other blocks, false otherwise.
     */
    bool checkCollision() const;

    /**
     * @brief Moves the preview ghost piece down by one.
     * @return Returns true if the piece is successfully moved down, false if the piece is unable to move down.
     */
    bool moveGhostDown();

    /**
     * @brief Snaps the ghost piece down to the landing position.
     */
    void calculateLandingPosition() { while (this->moveGhostDown()) {} }

	bool checkGhostCollision() const;
};

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

    std::vector<Piece*> peekNextPieces(int count);
    void enqueue(Piece* val);
    Piece dequeue();
    int getLength() const { return this->length; }
    bool isEmpty() const { return first == nullptr; }
    void refillQueue();
    Piece* getFirstPiece() const { return this->first->val; }

private:
    PieceQueueNode* first = nullptr;
    PieceQueueNode* last = nullptr;

    int length = 0;

    void generateBag();
    void fillQueueFromBag();


    std::vector<PieceType> blockBag; // Store block types for the bag
};