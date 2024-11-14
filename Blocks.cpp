#include <vector>
#include "Blocks.hpp"


Piece::Piece(int x, int y, PieceType type) {

	this->x = x;
	this->y = y;

	// Lambda function for copying block array to piece
	auto setRotateStates = [this](const RotationalState(&states)[4]) {
		for (int i = 0; i < 4; ++i) {
			this->rotateStates[i] = Rotations::castRotationalState(&states[i], this->x, this->y);
		}
	};

	switch (type) {
	case I_PIECE: {
		setRotateStates(Rotations::I_STATES);
		break;
	}
	case O_PIECE: {
		setRotateStates(Rotations::O_STATES);
		break;
	}
	case S_PIECE: {
		setRotateStates(Rotations::S_STATES);
		break;
	}
	case Z_PIECE: {
		setRotateStates(Rotations::Z_STATES);
		break;
	}
	case L_PIECE: {
		setRotateStates(Rotations::L_STATES);
		break;
	}
	case T_PIECE: {
		setRotateStates(Rotations::T_STATES);
		break;
	}
	case J_PIECE: {
		setRotateStates(Rotations::J_STATES);
		break;
	}
	default: break;
	}

	this->getCurrentState().blocks[0].x = x;
}

void Piece::rotate() {
	currentRotation = (currentRotation + 1) % 4;
}
void Piece::moveUp() {
	this->y--;
	for (Block& block : this->getCurrentState().blocks) {
		block.y--;
	}
}
void Piece::moveDown() {
	this->y++;
	for (Block& block : this->getCurrentState().blocks) {
		block.y++;
	}
}
void Piece::moveLeft() {
	this->x--;
	for (Block& block : this->getCurrentState().blocks) {
		block.x--;
	}
}
void Piece::moveRight() {
	this->x++;
	for (Block& block : this->getCurrentState().blocks) {
		block.y++;
	}
}

std::vector<Block> Piece::getAbsoluteBlocks() const {
	std::vector<Block> absoluteBlocks;
	for (const Block& block : this->rotateStates[currentRotation].blocks) {
		absoluteBlocks.push_back(Block(block.x + this->x, block.y + this->y));
	}

	return absoluteBlocks;
}

void Rotations::castBlock(Block* block, int x, int y) {
	block->x += x;
	block->y += y;
}

RotationalState Rotations::castRotationalState(const RotationalState* state, int x, int y) {
	RotationalState newState;
	for (int i = 0; i < 4; ++i) {
		newState.blocks[i] = state->blocks[i];
		castBlock(&newState.blocks[i], x, y);
	}

	return newState;
}