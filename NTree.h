#pragma once
#include <stdexcept>

template <class T, int N>
class NTree
{
private:
	T fKey;
	int size;
	NTree<T, N>* fNodes[N];
	NTree() {
		size = 0;
		fKey = (T)0;
		for (int x = 0; x < N; x++) {
			fNodes[x] = &NIL;
		}
	};
public:
	static NTree<T, N> NIL;
	NTree(const T& pKey) {
		size = 1;
		fKey = pKey;
		for (int x = 0; x < N; x++) {
			fNodes[x] = &NIL;
		}
	}
	~NTree() {
		for (int x = 0; x < N; x++) {
			if (fNodes[x] != &NIL) {  // Only delete if it's not NIL
				delete fNodes[x];  // Free dynamically allocated child nodes
			}
		}
	}

	bool isEmpty() const {
		return this == &NIL;
	}
	const T& getKey() const {
		if (isEmpty()) {
			throw std::domain_error("Empty NTree!");
		}
		return fKey;
	}
	void attachNTree(int aIndex, NTree<T, N>* aNTree) {
		if (isEmpty()) {
			throw std::domain_error("Empty NTree!");
		}
		if ((aIndex >= 0) && (aIndex < N)) {
			if (fNodes[aIndex] != &NIL) {
				throw std::domain_error("Non-empty subtree present!");
			}
			fNodes[aIndex] = aNTree;
			size++;
		}
		else {
			throw std::domain_error("Illegal subtree index!");
		}
	}
	NTree& operator[](int aIndex) const {
		if (isEmpty()) {
			throw std::domain_error("Empty NTree!");
		}
		if ((aIndex >= 0) && (aIndex < N)) {
			return *fNodes[aIndex];
		}
		else {
			throw std::domain_error("Illegal subtree index!");
		}
	}

	NTree& detachNTree(int aIndex) {
		if (isEmpty()) {
			throw std::domain_error("Empty NTree!");
		}
		if ((aIndex >= 0) && (aIndex < N)) {
			NTree<T, N>* Result = fNodes[aIndex];
			fNodes[aIndex] = &NIL;
			size--;
			return  Result;
		}
		else {
			throw std::domain_error("Illegal subtree index!");
		}
	}

	int getSize() const {
		return size;
	}

	NTree<T, N>* search(const T& key) const {
		if (isEmpty()) {
			throw std::domain_error("Empty NTree!");
		}
		for (int x = 0; x < N; x++) {
			if (fNodes[x] != &NIL) {
				if (fNodes[x]->getKey() == key) {
					return fNodes[x];
				}
			}
		}
		return &NIL;
	}
};

template <class T, int N>
NTree<T, N> NTree<T, N>::NIL;