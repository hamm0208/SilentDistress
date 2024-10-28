#include <iostream>
#include "SinglyLinkedList.h"
using namespace std;

int main() {
	SinglyLinkedList<int> myList;
	myList.pushBack(1);
	myList.pushBack(2);
	myList.pushBack(3);
	myList.pushBack(4);

	cout << myList.popBack() << endl;
	cout << myList.popBack() << endl;
	cout << myList.popBack() << endl;
	cout << myList.popBack() << endl;
	

	return 0;
}