#include "DoublyLinkedNode.h"
#pragma once

template<class DataType>
class DoublyLinkedNodeIterator
{
	private:
		typedef DoublyLinkedNode<DataType> Node;
		Node* current; // Pointer to the current node
	public:
		DoublyLinkedNodeIterator(Node* start) : current(start) {}
		DoublyLinkedNodeIterator(Node& node) : current(	&node) {} //Pass in the original 

		// Prefix increment operator: Moves iterator to the next node
		DoublyLinkedNodeIterator& operator++() {
			current = current->getNext();
			return *this;
		}

		// Postfix increment operator: Moves iterator to the next node, returns old position
		DoublyLinkedNodeIterator& operator++(int) {
			DoublyLinkedNodeIterator& temp = *this;
			++(*this);
			return temp;
		}

		// Prefix decrement operator: Moves iterator to the previous node
		DoublyLinkedNodeIterator& operator--() {
			current = current->getPrevious();
			return *this;
		}

		// Postfix decrement operator: Moves iterator to the previous node, returns old position
		DoublyLinkedNodeIterator& operator--(int) {
			DoublyLinkedNodeIterator& temp = *this;
			--(*this);
			return temp;
		}

		// Equality operator: Checks if two iterators point to the same node
		bool operator==(const DoublyLinkedNodeIterator& other) const {
			return current == other.current;
		}

		// Inequality operator: Checks if two iterators do not point to the same node
		bool operator!=(const DoublyLinkedNodeIterator& other) const {
			return current != other.current;
		}

		// Dereference operator: Returns a reference to the data value of the current node
		DataType& operator*() const {
			return current->getValue();
		}

		// Getter for current node pointer
		Node* getCurrent() {
			return current;
		}

		// Begin method: Returns an iterator pointing to the current node (start of iteration)
		DoublyLinkedNodeIterator begin() {
			return DoublyLinkedNodeIterator(current);
		}

		// End method: Returns an iterator representing the end of the list
		DoublyLinkedNodeIterator end() {
			return DoublyLinkedNodeIterator(Node::NIL);  // Assuming NIL is a static member indicating end
		}
};