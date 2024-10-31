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
	for (int i = 0; i < BUCKET_SIZE; ++i) {
		HNode* node = fInventory.getTable()[i];
		while (node != &(HNode::NIL)) {
			node->getKey()->Inspect();
			node = node->getNext();
		}
		if (node != &(HNode::NIL)) {
			cout << endl;
		}
	}
}
Inventory::~Inventory() {
}