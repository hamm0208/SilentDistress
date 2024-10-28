#pragma once
#include "SinglyLinkedNodeIterator.h"

template <class T>
class SinglyLinkedList{
    private:
        typedef SinglyLinkedNode<T> Node;
        Node* last;
		Node* head;
		int count;
    public:
		typedef SinglyLinkedNodeIterator<T> Iterator;
		SinglyLinkedList() : last(&(Node::NIL)), head(&(Node::NIL)), count(0) {}; //Empty list, head and tail points to the sentinel node
		SinglyLinkedList(Node* firstNode) : last(firstNode), head(firstNode), count(1) {}; //List initailise with 1 Node, Head and tail points to the node, count is now 1

        //Destructor
        ~SinglyLinkedList(){
			Iterator it = getIteratorHead();
            while (it != it.end()) {
				Node* toDelete = it.getCurrent();
				++it;
                delete toDelete;
			}
        }
        
        //Push an element from the front of the list
		void pushFront(const T& value) {
            Node* newNode = new Node(value);
            newNode->next = head;
            head = newNode;
            if (count == 0) {
                last = newNode;
            }
            ++count;
		}

        //Push an element from the back of the list
		void pushBack(const T& value) {
			Node* newNode = new Node(value);
			if (last == &(Node::NIL)) { // If the list is empty
				head = newNode;
			}else {
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
                delete toDelete;
				--count;
				if (count == 0) {
					head = &(Node::NIL);
					last = &(Node::NIL);
				}
				return value;
			}
			cout << "Error: List is empty, Unable  to pop front" << endl;
			exit(0);
		}

        //Pop the element from the back
		T popBack() {
			if (last != &(Node::NIL)) {                     //If list is not empty
				T value = last->getValue();                 //Value of the last node
                Node* toDelete = last;                      //Node to delete
                if(head == last){                           //If there's only 1 node in the list
                    delete toDelete;
                    head = &(Node::NIL);
                    last = &(Node::NIL);
                }else{
                    Node* ptr = head;                       
                    while (ptr->getNext() != last) {        //If ptr's next points to the last node, then that is the new last node
                        ptr = ptr->getNext();
                    }
                    delete toDelete;                       //Delete last node
                    last = ptr;                            //the new last node is now the ptr
                    last->next = &(Node::NIL);             //Reassign the last's next node points to the sentinel node
                }
                --count;
				return value;                               // Return the value.
			}
			exit(0);
		}

        //Overload operator [] so can be used to find the selected element using the index
		T& operator[](int pIndex){
			if (pIndex >= count || pIndex < 0) {            //If pIndex is more than the list's count or below 0, then...
				cout << "Error: List index out of bound";   //show an error
        		exit(0);                                    //End the program
			}
			return findAt(pIndex)->getValue();              //.findAt() will return a Node* which can be used to access the getValue();
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
        
        //Check if the list is empty
		bool isEmpty() const{
			return count == 0;
		}

        //Return the total size of the list
		int size() const {
			return count;
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