#include "MainWindow.h"
Stack::Stack() {
	this->size = 0;
	this->head = nullptr;
	this->tail = nullptr;
}

Stack::~Stack() {

}

void Stack::push(int newValue) {
	this->incrementSize();
	Node* newNode = new Node(newValue);
	// caso base : no hay elementos en la cola
	if (this->tail == nullptr) {
		this->tail = newNode;
		return;
	}
	// caso 2 : si hay elementos en la lista
	newNode->next = this->tail;
	this->tail = newNode;
}

int Stack::pop() {
	if (this->size == 0) {
		return 0;
	}
	if (this->size == 1) {
		int valuetoReturn = this->tail->value;
		this->tail = nullptr;
		this->head = nullptr;
		this->decrementSize();
		return valuetoReturn;
	}
	int valueToReturn = tail->value;;
	this->tail = this->tail->next;
	this->decrementSize();
	return valueToReturn;
}

int Stack::print(int index) {
	Node* iteratorNode = this->tail;
	for (int i = 0; i <= index; i++) {
		if (i == index) {
			return iteratorNode->value;
		}
		else {
			iteratorNode = iteratorNode->next;
		}
	}
}

int Stack::getSize() {
	return this->size;
}

void Stack::incrementSize() {
	this->size = this->size + 1;
}

void Stack::decrementSize() {
	this->size = this->size - 1;
}