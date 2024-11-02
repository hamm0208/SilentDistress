#include <iostream>
using namespace std;
#pragma once

template<class DataType>
class DoublyLinkedNode
{
public:
	typedef DoublyLinkedNode<DataType> Node;
	static Node NIL; //Static = Don't copy this, only one instance in system memory
private:
	DataType value;
	Node* next;
	Node* previous;
public:
	DoublyLinkedNode() {
		value = DataType();
		next = &NIL; //Point to memory location of NIL
		previous = &NIL; //Point to memory location of NIL
	}
	DoublyLinkedNode(const DataType& aValue) {
		value = aValue;
		next = &NIL;
		previous = &NIL;
	}
	void prepend(Node* newNode) {
		newNode->next = this;
		if (this->previous != &NIL) {
			newNode->previous = this->previous;
			this->previous->next = newNode;
		}
		this->previous = newNode;
	}
	void append(Node* newNode) {
		newNode->previous = this;
		if (this->next != &NIL) {
			newNode->next = this->next;
			this->next->previous = newNode;
		}
		this->next = newNode;
	}
	void remove() {
		if (this->previous != &NIL) {
			this->previous->next = this->next;
		}
		if (this->next != &NIL) {
			this->next->previous = this->previous;
		}
		delete this;
	}
	DataType& getValue() {
		return value;
	}
	Node* getNext() const {
		return next;
	}
	Node* getPrevious() const {
		return previous;
	}
};

template<class DataType>
DoublyLinkedNode<DataType> DoublyLinkedNode<DataType>::NIL;