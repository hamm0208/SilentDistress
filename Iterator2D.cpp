#include "Iterator2D.h"
#include "Item.h"

//Consturctor to dimensionalise the Class's attributes
Iterator2D::Iterator2D(Item** pItemArray, const int pRowsLength, const int pColsLength, int startRow, int startCol):fItemArray(pItemArray), fRowsLength(pRowsLength), fColsLength(pColsLength) {
	fRowIndex = startRow;
	fColIndex = startCol;
};

//Returning the current index value of the array
const Item& Iterator2D::operator*() const {
	return fItemArray[fRowIndex][fColIndex];
};

// Pre-increment operator (move forward)
Iterator2D& Iterator2D::operator++() {
	if (fRowIndex == fRowsLength) {
		cout << "Index out of bounds" << endl;
	}
	else if (fColIndex == fColsLength - 1) {
		fRowIndex++;
		fColIndex = 0;
	}
	else {
		fColIndex++;
	}
	return *this;
}


// Post-increment operator (move forward, return original state)
Iterator2D Iterator2D::operator++(int) {
	Iterator2D temp = *this;
	if (fRowIndex == fRowsLength-1 && fColIndex == fColsLength-1) {
		cout << "Index out of bounds" << endl;
	}
	else if (fColIndex == fColsLength - 1) {
		fRowIndex++;
		fColIndex = 0;
	}
	else {
		fColIndex++;
	}
	return temp;
};

// Pre-decrement operator (move backward)
Iterator2D& Iterator2D::operator--() {
	if (fColIndex == 0 && fRowIndex == 0) {
		cout << "Index out of bounds" << endl;
	}
	else {
		if (fColIndex == 0) {
			fColIndex = fColsLength-1;
			fRowIndex--;
		}
		else {
			fColIndex--;
		}
	}
	return *this;
};

// Post-decrement operator (move backward, return original state)
Iterator2D Iterator2D::operator--(int) {
	Iterator2D temp = *this;
	if (fColIndex == 0 && fRowIndex == 0) {
		cout << "Index out of bounds" << endl;
	}
	else {
		if (fColIndex == 0) {
			fColIndex = fColsLength-1;
			fRowIndex--;
		}
		else {
			fColIndex--;
		}
	}
	return temp;
};

//Returning true or false depending if the current class Index is equal to the aOther's findex and current fStringArray is equal to the aOther's fStringArray
bool Iterator2D::operator==(const Iterator2D& aOther) const {
	return (fColIndex == aOther.fColIndex) && (fRowIndex == aOther.fRowIndex) && (fItemArray == aOther.fItemArray);
};

//Returning true or false depending if the current class Index is not equal to the aOther's findex and current fStringArray is equal to the aOther's fStringArray
bool Iterator2D::operator!=(const Iterator2D& aOther) const {
	return !(*this == aOther);
};

//Set the index to the one right after the last one
Iterator2D Iterator2D::end() const {
	return Iterator2D(fItemArray, fRowsLength, fColsLength, fRowsLength, 0);
}

int Iterator2D::getCurrentRowIndex() {
	return fRowIndex;
};
int Iterator2D::getCurrentColIndex() {
	return fColIndex;
};