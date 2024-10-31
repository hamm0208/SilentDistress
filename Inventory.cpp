#include "Inventory.h"
Inventory::Inventory(int pCapacity) : fInventory(BUCKET_SIZE), fMaxCapacity(pCapacity), fCurrentItem(nullptr), fCurrentCapacity(0) {
}

void Inventory::AddItem(Item* pItem) {
	int item_Weight = pItem->getWeight();
	if ((item_Weight + fCurrentCapacity) >= fMaxCapacity) {
		cout << pItem->getName() << "'s weight will exceed the inventory limit (" << fCurrentCapacity << "/" << fMaxCapacity << ")! Discard some item in inventory to create space to add new items in." << endl;
		return;
	}
	else {
		int item_Quantity = fInventory.findValue(pItem);
		if (item_Quantity > 0) {
			fInventory.modifyValue(pItem, item_Quantity + 1);
		}
		else {
			fInventory.insert(pItem, 1);
		}
	}
	fCurrentCapacity += item_Weight;
}
void Inventory::DisplayInventory() {
	//BUCKET_SIZE IS THE SIZE OF THE BUCKET ADN USE IT TO ITERATE THROUGH THE LIST
	bool isEmpty = true;
	cout << "----------------------------------------------------------------------" << endl;
	for (int i = 0; i < BUCKET_SIZE; ++i) {
		HNode* node = fInventory.getTable()[i];
		while (node != &(HNode::NIL)){
			isEmpty = false;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			cout<<"Details of " << node->getKey()->getName() << ", Quanity: " <<node->getValue() << endl;
			node->getKey()->Inspect();
    		cout << "Total Weight:\t\t\t" << node->getKey()->getWeight() * node->getValue() << "\n";
			node = node->getNext();
		}
	}
	if (isEmpty) {
		cout << "\t\t\tEmpty Inventory!" << endl;
	}
	cout << "----------------------------------------------------------------------" << endl;
}
Inventory::~Inventory() {
}