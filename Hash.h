#include <iostream>
#include <string>
#include "Item.h"
using namespace std;

//Template HashNode
template <class K, class V>
class HashNode {
private:
    K fKey;     //Key of HashNode
    V fValue;   //Value of HashNode
    HashNode* fNext; //Pointer to next HashNode
public:
    static HashNode<K, V> NIL; //Sentinel HashNode to signify the end of the bucket
    //Default constructor
    HashNode() {
        fNext = &NIL;
        fKey = K();
        fValue = V();
    }
    //Overloaded constructor to assign the key and value into fKey and fValue
    HashNode(K pKey, V pValue) {
        fKey = pKey;
        fValue = pValue;
        fNext = &NIL;
    }
    //Append HashNode 
    void append(HashNode* newNode) {
        if (fNext != &NIL) {
            newNode->fNext = this->fNext;
        }
        this->fNext = newNode;
    }
    //Remove the next HashNode of this object
    void removeNext() {
        if (fNext != &NIL) {
            HashNode* toDelete = this->fNext;
            this->fNext = this->fNext->fNext;
            delete toDelete;
        }
    }
    //Get key
    K getKey() const {
        return fKey;
    }
    //Get value
    V getValue() const {
        return fValue;
    }
    //Get next HashNode
    HashNode* getNext() const {
        return fNext;
    }
    //Set value of Key
    void setValue(V value) {
        fValue = value;
    }
};
//Initialise sentinel HashNode 
template <class K, class V>
HashNode<K, V> HashNode<K, V>::NIL;

//ItemHashTable's HashNode's Key is only for Item class, and template V for the value of the HashNode, because I have to implement the HashKey from scratch T_T
template <class V>
class ItemHashTable{
    public:
        typedef HashNode<Item*, V> HNode;
    private:
        int tableSize;  //Size of table
        HNode** table;  //Array of HNode pointers
    public:
        //Constructor
        ItemHashTable(int pTableSize) : tableSize(pTableSize) {
            table = new HNode* [tableSize]; //Assign table with allocated memory size of pTableSize for HNode*
            for (int i = 0; i < tableSize; ++i) {
                table[i] = &HNode::NIL;  // Initialize each to NIL
            }
        }

        //Hash by name of item
        int hashKey(string pName) {
            int hash = 0;
            for (size_t x = 0; x < pName.length(); x++) {
                hash += static_cast<int>(pName[x]); //Add each of the characters by their ASCII value
            }
            return hash % tableSize; //the index of the table index
        }

        //Insert new item and its value
        void insert(Item* key, V value) {
            int index = hashKey(key->getName()); //Hashing the item and get the index
            if (table[index] == &HNode::NIL) { //If the table's first node is NIL, then...
                table[index] = new HNode(key, value); //Create new HNode with the key value pair and place it in the table
            }
            else { //else..
                HNode* node = new HNode(key, value);
                table[index]->append(node); //Append newNode to the exisiting node at this index
            }
        }

        //Get value by key
        V findValue(Item* key) {
            int index = hashKey(key->getName()); //Get the index of item
            HNode* targetBucket = table[index]; //Get the target bucket
            while (targetBucket != &(HNode::NIL)) { //If target bucket's first item is not NIL...
                if (targetBucket->getKey()->getName() == key->getName()){ //If the key's name is the same as the parameter's key's name
                    return targetBucket->getValue(); // Return the value if key matches
                }
                targetBucket = targetBucket->getNext(); //Move to the next HNode
            }
            return V();
        }
        Item* findKey(Item* key) {
            if (key != nullptr) {
                int index = hashKey(key->getName()); //Get the index of item
                HNode* targetBucket = table[index]; //Get the target bucket
                while (targetBucket != &(HNode::NIL)) { //If target bucket's first item is not NIL...
                    if (targetBucket->getKey()->getName() == key->getName()) { //If the key's name is the same as the parameter's key's name
                        return targetBucket->getKey(); // Return the value if key matches
                    }
                    targetBucket = targetBucket->getNext(); //Move to the next HNode
                }
            }
            return nullptr;
        }

        //Remove by key
        bool remove(Item* key) {
            int index = hashKey(key->getName());
            HNode* current = table[index];

            if (current != &HNode::NIL && current->getKey()->getName() == key->getName()) {
                table[index] = current->getNext(); // Move the head of the list to the next node
                delete current;
                return true;
            }

            while (current != &HNode::NIL && current->getNext() != &HNode::NIL) {
                if (current->getNext()->getKey()->getName() == key->getName()) {
                    current->removeNext();
                    return true;
                }
                current = current->getNext();
            }
            return false;
        }

        //Modify key
        void modifyKey(Item key, Item newKey, V newValue){
            if(remove(key)){ //Remove the old key
                cout<<"Item has been modified"<<endl;
            }else{
                cout<<"Item is not in the table"<<endl;
            }
            insert(newKey, newValue); //Insert the new key
        }

        //Modify value
        void modifyValue(Item* key, V newValue){
            int index = hashKey(key->getName());
            HNode* targetBucket = table[index];

            while (targetBucket != &HNode::NIL) {
                if (targetBucket->getKey()->getName() == key->getName()) {
                    targetBucket->setValue(newValue); // Update the value if key matches
                    return; // Exit after modifying the value
                }
                targetBucket = targetBucket->getNext(); // Move to the next node
            }
            cout << "Item not found, cannot modify" << endl; // Optional: Inform if the item is not found
        }
        
        //Getter for table
        HNode** getTable() const {
            return table;
        }

        //Destructor
        ~ItemHashTable() {
            for (int i = 0; i < tableSize; ++i) {
                HNode* current = table[i];
                while (current != &HNode::NIL) {
                    HNode* toDelete = current;
                    current = current->getNext(); // Move to the next node
                    delete toDelete->getKey();
                    delete toDelete;              // Delete the current node
                }
            }
            delete[] table; // Delete the array of pointers
        }
};
