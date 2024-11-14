#pragma once

#include <iostream>
#include <SDL.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <type_traits>
#include "Blocks.hpp"
#include "Render.hpp"
#include "Colors.hpp"

/**
 * @brief A class that represents the Tetris grid.
 */
class TetrisGrid {
public:

    const int GRID_WIDTH = 10;
    const int GRID_HEIGHT = 20;
    const int NEW_PIECE_X = GRID_WIDTH / 2;
    const int NEW_PIECE_Y = 2;

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

private:
    const int maxFrameTimer = 30; // Move the piece down automatically every _ frames
    int frameTimer = maxFrameTimer;
    bool gameOver = false;

    std::vector<Block> blocks;
    Piece* currentPiece = nullptr;

    /**
     * @brief Sets the currently active piece onto the grid, freezing it in place. Then, generates a new
     * currently selected piece.
     */
    void newPiece();

    /**
     * @brief Sets the currently active piece onto the grid, freezing it in place.
     */
    void setPiece();

    /**
     * @brief Method for detecting whether the currently selected piece overlaps with the existing blocks on the grid.
	 * @return returns true if the piece is colliding with the walls or other blocks, false otherwise.
     */
    bool checkCollision() const;

    
};


typedef struct PieceQueueNode {
    explicit PieceQueueNode(Piece val) { this->val = val; this->next = nullptr; }

	Piece val;
    PieceQueueNode* next;
} PieceQueueNode;

class PieceQueue {
public:
	template<typename... Pieces>
	explicit PieceQueue(Pieces... blockData) {
		static_assert((std::is_same_v<Pieces, Piece> && ...), "All entries in PieceQueue must be of type Piece\n");
		(this->enqueue(Pieces), ...);
	}
    ~PieceQueue();
    void enqueue(Piece piece);
    Piece dequeue();
    int getLength() const { return this->length; }

private:
    PieceQueueNode* first = nullptr;
    PieceQueueNode* last = nullptr;
    int length = 0;
};