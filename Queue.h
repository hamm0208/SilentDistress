#pragma once
#include "List.h"

template<class T>
class Queue{
    private:
        List<T> fQueue;
        int fMax;
    public:
		typedef DoublyLinkedNodeIterator<T> Iterator;
        Queue(int pMax):fMax(pMax){};
        ~Queue(){};
        bool queue(T pValue){
            if(fQueue.size()  < fMax){
				fQueue.pushBack(pValue);
				return true;
			}else{
				return false;
			}
        }
        T dequeue(){
			if(fQueue.size() > 0){
				T temp = fQueue.popFront();
				return temp;
			}
			cout << "List is empty" << endl;
			exit(0);
		}
		bool IsEmpty() {
			return fQueue.size() == 0;
		}
		int GetSize() {
			return fQueue.size();
		}
		int getMax() {
			return fMax;
		};
		void View() {
			for (Iterator iter = fQueue.getIteratorHead(); iter != iter.end(); ++iter) {
				cout << *iter;
				if (iter != fQueue.getIteratorLast()) {
					cout << ", ";
				}
			}
			cout << endl;
		}
		T& operator[](int pIndex) {
			if (pIndex >= fMax || pIndex < 0) {
				cout << "Error: List index out of bound";
				exit(0);
			}
			return fQueue.findAt(pIndex)->getValue(); //.findAt() will return a Node* which can be used to access the getValue();
		}
		T RemoveAt(int pIndex) {
			if (pIndex >= fMax || pIndex < 0) {
				cout << "Error: List index out of bound";
				exit(0);
			}
			return fQueue.popAt(pIndex);
		}
};