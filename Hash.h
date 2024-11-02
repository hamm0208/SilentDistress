#include <iostream>
#include <string>
#include "Item.h"
using namespace std;


template <class K, class V>
class HashNode {
private:
    K fKey;
    V fValue;
    HashNode* fNext;
public:
    static HashNode<K, V> NIL;
    HashNode() {
        fNext = &NIL;
        fKey = K();
        fValue = V();
    }
    HashNode(K pKey, V pValue) {
        fKey = pKey;
        fValue = pValue;
        fNext = &NIL;
    }
    void append(HashNode* newNode) {
        if (fNext != &NIL) {
            newNode->fNext = this->fNext;
        }
        this->fNext = newNode;
    }
    void removeNext() {
        if (fNext != &NIL) {
            HashNode* toDelete = this->fNext;
            this->fNext = this->fNext->fNext;
            delete toDelete;
        }
    }
    K getKey() const {
        return fKey;
    }
    V getValue() const {
        return fValue;
    }
    HashNode* getNext() const {
        return fNext;
    }
    void setValue(V value) {
        fValue = value;
    }
};

template <class K, class V>
HashNode<K, V> HashNode<K, V>::NIL;

template <class V>
class ItemHashTable{
    public:
        typedef HashNode<Item*, V> HNode;
    private:
        int tableSize;
        HNode** table;
    public:
        ItemHashTable(int pTableSize) : tableSize(pTableSize) {
            table = new HNode* [tableSize];
            for (int i = 0; i < tableSize; ++i) {
                table[i] = &HNode::NIL;  // Initialize each to NIL
            }
        }

        int hashKey(string pName) {
            int hash = 0;
            for (size_t x = 0; x < pName.length(); x++) {
                hash += static_cast<int>(pName[x]);
            }
            return hash % tableSize;
        }

        void insert(Item* key, V value) {
            int index = hashKey(key->getName());
            if (table[index] == &HNode::NIL) {
                table[index] = new HNode(key, value);
            }
            else {
                HNode* node = new HNode(key, value);
                table[index]->append(node);
            }
        }

        V findValue(Item* key) {
            int index = hashKey(key->getName());
            HNode* targetBucket = table[index];
            while (targetBucket != &(HNode::NIL)) {
                if (targetBucket->getKey()->getName() == key->getName()){
                    return targetBucket->getValue(); // Return the value if key matches
                }
                targetBucket = targetBucket->getNext();
            }
            return V();
        }

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

        void modifyKey(Item key, Item newKey, V newValue){
            if(remove(key)){
                cout<<"Item has been modified"<<endl;
            }else{
                cout<<"Item is not in the table"<<endl;
            }
            insert(newKey, newValue);
        }

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
        

        HNode** getTable() const {
            return table;
        }

        ~ItemHashTable() {
            for (int i = 0; i < tableSize; ++i) {
                HNode* current = table[i];
                while (current != &HNode::NIL) {
                    HNode* next = current->getNext();
                    delete current;
                    current = next;
                }
            }
            delete[] table;
        }
};