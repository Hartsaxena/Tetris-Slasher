#pragma once
#include <iostream>
typedef enum PieceType {
	I_PIECE,
	O_PIECE,
	S_PIECE,
	Z_PIECE,
	L_PIECE,
	T_PIECE,
	J_PIECE,
} PieceType;


/* Block Restructuring. Here's my new idea that was proposed in class today:
* 
* Store Blocks as objects that represent a single square on the tetris grid.
* In the TetrisGrid object, store the currently selected piece as an array of 4 instances of Block.
* Should be simple, right?
*/

class Block {
public:
    /**@brief Constructs a new Block object.
	 *
     * @param x The x position of the block.
     * @param y The y position of the block.
     * @param immortal Whether the block is immortal (default is false).
	 */
	Block() { x = 0; y = 0; immortal = false; }
	Block(int x, int y, bool immortal = false) { this->x = x; this->y = y; this->immortal = immortal; }

	int x, y;
	bool immortal = false;
};

typedef struct RotationalState {
	Block blocks[4];
} RotationalState;

/**
 * @brief Responsible for managing all 4 rotational states of a single type of piece in Tetris (e.g., L-Piece).
 */
class Piece {
public:

	int x, y; // The absolute position of the piece's top-left corner.

	/**
	 * @brief Constructs a new Piece object.
	 * @param x The 'x' position of the piece's left-most tile.
	 * @param y The 'y' position of the piece's left-most tile.
	 * @param type The type of block to create (default is O_PIECE).
	 */
	explicit Piece(int x = 0, int y = 0, PieceType type = O_PIECE);

	/**
	 * @brief Rotates the Piece object 90 degrees clockwise.
	 */
	void rotate() {
		this->currentRotation = (this->currentRotation + 1) % 4;
		std::cout << "NEW ROTATION IS " << this->currentRotation << std::endl;
	}
	void moveUp()    { y--; }
	void moveDown()  { y++; }
	void moveLeft()  { x--; }
	void moveRight() { x++; }

	/********* ACCESSOR METHODS **********/

    RotationalState getCurrentState() const { return rotateStates[currentRotation]; }
	/**
	 * @brief Gets the 4 blocks with absolute positions.
	 * @return A vector of Block objects.
	 */
	std::vector<Block> getAbsoluteBlocks() const;

	PieceType getType() const { return this->type; }

private:
	int currentRotation = 0;
	PieceType type;
	RotationalState rotateStates[4];
};


namespace Rotations {
	// Pieces for each rotational state of each block type

	/**
	 * @brief Casts a block to an absolute position based on where it's topleft corner is.
	 * @param block pointer to a Block object, to be casted.
	 * @param x top-left x position
	 * @param y top-left y position
	 */
	void castBlock(Block* block, int x, int y);
	RotationalState castRotationalState(const RotationalState* state, int x, int y);

	// I Block
	const RotationalState I_STATES[4] =
	{
		{
		Block(0, 1),
		Block(1, 1),
		Block(2, 1),
		Block(3, 1)
		},
		{
		Block(2, 0),
		Block(2, 1),
		Block(2, 2),
		Block(2, 3)
		},
		{
		Block(0, 2),
		Block(1, 2),
		Block(2, 2),
		Block(3, 2)
		},
		{
		Block(1, 0),
		Block(1, 1),
		Block(1, 2),
		Block(1, 3)
		}
	};

	// J Block
	const RotationalState J_STATES[4] =
	{
		{
		Block(0, 0),
		Block(0, 1),
		Block(1, 1),
		Block(2, 1)
		},
		{
		Block(1, 0),
		Block(2, 0),
		Block(1, 1),
		Block(1, 2)
		},
		{
		Block(0, 1),
		Block(1, 1),
		Block(2, 1),
		Block(2, 2)
		},
		{
		Block(1, 0),
		Block(1, 1),
		Block(1, 2),
		Block(0, 2)
		}
	};

	// L Block
	const RotationalState L_STATES[4] =
	{
		{
		Block(0, 1),
		Block(1, 1),
		Block(2, 1),
		Block(2, 0)
		},
		{
		Block(1, 0),
		Block(1, 1),
		Block(1, 2),
		Block(2, 2)
		},
		{
		Block(0, 1),
		Block(0, 2),
		Block(1, 1),
		Block(2, 1)
		},
		{
		Block(0, 0),
		Block(1, 0),
		Block(1, 1),
		Block(1, 2)
		}
	};

	// S Block
	const RotationalState S_STATES[4] =
	{
		{
		Block(0, 1),
		Block(1, 0),
		Block(1, 1),
		Block(2, 0)
		},
		{
		Block(1, 0),
		Block(1, 1),
		Block(2, 1),
		Block(2, 2)
		},
		{
		Block(1, 1),
		Block(0, 2),
		Block(1, 2),
		Block(2, 1)
		},
		{
		Block(0, 0),
		Block(0, 1),
		Block(1, 1),
		Block(1, 2)
		}
	};

	// T Block
	const RotationalState T_STATES[4] =
	{
		{
		Block(1, 0),
		Block(0, 1),
		Block(1, 1),
		Block(2, 1)
		},
		{
		Block(1, 0),
		Block(1, 1),
		Block(2, 1),
		Block(1, 2)
		},
		{
		Block(0, 1),
		Block(1, 1),
		Block(2, 1),
		Block(1, 2)
		},
		{
		Block(1, 0),
		Block(0, 1),
		Block(1, 1),
		Block(1, 2)
		}
	};

	// Z Block
	const RotationalState Z_STATES[4] =
	{
		{
		Block(0, 0),
		Block(1, 0),
		Block(1, 1),
		Block(2, 1)
		},
		{
		Block(2, 0),
		Block(2, 1),
		Block(1, 1),
		Block(1, 2)
		},
		{
		Block(0, 1),
		Block(1, 1),
		Block(1, 2),
		Block(2, 2)
		},
		{
		Block(1, 0),
		Block(0, 1),
		Block(1, 1),
		Block(0, 2)
		}
	};

	// O Block
	const RotationalState O_STATES[4] =
	{
		{
		Block(0, 0),
		Block(1, 0),
		Block(1, 1),
		Block(0, 1)
		},
		{
		Block(0, 0),
		Block(1, 0),
		Block(1, 1),
		Block(0, 1)
		},
		{
		Block(0, 0),
		Block(1, 0),
		Block(1, 1),
		Block(0, 1)
		},
		{
		Block(0, 0),
		Block(1, 0),
		Block(1, 1),
		Block(0, 1)
		}
	};
}
