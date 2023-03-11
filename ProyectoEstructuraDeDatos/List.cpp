#include <iostream>
#include "MainWindow.h"
using namespace std;

List::List() {
	this->first = nullptr;
}

List::~List() {}

void List::insertNode(int newValue) {
    Node* newNode = new Node(newValue);
    if (this->first == nullptr) {
        this->first = newNode;
        return;
    }
    else {
        Node* iteratorNode = this->first;
        while (iteratorNode->next != nullptr) {
            iteratorNode = iteratorNode->next;
        }
        iteratorNode->next = newNode;
    }
}

void List::printList() {
	Node* iteratorNode = this->first;
	while (iteratorNode != nullptr) {
		ui.combo_eliminar->addItem("hola");
		iteratorNode = iteratorNode->next;
	}
}

int List::size() {
	int i = 0;
	Node* iteratorNode = this->first;
	while (iteratorNode != nullptr) {
		i++;
		iteratorNode = iteratorNode->next;
	}
	return i;
}

int List::valueAt(int index) {
	Node* iteratorNode = this->first;
	for (int i = 0; i <= index; i++) {
		if (i == index) {
			return iteratorNode->value;
		}
		else {
			iteratorNode = iteratorNode->next;
		}
	}
}

bool List::contains(int value) {
    bool exists = false;
    if (this->first->value == value) {
        exists = true;
    }
    Node* iteratorNode = this->first;
    while (iteratorNode->next != nullptr) {
        if (iteratorNode->next->value == value) {
            exists = true;
            break;
        }
        iteratorNode = iteratorNode->next;
    }
    if (exists) {
        return true;
    }
    else {
        return false;
    }
}

bool List::deleteNode(int valueToDelete)
{
    // caso base, si es el primer nodo de la lista o el unico que queda en la lista
    bool isDeleteComplete = false;
    if (this->first->value == valueToDelete) {
        this->first = this->first->next;
        isDeleteComplete = true;
    }
    else {
        // case 2: borrar cualquier elemento de enmedio de la lista
        Node* iteratorNode = this->first;
        while (iteratorNode->next != nullptr) {
            if (iteratorNode->next->value == valueToDelete) {
                iteratorNode->next = iteratorNode->next->next;
                isDeleteComplete = true;
                break;
            }
            iteratorNode = iteratorNode->next;
        }
    }
    
    if (isDeleteComplete) {
        cout << "true\n";
    }
    else {
        cout << "false\n";
    }
    return isDeleteComplete;
}

