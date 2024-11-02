#include "Inventory.h"
Inventory::Inventory(int pCapacity) : fInventory(BUCKET_SIZE), fMaxCapacity(pCapacity), fCurrentItem(nullptr), fCurrentCapacity(0) {
}

//Add  new item to inventory
void Inventory::AddItem(Item* pItem) {
	int item_Weight = pItem->getWeight(); //Item's weight
	if (IsFull()) {
		if ((item_Weight + fCurrentCapacity) >= fMaxCapacity) { //If item's weight + fCurrentCapacity reaches over fMaxCapacity, then you can't add more items
			cout << pItem->getName() << "'s weight will exceed the inventory limit (" << fCurrentCapacity << "/" << fMaxCapacity << ")! Discard some item in inventory to create space to add new items in." << endl;
			return; //End function
		}
		else {
			int item_Quantity = fInventory.findValue(pItem);		//Find the item quantity in inventory
			if (item_Quantity > 0) {								//If quantity > 1, means that the item already exist in inventory
				fInventory.modifyValue(pItem, item_Quantity + 1);	//Increase the quantity of that item by 1
			}
			else {													//If item does not exist in Inventory,
				fInventory.insert(pItem, 1);						//then insert the new  item
			}
			fCurrentCapacity += item_Weight;						//Increase fCurrentCapacity by item's weight
		}
	}else{
		cout << "Inventory is full!" << endl;
	}
	
}

//Remove item from inventory
bool Inventory::RemoveItem(Item* pItem) {
	int item_Quantity = fInventory.findValue(pItem);											//Find the item quantity in inventory
	cout << "\nDiscarding an item includes removing all the quantity of " << pItem->getName() << "(" << item_Quantity << " left)" << endl;
	int choice = 0;
	do {
		cout << "\nProceed?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		cout << "Choice: ";
		cin >> choice;
		if (choice <= 0 || choice > 2) {
			cout << "Invalid choice! Try again." << endl;
		}
	} while (choice < 1 || choice > 2);
	if (choice == 1) {
		cout << pItem->getName() << " has been discarded!\n" << endl;
		fInventory.remove(pItem);
		return true;
	}
	else {
		cout << pItem->getName() << " will not be discarded!\n" << endl;
		return false;
	}
};

<<<<<<< HEAD
//Search item from inventory by name
Item* Inventory::SearchItem(string pName) {
	int index = fInventory.hashKey(pName);
	HNode* node = fInventory.getTable()[index];		//Get the head HashNode from the table through the index
	while (node != &(HNode::NIL)) {					//While HNode is not the sentinel node, display item details
		if (node->getKey()->getName() == pName) {
			return node->getKey();
		}
		node = node->getNext();						//Move to next node
	}
	return (Item*)0;
};

=======
>>>>>>> parent of 6ddcac8 (Finish Inventory class)
//Display item details
void Inventory::ViewItemDetails(Item* pItem) {
	int item_Quantity = fInventory.findValue(pItem);										//Find the item quantity in inventory
	if (item_Quantity > 0) {																//If quantity > 0, item exist
		cout << "Details of " << pItem->getName() << ", Quanity: " << item_Quantity << endl;
		pItem->Inspect();
		cout << "Total Weight:\t\t\t" << pItem->getWeight() * item_Quantity << "\n";
	}
	else {
		cout << "Item does not exist in inventory." << endl;
	}
}

//Check whether the inventory is full
bool Inventory::IsFull() {
	return fCurrentCapacity >= fMaxCapacity;
}


//Display all items's detail in  Inventory
void Inventory::ViewInventory() {
	bool isEmpty = true;							//Is inventory empty flag
	cout << "----------------------------------------------------------------------" << endl;
	for (int i = 0; i < BUCKET_SIZE; ++i) {			//Iterate through the Inventory
		HNode* node = fInventory.getTable()[i];		//Get the HashNode from the table through the index
		while (node != &(HNode::NIL)){				//While HNode is not the sentinel node, display item details
			isEmpty = false;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			ViewItemDetails(node->getKey());
			node = node->getNext();					//Move to next node
		}
	}
	if (isEmpty) {
		cout << "\t\t\tEmpty Inventory!" << endl;
	}
	cout << "----------------------------------------------------------------------" << endl;
}
Inventory::~Inventory() {
}