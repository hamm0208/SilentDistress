#pragma once
#include <iostream>
using namespace std;
template <typename T>
class SinglyLinkedNode {
public:
    typedef SinglyLinkedNode<T> Node;
    static Node NIL;  // Static sentinel node
private:
    T value;                     // Value held by the node
    Node* next;              // Pointer to the next node

public:
    // Default constructor
    SinglyLinkedNode() : value(T()), next(&NIL) {}  // Initialize to NIL

    // Constructor with value
    SinglyLinkedNode(const T& value) : value(value), next(&NIL) {}

    // Getter for value
    T& getValue() {
        return value;
    }

    // Setter for value
    void setValue(const T& newValue) {
        value = newValue;
    }

    // Getter for the next node
    Node* getNext() const {
        return next;
    }

    // Append a new node to the this
    void append(Node* newNode) {
        if(next != &NIL){
            newNode->next = this->next;
        }
        this->next = newNode;
    }

    // Remove the next node
    void removeNext() {
        if (next != &NIL) {
            Node* temp = next; // Node to be removed
            next = next->next; // Bypass the node
            delete temp; // Free memory
        }
    }
};

// Define the static NIL node
template <typename T>
typename SinglyLinkedNode<T>::Node SinglyLinkedNode<T>::NIL;
