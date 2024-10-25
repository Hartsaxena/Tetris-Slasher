#include "Blocks.hpp"


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