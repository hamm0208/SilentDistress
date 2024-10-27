#include "DoublyLinkedNode.h"
#pragma once

template<class DataType>
class DoublyLinkedNodeIterator
{
	private:
		typedef DoublyLinkedNode<DataType> Node;
		Node* current;
	public:
		DoublyLinkedNodeIterator(Node* start) : current(start) {}
		DoublyLinkedNodeIterator(Node& node) : current(	&node) {} //Pass in the original 

		DoublyLinkedNodeIterator& operator++() {
			current = current->getNext();
			return *this;
		}
		
		DoublyLinkedNodeIterator& operator++(int) {
			DoublyLinkedNodeIterator& temp = *this;
			++(*this);
			return *this;
		}

		DoublyLinkedNodeIterator& operator--() {
			current = current->getPrevious();
			return *this;
		}

		DoublyLinkedNodeIterator& operator--(int) {
			DoublyLinkedNodeIterator& temp = *this;
			--(*this);
			return *this;
		}

		bool operator==(const DoublyLinkedNodeIterator& other) const {
			return current == other.current;
		}
		bool operator!=(const DoublyLinkedNodeIterator& other) const {
			return current != other.current;
		}
		DataType& operator*() const {
			return current->getValue();
		}
		Node* getCurrent() {
			return current;
		}
		DoublyLinkedNodeIterator begin() {
			return DoublyLinkedNodeIterator(current);
		}
		DoublyLinkedNodeIterator end() {
			return DoublyLinkedNodeIterator(Node::NIL);	
		}
};