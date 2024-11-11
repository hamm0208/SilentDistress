#pragma once
#include "SinglyLinkedNode.h"
template <class T>
class SinglyLinkedNodeIterator{
    private:
		typedef SinglyLinkedNode<T> Node;
		Node* current;
	public:
		SinglyLinkedNodeIterator(Node* start) : current(start) {} //Default constructor
		SinglyLinkedNodeIterator(Node& node) : current(	&node) {}
        
        //Overload operator for ++  to move on to the next SinglyNode
        SinglyLinkedNodeIterator& operator++() {
			current = current->getNext();
			return *this;
		}
        SinglyLinkedNodeIterator& operator++(int) {
			SinglyLinkedNodeIterator& temp = *this;
			++(*this);
			return *this;
		}

        //Overload == operator to check whether the 2 SinglyLinkedIterator is the same
        bool operator==(const SinglyLinkedNodeIterator& other) const {
			return current == other.current;
		}

        //Overload != operator to check whether the 2 SinglyLinkedIterator is the same
		bool operator!=(const SinglyLinkedNodeIterator& other) const {
			return current != other.current;
		}
        
        //Overload operator * to return the current node's value
        T& operator*() const {
			return current->getValue();
		}

        //Return the current SinglyNode
        Node* getCurrent() {
			return current;
		}
        //Return the current SinglyLinkedNodeIterator 
		SinglyLinkedNodeIterator begin() {
			return SinglyLinkedNodeIterator(current);
		}
        //Return the sentinel node SinglyLinkedIterator
		SinglyLinkedNodeIterator end() {
			return SinglyLinkedNodeIterator(Node::NIL);	
		}
};
