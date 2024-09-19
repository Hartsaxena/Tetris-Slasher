#include "Blocks.hpp"


void RotationalStateList::push(RotationalState rotationalState) {
	RotationalStateNode* newNode = new RotationalStateNode(&rotationalState);
	if (this->head == nullptr) {
		this->head = newNode;
		this->head->next = newNode;
		this->tail = newNode;
		this->curr = this->head;
		return;
	}

	newNode->next = this->head;
	this->tail->next = newNode;
	this->head = newNode;
}

IBlock::IBlock() {

}

OBlock::OBlock() {

}

SBlock::SBlock() {

}

ZBlock::ZBlock() {

}

LBlock::LBlock() {

}

TBlock::TBlock() {

}

JBlock::JBlock() {

}