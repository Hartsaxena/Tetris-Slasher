#include "Blocks.hpp"

Piece::Piece(int x, int y, PieceType type) {

	this->x = x;
	this->y = y;

	// Lambda function for copying block array to piece
	auto setRotateStates = [this](const RotationalState(&states)[4]) {
		for (int i = 0; i < 4; ++i) {
			this->rotateStates[i] = states[i];
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
}

void Rotations::castBlock(Block* block, int x, int y) {
	block->x += x;
	block->y += y;
}