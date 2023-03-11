#include "MainWindow.h"
Queue::Queue() {
	this->size = 0;
	this->head = nullptr;
	this->tail = nullptr;
}

Queue::~Queue() {

}

void Queue::enqueue(int newValue) {
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

int Queue::dequeue()
{
    if (this->getSize() == 0) {
        return 0;
    }
    else if (this->getSize() == 1) {
        int valueToReturn = this->tail->value;
        this->tail = nullptr;
        this->head = nullptr;
        this->decrementSize();
        return valueToReturn;
    }

    Node* iteratorNode = this->tail;
    int valueToReturn = 0;
    while (iteratorNode->next != nullptr) {
        // avanzar el apuntador
        if (iteratorNode->next->next == nullptr) {
            // estoy en el penultimo
            valueToReturn = iteratorNode->next->value;
            iteratorNode->next = iteratorNode->next->next;
            // iteratorNode->next = nullptr;
            // linea 111 y 112 son lo mismo

            this->head = iteratorNode;
            break;
        }
        iteratorNode = iteratorNode->next;
    }
    this->decrementSize();
    return valueToReturn;
}

void Queue::incrementSize() {
	this->size = this->size + 1;
}
void Queue::decrementSize() {
    this->size = this->size - 1;
}
int Queue::getSize()
{
	return this->size;
}

int Queue::print(int index)
{
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

bool Queue::contains(int value) {
    bool exists = false;
    if (this->tail->value == value) {
        exists = true;
    }
    Node* iteratorNode = this->tail;
    while (iteratorNode->next != nullptr) {
        if (iteratorNode->next->value == value) {
            exists = true;
            break;
        } 
        iteratorNode = iteratorNode->next;
    }
    if (exists)
        return true;
    else
        return false;
}