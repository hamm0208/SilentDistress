#include <iostream>

#pragma once

class Item;
using namespace std;

class Iterator2D
{
private:
	Item** fItemArray; //the array
	const int fRowsLength; //the num of rows in the 2D Array
	const int fColsLength; //the num of cols in the 2D Array
	int fRowIndex; //current row index of the array
	int fColIndex; //current cols index of the array
public:
	Iterator2D(Item** pItemArray, const int pRowsLength, const int pColsLength, const int startRow = 0, const int  startCol = 0);//Constructor of Iterator2D
	const Item& operator*() const; //* operator to return the value of the array index
	Iterator2D& operator++(); //++ operator to move on to the next index and returning the value after moving forward
	Iterator2D operator++(int); //++ int operator to move on to the next index and returning the value before moving forward
	Iterator2D& operator--(); //-- operator to move on to the previous index and returning the value after moving backwards
	Iterator2D operator--(int); //-- operator to move on to the previous index and returning the value before moving backwards
	bool operator==(const Iterator2D& aOther) const; //== opeartor to check if 2 Iterator1D object are equal
	bool operator!=(const Iterator2D& aOther) const; //!= opeartor to check if 2 Iterator1D object are not equal
	int getCurrentRowIndex();
	int getCurrentColIndex();
	Iterator2D end() const;
};


