#include "DoublyLinkedNode.h"
#include "DoublyLinkedNodeIterator.h"
#pragma once

template<class T>
class List
{
	private:
		typedef DoublyLinkedNode<T> Node;
		Node* last; //last node of the list
		Node* head; //head of the list
		int count; //total size of the list
	public:
		typedef DoublyLinkedNodeIterator<T> Iterator;
		List() : last(&(Node::NIL)), head(&(Node::NIL)), count(0) {}; //Empty list, head and tail points to the sentinel node
		List(Node* firstNode) : last(firstNode), head(firstNode), count(1) {}; //List initailise with 1 Node, Head and tail points to the node, count is now 1

		//Destructor to delete the elements in the list
		~List() {
			Iterator it = getIteratorLast();
			while (it != it.end()) {
				Node* toDelete = it.getCurrent();
				--it;
				toDelete->remove();
			}
		}

		//Check if the list is empty
		bool isEmpty() const{
			return count == 0;
		}

		//Return the total size of the list
		int size() const {
			return count;
		}

		//Push an element from the front of the list
		void pushFront(const T& value) {
			Node* newNode = new Node(value); 
			if (head == &(Node::NIL)) {
				head = newNode;
				last = newNode;
			}
			else {
				head->prepend(newNode);
			}
			head = newNode;
			++count;
		}

		//Push an element from the back of the list
		void pushBack(const T& value) {
			Node* newNode = new Node(value);
			if (last == &(Node::NIL)) { // If the list is empty
				head = newNode;
				last = newNode;
			}
			else {
				last->append(newNode);
			}
			last = newNode;
			++count;
		}

		//Pop the element from the front
		T popFront() {
			if (head != &(Node::NIL)) {
				T value = head->getValue();
				Node* toDelete = head;
				head = head->getNext();
				toDelete->remove();
				--count;
				if (count == 0) {
					head = &(Node::NIL);
					last = &(Node::NIL);
				}
				return value;
			}
			exit(0);
		}

		//Pop the element from the back
		T popBack() { // Change return type to T
			if (last != &(Node::NIL)) {
				T value = last->getValue(); // Move this line after checking last.
				Node* toDelete = last;
				last = last->getPrevious();
				toDelete->remove();
				--count;
				if (count == 0) {
					head = &(Node::NIL);
					last = &(Node::NIL);
				}
				return value; // Return the value.
			}
			exit(0);
		}

		//Pop the element at the selected index
		T popAt(int pIndex) {
			Node* toRemove = findAt(pIndex);
			//If toRemove's next is the sentinel node, it means that its the tail
			if (toRemove->getNext() == &(Node::NIL)) {
				return popBack();
			}
			//If toRemove's previous is the sentinel node, it means that its the head
			if (toRemove->getPrevious() == &(Node::NIL)) {
				return popFront();
			}
			T value = toRemove->getValue();
			toRemove->remove();
			--count;
			return value;
		}

		//Overload operator [] so can be used to find the selected element using the index
		T& operator[](int pIndex){
			if (pIndex >= count || pIndex < 0) { //If pIndex is more than the list's count or below 0, then...
				cout << "Error: List index out of bound"; //show an error
        		exit(0); //End the program
			}
			return findAt(pIndex)->getValue(); //.findAt() will return a Node* which can be used to access the getValue();
		}

		//Return Node* so that the ADTs can access the Node's attributes and methods
		Node* findAt(int pIndex){
			Iterator iter = getIteratorHead();
			int count = 0; 
			for(iter; iter != iter.end(); ++iter){
				if(count == pIndex){
					return iter.getCurrent();
				}
				count++;
			}
			cout << "Index is invalid/empty"  <<endl;
			exit(0);
		}

		//Return the Iterator of the last element
		Iterator getIteratorLast() const {
			return Iterator(last);
		}
		
		//Return the Iterator of the first element
		Iterator getIteratorHead() const {
			return Iterator(head);
		}
};

