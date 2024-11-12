#pragma once
#include "List.h"

template<class T>
class Queue {
private:
    List<T> fQueue;  // List to store elements in the queue
    int fMax;        // Maximum size of the queue

public:
    typedef DoublyLinkedNodeIterator<T> Iterator;  // Iterator for traversing the list

    Queue(int pMax) : fMax(pMax) {}  // Constructor to initialize max size
    ~Queue() {}  // Default destructor

    // Enqueue an element to the back of the queue if space is available
    bool queue(T pValue) {
        if (fQueue.size() < fMax) {
            fQueue.pushBack(pValue);
            return true;
        } else {
            return false;  // Queue is full
        }
    }

    // Dequeue an element from the front of the queue
    T dequeue() {
        if (fQueue.size() > 0) {
            T temp = fQueue.popFront();
            return temp;
        }
        // If queue is empty, output a message and exit
        cout << "List is empty" << endl;
        exit(0);
    }

    // Check if the queue is empty
    bool IsEmpty() const {
        return fQueue.size() == 0;
    }

    // Get the current size of the queue
    int GetSize() const {
        return fQueue.size();
    }

    // Get the maximum capacity of the queue
    int getMax() const {
        return fMax;
    }

    // View the contents of the queue
    void View() const {
        for (Iterator iter = fQueue.getIteratorHead(); iter != iter.end(); ++iter) {
            cout << *iter;
            if (iter != fQueue.getIteratorLast()) {
                cout << ", ";
            }
        }
        cout << endl;
    }

    // Overload operator[] to access element at index
    T& operator[](int pIndex) {
        if (pIndex >= fQueue.size() || pIndex < 0) {
            cout << "Error: List index out of bound";
            exit(0);
        }
        return fQueue.findAt(pIndex)->getValue();  // Access value at specific index
    }

    // Remove element at specified index
    T RemoveAt(int pIndex) {
        if (pIndex >= fQueue.size() || pIndex < 0) {
            cout << "Error: List index out of bound";
            exit(0);
        }
        return fQueue.popAt(pIndex);  // Remove element at index and return its value
    }
};
