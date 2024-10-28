#pragma once
#include <iostream>

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
    T getValue() const {
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

    // Setter for the next node
    void setNext(Node* nextNode) {
        next = nextNode;
    }

    // Append a new node to the end of the list
    void append(Node* newNode) {
        Node* current = this;
        while (current->next != &NIL) {
            current = current->next;
        }
        current->next = newNode;
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
