#pragma once
#include "List.h"

// Stack class implementation with a maximum size and generic type T
template<class T>
class Stack {
private:
    List<T> fStack;  // List to hold the stack elements
    int fMax;        // Maximum size of the stack

public:
    typedef DoublyLinkedNodeIterator<T> Iterator;  // Define an alias for the iterator type

    // Constructor to initialize the stack with a maximum size
    Stack(int pMax) : fMax(pMax) {}

    // Destructor
    ~Stack() {}

    // Push an element onto the stack
    void Push(T pValue) {
        // Check if there is space left in the stack
        if (fStack.size() < fMax) {
            fStack.pushBack(pValue);  // Add the element to the end of the list
        } else {
            cout << "Stack is full" << endl;  // Print an error message if the stack is full
        }
    }

    // Pop an element from the stack
    T Pop() {
        // Ensure the stack is not empty before popping
        if (fStack.size() > 0) {
            T temp = fStack.popBack();  // Remove the last element of the stack
            return temp;
        }
        exit(0);  // Exit the program if trying to pop from an empty stack
    }

    // View all elements in the stack
    void View() {
        // Iterate through the stack starting from the last element (top of the stack)
        for (Iterator iter = fStack.getIteratorLast(); iter != iter.end(); --iter) {
            cout << *iter;  // Print the current element
            if (iter != fStack.getIteratorLast()) {  // Check if it's not the last element
                cout << ", ";  // Print a separator for the elements
            }
        }
        cout << endl;  // Print a newline after the stack elements
    }

    // Get the maximum size of the stack
    int getMax() {
        return fMax;
    }

    // Check if the stack is empty
    bool IsEmpty() {
        return GetSize() == 0;  // Return true if the size is 0, meaning the stack is empty
    }

    // Get the current size of the stack
    int GetSize() {
        return fStack.size();  // Return the number of elements in the stack
    }

    // Overload the index operator to access elements by index
    T& operator[](int pIndex) {
        // Ensure the index is within valid bounds
        if (pIndex >= fMax || pIndex < 0) {
            cout << "Error: List index out of bound";  // Print an error message for out-of-bounds index
            exit(0);  // Exit the program if index is out of bounds
        }
        return fStack.findAt(pIndex)->getValue();  // Return the element at the specified index
    }

    // Remove an element at a specific index
    T RemoveAt(int pIndex) {
        // Ensure the index is within valid bounds
        if (pIndex >= fMax || pIndex < 0) {
            cout << "Error: List index out of bound";  // Print an error message for out-of-bounds index
            exit(0);  // Exit the program if index is out of bounds
        }
        return fStack.popAt(pIndex);  // Remove the element at the specified index and return it
    }
};