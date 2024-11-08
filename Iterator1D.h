template <typename T>
class Iterator1D
{
private:
    const T* fArray; // the array
    const int fLength; // the length of the array
    int fIndex; // current index of the array

public:
    Iterator1D(const T* pArray, const int fLength, int start = 0)
        : fArray(pArray), fLength(fLength), fIndex(start) {} // Constructor of Iterator1D

    // * operator to return the value of the array index
    const T& operator*() const {
        return fArray[fIndex];
    }

    // ++ operator to move on to the next index and return the value after moving forward
    Iterator1D& operator++() {
        ++fIndex;
        return *this;
    }

    // ++ int operator to move on to the next index and return the value before moving forward
    Iterator1D operator++(int) {
        Iterator1D temp = *this;
        ++fIndex;
        return temp;
    }

    // -- operator to move on to the previous index and return the value after moving backwards
    Iterator1D& operator--() {
        --fIndex;
        return *this;
    }

    // -- int operator to move on to the previous index and return the value before moving backwards
    Iterator1D operator--(int) {
        Iterator1D temp = *this;
        --fIndex;
        return temp;
    }

    // == operator to check if 2 Iterator1D objects are equal
    bool operator==(const Iterator1D& aOther) const {
        return fIndex == aOther.fIndex;
    }

    // != operator to check if 2 Iterator1D objects are not equal
    bool operator!=(const Iterator1D& aOther) const {
        return fIndex != aOther.fIndex;
    }

    // Return Iterator1D object that contains the first element of the array
    Iterator1D begin() const {
        return Iterator1D(fArray, fLength, 0);
    }

    // Return Iterator1D object to show that it's at the end of the array
    Iterator1D end() const {
        return Iterator1D(fArray, fLength, fLength); // end points one past the last element
    }

    // Return Iterator1D object that contains the last element of the array
    Iterator1D getLastElement() const {
        return Iterator1D(fArray, fLength, fLength - 1);
    }
};
