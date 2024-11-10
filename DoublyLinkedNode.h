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
	DataType value;	//Value in the node
	Node* next;		//Next  node's memory address
	Node* previous;	//Previous node's  memory address
public:
	DoublyLinkedNode() {
		value = DataType(); //Call the default constructor of the datatype
		next = &NIL; //Point to memory location of NIL
		previous = &NIL; //Point to memory location of NIL
	}
	DoublyLinkedNode(const DataType& aValue) {
		value = aValue;	//Assign the datatype aValue to value
		next = &NIL;	//next points to  NIL 
		previous = &NIL;//previous points to NIl	
	}

	//Adding behind of this node
	void prepend(Node* newNode) {
		newNode->next = this;  // Set newNode's next to the current node (this).

		if (this->previous != &NIL) {  // If current node has a previous node.
			newNode->previous = this->previous;  // Link newNode's previous to current node's previous.
			this->previous->next = newNode;  // Link previous node's next to newNode.
		}
		this->previous = newNode;  // Link current node's previous to newNode.
	}

	//Adding infront of this node
	void append(Node* newNode) {
		newNode->previous = this;
		if (this->next != &NIL) {  // If current node has a next node.
		newNode->next = this->next;  // Link newNode's next to current node's next.
		this->next->previous = newNode;  // Link next node's previous to newNode.
		}
		this->next = newNode;  // Link current node's next to newNode.
	}

	//Remove this node
	void remove() {
		if (this->previous != &NIL) {  // If current node has a previous node.
		this->previous->next = this->next;  // Link previous node's next to current node's next.
		}

		if (this->next != &NIL) {  // If current node has a next node.
			this->next->previous = this->previous;  // Link next node's previous to current node's previous.
		}
		delete this;  // Delete the current node to free memory.
	}

	//Getter for value
	DataType& getValue() {
		return value;
	}
	
	//Getter for next
	Node* getNext() const {
		return next;
	}
	
	//Getter for value
	Node* getPrevious() const {
		return next;
	}
};

template<class DataType>
DoublyLinkedNode<DataType> DoublyLinkedNode<DataType>::NIL;