#include "Blocks.hpp"
#include <iostream>

/* Get the value of a specific cell(row, col) in the 4x4 grid */
bool RotationalStates::getCell(RotationalState state, int row, int col) {
	int index = 15 - (row * 4 + col); // Calculate inverted bit index (0-15)
	return (state >> index) & 1; // Shift right and mask the bit
}

/* Set a specific cell in the 4x4 grid(1 = filled, 0 = empty) */
void RotationalStates::setCell(RotationalState* state, int row, int col, bool value) {
	int index = 15 - (row * 4 + col);   
	if (value)
		*state |= (1 << index); // Set the bit to 1
	else
		*state &= ~(1 << index); // Set the bit to 0
}

void RotationalStateList::push(RotationalState rotationalState) {
	RotationalStateNode* newNode = new RotationalStateNode(&rotationalState);
	if (this->head == nullptr) {
		head = tail = curr = newNode;
		tail->next = head;

		return;
	}

	newNode->next = this->head; // New node points to the head
	this->tail->next = newNode; // Old tail points to the new node
	this->tail = newNode;       // Update the tail to be the new node
}

void RotationalStateList::debugNodes() {
	std::cout << "RotationalStateList debugNode output:\n";
	RotationalStateNode* currNode = this->head;
	do {
		std::cout << currNode->data << " ";
		currNode = currNode->next;
	} while (currNode != this->head);
	std::cout << "\nCurrent Node: "<<this->curr->data<<"\n";
}

Block::Block(BlockType type) : type(type) {
	switch (type) {
	case I_BLOCK: {
		this->rotationalStates = RotationalStateList(
			RotationalStates::IBlock1,
			RotationalStates::IBlock2,
			RotationalStates::IBlock3,
			RotationalStates::IBlock4
		);
		break;
	}
	case O_BLOCK: {
		this->rotationalStates = RotationalStateList(
			RotationalStates::OBlock1
		);
		break;
	}
	case S_BLOCK: {
		this->rotationalStates = RotationalStateList(
			RotationalStates::SBlock1,
			RotationalStates::SBlock2,
			RotationalStates::SBlock3,
			RotationalStates::SBlock4
		);
		break;
	}
	case Z_BLOCK: {
		this->rotationalStates = RotationalStateList(
			RotationalStates::ZBlock1,
			RotationalStates::ZBlock2,
			RotationalStates::ZBlock3,
			RotationalStates::ZBlock4
		);
		break;
	}
	case L_BLOCK: {
		this->rotationalStates = RotationalStateList(
			RotationalStates::LBlock1,
			RotationalStates::LBlock2,
			RotationalStates::LBlock3,
			RotationalStates::LBlock4
		);
		break;
	}
	case T_BLOCK: {
		this->rotationalStates = RotationalStateList(
			RotationalStates::TBlock1,
			RotationalStates::TBlock2,
			RotationalStates::TBlock3,
			RotationalStates::TBlock4
		);
		break;
	}
	case J_BLOCK: {
		this->rotationalStates = RotationalStateList(
			RotationalStates::JBlock1,
			RotationalStates::JBlock2,
			RotationalStates::JBlock3,
			RotationalStates::JBlock4
		);
		break;
	}
	default: break;
	}
}