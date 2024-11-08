#pragma once
#include "List.h"
template<class T>
class Stack
{
	private:
		List<T> fStack;
		int fMax;
	public:
		typedef DoublyLinkedNodeIterator<T> Iterator;
		Stack(int pMax): fMax(pMax){};
		~Stack(){};
		void Push(T pValue){
			if(fStack.size()  < fMax){
				fStack.pushBack(pValue);
			}else{
				cout<<"Stack is full"<<endl;
			}
		}
		T Pop(){
			if(fStack.size() > 0){
				T temp = fStack.popBack();
				return temp;
			}
			exit(0);
		}
		void View(){
			for(Iterator iter = fStack.getIteratorLast(); iter != iter.end(); --iter){
				cout << *iter;
				if (iter != fStack.getIteratorLast()) {
					cout << ", ";
				}
			}
			cout << endl;
		}
		int getMax() {
			return fMax;
		};

		bool IsEmpty() {
			return GetSize() == 0;
		}
		int GetSize() {
			return fStack.size();
		}
		//Return a reference to T, so it can be modify if needed
		T& operator[](int pIndex){
			if (pIndex >= fMax || pIndex < 0) {
				cout << "Error: List index out of bound";
        		exit(0);
			}
			return fStack.findAt(pIndex)->getValue(); //.findAt() will return a Node* which can be used to access the getValue();
		}
		T RemoveAt(int pIndex) {
			if (pIndex >= fMax || pIndex < 0) {
				cout << "Error: List index out of bound";
				exit(0);
			}
			return fStack.popAt(pIndex);
		}
};


