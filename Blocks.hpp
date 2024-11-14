#pragma once

#include <cstdint>
#include <type_traits>

typedef enum BlockType {
	I_BLOCK,
	O_BLOCK,
	S_BLOCK,
	Z_BLOCK,
	L_BLOCK,
	T_BLOCK,
	J_BLOCK,
} BlockType;


/*
*** A 16-bit integer that represents a 4x4 2D matrix. ***
* Example: the numbers are the indexes of the integer:
* 0 0 0 0
* 1 1 1 0
* 0 1 0 0
* 0 0 0 0
*
* This matrix represents the rotation of a T-block (Specifically t-block 3)
* Convert this matrix to binary (from the top left to the bottom right, like you're reading english):
* 0000 1110 0100 0000
* Convert binary to decimal: 3648
*/

typedef uint16_t RotationalState;
namespace RotationalStates {
	bool getCell(RotationalState state, int row, int col);
	void setCell(RotationalState* state, int row, int col, bool value);

	// Data for rotational states of all pieces.
	const RotationalState IBlock1 = 3840;
	const RotationalState IBlock2 = 8738;
	const RotationalState IBlock3 = 240;
	const RotationalState IBlock4 = 17476;

	const RotationalState OBlock1 = 52224; // The O-Block only has one orientation, but I'll make 4 variables just in case
	const RotationalState OBlock2 = 52224;
	const RotationalState OBlock3 = 52224;
	const RotationalState OBlock4 = 52224;

	const RotationalState SBlock1 = 27648;
	const RotationalState SBlock2 = 17952;
	const RotationalState SBlock3 = 1728;
	const RotationalState SBlock4 = 35904;

	const RotationalState ZBlock1 = 50688;
	const RotationalState ZBlock2 = 9792;
	const RotationalState ZBlock3 = 3168;
	const RotationalState ZBlock4 = 19584;

	const RotationalState LBlock1 = 11776;
	const RotationalState LBlock2 = 17504;
	const RotationalState LBlock3 = 3712;
	const RotationalState LBlock4 = 50240;

	const RotationalState TBlock1 = 19968;
	const RotationalState TBlock2 = 17984;
	const RotationalState TBlock3 = 3648;
	const RotationalState TBlock4 = 19520;

	const RotationalState JBlock1 = 36352;
	const RotationalState JBlock2 = 25664;
	const RotationalState JBlock3 = 3616;
	const RotationalState JBlock4 = 17600;
}

typedef struct RotationalStateNode { // Circular singly-linked list
	explicit RotationalStateNode(RotationalState* data) { this->data = *data; }

	RotationalState data;
	RotationalStateNode* next = nullptr;

} RotationalStateNode;

class RotationalStateList {
public:
	template<typename... States>
	RotationalStateList(States... rotationalStates) {
		static_assert((std::is_same_v<States, RotationalState> && ...),
			"All entries in RotationStateList must be of type RotationalState\n");
		(this->push(rotationalStates), ...);
	}

	void push(RotationalState rotationalState);
	RotationalState getCurr() const { return this->curr->data; }
	void cycleCurr() { this->debugNodes(); this->curr = this->curr->next; }
	void debugNodes();

private:
	RotationalStateNode* head = nullptr;
	RotationalStateNode* tail = nullptr;
	RotationalStateNode* curr = nullptr;
};



class Block {
public:
	Block(BlockType type = T_BLOCK);

	void rotate() {
		RotationalState debugCurr = this->rotationalStates.getCurr();
		this->rotationalStates.cycleCurr();
		debugCurr = this->rotationalStates.getCurr();
	}

	RotationalState getCurrentState() const { return rotationalStates.getCurr(); }

	BlockType getType() const { return type; }

private:
	BlockType type;
	RotationalStateList rotationalStates;

	static RotationalStateList getRotationalStatesForType(BlockType type) {
		switch (type) {
		case I_BLOCK:
			return RotationalStateList(RotationalStates::IBlock1, RotationalStates::IBlock2, RotationalStates::IBlock3, RotationalStates::IBlock4);
		case O_BLOCK:
			return RotationalStateList(RotationalStates::OBlock1, RotationalStates::OBlock2, RotationalStates::OBlock3, RotationalStates::OBlock4);
		case S_BLOCK:
			return RotationalStateList(RotationalStates::SBlock1, RotationalStates::SBlock2, RotationalStates::SBlock3, RotationalStates::SBlock4);
		case Z_BLOCK:
			return RotationalStateList(RotationalStates::ZBlock1, RotationalStates::ZBlock2, RotationalStates::ZBlock3, RotationalStates::ZBlock4);
		case L_BLOCK:
			return RotationalStateList(RotationalStates::LBlock1, RotationalStates::LBlock2, RotationalStates::LBlock3, RotationalStates::LBlock4);
		case T_BLOCK:
			return RotationalStateList(RotationalStates::TBlock1, RotationalStates::TBlock2, RotationalStates::TBlock3, RotationalStates::TBlock4);
		case J_BLOCK:
			return RotationalStateList(RotationalStates::JBlock1, RotationalStates::JBlock2, RotationalStates::JBlock3, RotationalStates::JBlock4);
		default:
			return RotationalStateList(RotationalStates::TBlock1);
		}
	}
};
