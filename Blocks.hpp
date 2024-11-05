#pragma once

#include <cstdint>
#include <type_traits>

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
	Block() { x = 0; y = 0; immortal = false; }
	Block(int x, int y, bool immortal = false) { this->x = x; this->y = y; this->immortal = immortal; }

	int x, y;
	bool immortal = false;
};

typedef struct RotationalState {
	Block blocks[4];
} RotationalState;

class Piece {
public:

	int x, y;

	/*
	x = x position of the piece's left-most tile (on the 4x4 available grid)
	y = y position of the same tile
	type = type of block to create
	*/
	Piece(int x, int y, PieceType type = O_PIECE);

	void rotate() { currentRotation = (currentRotation + 1) % 4; }
	RotationalState* getCurrentState() const { return &rotateStates[currentRotation]; }

private:
	int currentRotation = 0;
	RotationalState rotateStates[4];
};


namespace Rotations {
	// Pieces for each rotational state of each block type

	void castBlock(Block* block, int x, int y);

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
		Block(1, 0),
		Block(1, 1),
		Block(1, 2),
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
