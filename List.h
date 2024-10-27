#include "DoublyLinkedNode.h"
#include "DoublyLinkedNodeIterator.h"
#pragma once

template<class T>
class List
{
	private:
		typedef DoublyLinkedNode<T> Node;
		Node* last;
		Node* head;
		int count;
	public:
		typedef DoublyLinkedNodeIterator<T> Iterator;

		List() : last(&(Node::NIL)), head(&(Node::NIL)), count(0) {};
		List(Node* firstNode) : last(firstNode), head(firstNode), count(1) {};

		~List() {
			Iterator it = getIteratorLast();
			while (it != it.end()) {
				Node* toDelete = it.getCurrent();
				--it;
				toDelete->remove();
			}
		}
		bool isEmpty() const{
			return count == 0;
		}
		int size() const {
			return count;
		}
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
		Iterator getIteratorLast() const {
			return Iterator(last);
		}
		Iterator getIteratorHead() const {
			return Iterator(head);
		}
};

