#pragma once
#include <stdexcept>
using namespace std;

template <class T>
class BTree {
private:
	T* fKey;
	BTree<T>* fLeft;
	BTree<T>* fRight;
public:
	BTree() :fKey() {
		fKey = new T();;
		fLeft = &NIL;
		fRight = &NIL;
	}
	static BTree<T> NIL;
	BTree(const T& aKey){
		fKey = new T(aKey);
		fLeft = &NIL;
		fRight = &NIL;
	}
	~BTree(){
		if (fKey != nullptr) {
			delete fKey;
		}
		if (fLeft != &NIL) {
			delete fLeft;
		}
		if (fRight != &NIL) {
			delete fRight;
		}
	}
	bool  isEmpty() const{
		return this == &NIL;
	}
	const T& key() const{
		if(isEmpty()){
			throw std::domain_error("Empty node!");
		}
		return *fKey;
	}
	void setKey(const T& k) {
		*fKey = k;
	}
	BTree& left() const{
		return *fLeft;
	}
	BTree& right() const{
		return *fRight;
	}
	void attachLeft(BTree<T>* aBTree){
		if (isEmpty()){
			throw std::domain_error("Empty BTree");
		}
		if (fLeft != &NIL){
			throw std::domain_error("Non-empty sub tree");
		}
		fLeft = aBTree;
	}

	void attachRight(BTree<T>* aBTree){
		if (isEmpty()){
			throw std::domain_error("Empty BTree");
		}
		if (fRight  != &NIL){
			throw std::domain_error("Non-empty sub tree");
		}
		fRight  = aBTree;
	}

	BTree* detachLeft(){
		if(isEmpty()){
			throw std::domain_error("Empty BTree");
		}
		BTree<T>& Result = *fLeft;
		fLeft = &NIL;
		return &Result;
	}

	BTree* detachRight(){
		if(isEmpty()){
			throw std::domain_error("Empty BTree");
		}
		BTree<T>& Result = *fRight;
		fRight = &NIL;
		return &Result;
	}
};

template <class T>
BTree<T> BTree<T>::NIL;