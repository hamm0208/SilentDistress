#pragma once
#include <stdexcept>
using namespace std;

// Template class for a Binary Tree (BTree)
template <class T>
class BTree {
public:
	// Static NIL node to represent empty trees or subtrees
	static BTree<T> NIL;
private:
	// Pointer to the key of the node
	T* fKey;
	// Pointers to the left and right children
	BTree<T>* fLeft;
	BTree<T>* fRight;
public:
	// Default constructor: Initializes an empty node
	BTree() : fKey() {
		// Allocates memory for the key
		fKey = new T();
		// Sets left and right children to NIL
		fLeft = &NIL;
		fRight = &NIL;
	}

	// Constructor that initializes the node with a given key
	BTree(const T& aKey) {
		// Allocates memory for the key and assigns it
		fKey = new T(aKey);
		// Sets left and right children to NIL
		fLeft = &NIL;
		fRight = &NIL;
	}

	// Destructor to clean up allocated memory
	~BTree() {
		// Deletes the key if it's not nullptr
		if (fKey != nullptr) {
			delete fKey;
		}
		// Deletes left and right subtrees if they are not NIL
		if (fLeft != &NIL) {
			delete fLeft;
		}
		if (fRight != &NIL) {
			delete fRight;
		}
	}

	// Checks if the current node is empty (i.e., if it is NIL)
	bool isEmpty() const {
		return this == &NIL;
	}

	// Returns the key of the current node
	const T& key() const {
		// Throws an error if trying to access the key of an empty node
		if (isEmpty()) {
			throw domain_error("Empty node!");
		}
		return *fKey;
	}

	// Sets the key of the current node
	void setKey(const T& k) {
		*fKey = k;
	}

	// Returns the left child of the current node
	BTree& left() const {
		return *fLeft;
	}

	// Returns the right child of the current node
	BTree& right() const {
		return *fRight;
	}

	// Attaches a subtree as the left child of the current node
	void attachLeft(BTree<T>* aBTree) {
		// Throws an error if the current node is empty
		if (isEmpty()) {
			throw domain_error("Empty BTree");
		}
		// Throws an error if the left child is not empty
		if (fLeft != &NIL) {
			throw domain_error("Non-empty sub tree");
		}
		fLeft = aBTree;
	}

	// Attaches a subtree as the right child of the current node
	void attachRight(BTree<T>* aBTree) {
		// Throws an error if the current node is empty
		if (isEmpty()) {
			throw domain_error("Empty BTree");
		}
		// Throws an error if the right child is not empty
		if (fRight != &NIL) {
			throw domain_error("Non-empty sub tree");
		}
		fRight = aBTree;
	}

	// Detaches the left child of the current node and returns it
	BTree* detachLeft() {
		// Throws an error if the current node is empty
		if (isEmpty()) {
			throw domain_error("Empty BTree");
		}
		// Stores the left child in Result and sets the left child to NIL
		BTree<T>& Result = *fLeft;
		fLeft = &NIL;
		return &Result;
	}

	// Detaches the right child of the current node and returns it
	BTree* detachRight() {
		// Throws an error if the current node is empty
		if (isEmpty()) {
			throw domain_error("Empty BTree");
		}
		// Stores the right child in Result and sets the right child to NIL
		BTree<T>& Result = *fRight;
		fRight = &NIL;
		return &Result;
	}
};

// Static member initialization for NIL, which represents an empty node
template <class T>
BTree<T> BTree<T>::NIL;
