#pragma once

enum BlockType {
	I_BLOCK,
	O_BLOCK,
	S_BLOCK,
	Z_BLOCK,
	L_BLOCK,
	T_BLOCK,
	J_BLOCK,
};

class RotationalState {
public:

private:
};

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
		(this->push(States), ...);
	}

	void push(RotationalState rotationalState);
	RotationalState getCurr() const { return this->curr->data; }
	void cycleCurr() { this->curr = this->curr->next; }

private:
	RotationalStateNode* head = nullptr;
	RotationalStateNode* tail = nullptr;
	RotationalStateNode* curr = nullptr;
};

class Block {
public:
	void rotate() { this->rotationalStates.cycleCurr(); }

protected:
	RotationalStateList rotationalStates;
};

class IBlock : public Block {
public:
	IBlock();

private:

};

class OBlock : public Block {
public:
	OBlock();

private:

};

class SBlock : public Block {
public:
	SBlock();

private:

};

class ZBlock : public Block {
public:
	ZBlock();

private:

};

class LBlock : public Block {
public:
	LBlock();

private:

};

class TBlock : public Block {
public:
	TBlock();

private:

};

class JBlock : public Block {
public:
	JBlock();

private:

};