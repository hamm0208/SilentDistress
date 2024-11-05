#include "Inventory.h"
#include "Weapon.h"


Inventory::Inventory(int pCapacity) : fInventory(BUCKET_SIZE), fMaxCapacity(pCapacity), fCurrentItem(nullptr), fCurrentCapacity(0) {
}

//Add  new item to inventory
void Inventory::AddItem(Item* pItem) {
	int item_Weight = pItem->getWeight(); //Item's weight
	if (!IsFull()) {
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
				fInventory.insert(pItem->clone(), 1);				//then insert the cloned item
			}
			cout << "You have added " << pItem->getName() << " into your inventory" << endl;
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
		cout << "Choice (1 or 2): ";
		cin >> choice;
		if (choice <= 0 || choice > 2) {
			cout << "Invalid choice! Try again." << endl;
		}
	} while (choice < 1 || choice > 2);
	if (choice == 1) {
		cout << pItem->getName() << " has been discarded!\n" << endl;
		fCurrentCapacity = fCurrentCapacity - (pItem->getWeight() * item_Quantity);
		fInventory.remove(pItem);
		return true;
	}
	else {
		cout << pItem->getName() << " will not be discarded!\n" << endl;
		return false;
	}
};

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
//View all items's detail in fInventory
void Inventory::ViewInventoryDetails() {
	system("CLS");
	bool isEmpty = true;							//Is inventory empty flag
	cout << "------------------------------------------------------------------" << endl;
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
	cout << "------------------------------------------------------------------" << endl;
}

//View all the items in fInventory
void Inventory::ViewInventoryItems() {
	int count = 0;
	bool isEmpty = true;							//Is inventory empty flag
	cout << "--------------------------------------------------\n" << endl;
	cout << "\t\tItems In Inventory\n" << endl;
	for (int i = 0; i < BUCKET_SIZE; ++i) {			//Iterate through the Inventory
		HNode* node = fInventory.getTable()[i];		//Get the HashNode from the table through the index
		while (node != &(HNode::NIL)) {				//While HNode is not the sentinel node, display item details
			isEmpty = false;
			count++;
			cout << count << ". " << node->getValue() <<" " << node->getKey()->getName() << ", Total Weight: " << (node->getKey()->getWeight() * node->getValue()) << endl;
			node = node->getNext();					//Move to next node
		}
	}
	if (isEmpty) {
		cout << "\t\tEmpty Inventory!" << endl;
	}
	cout << "\n\t\tWeight: " << fCurrentCapacity << "/" << fMaxCapacity << endl;

	cout << "\n--------------------------------------------------\n" << endl;
};

//Check whether the inventory is full
bool Inventory::IsFull() {
	return fCurrentCapacity >= fMaxCapacity;
}

//Getter fInventory
ItemHashTable<int> Inventory::getInventory(){
	return fInventory;
}

//Getter fMaxCapacity
int Inventory::getMaxCapacity() const{
	return fMaxCapacity;	
};

//Getter fCurrentCapacity
int Inventory::getCurrentCapacity() const{
	return fCurrentCapacity;
};

//Setter fCurrentCapacity
void Inventory::setCurrentCapacity(int pCurrentCapacity){
	fCurrentCapacity = pCurrentCapacity;
};
//Get fCurrentItem
Item* Inventory:: getCurrentItem(){
	return fCurrentItem;
};

//Set fCurrentItem
void Inventory::setCurrentItem(Item* pItem){
	fCurrentItem = pItem;
};

//Get fCurrentItem's Quantity
int Inventory::getCurrentItemQuantity(){
	return fInventory.findValue(fCurrentItem);
};

//Decrease Quantity of fCurrentItem
void Inventory::DecreaseCurrentItemQuantity(int pDecrementValue){
	int item_CurrentQuantity = getCurrentItemQuantity();
	int item_AfterDeduction = item_CurrentQuantity - pDecrementValue;
	if(item_AfterDeduction<=0){ //If after deduction is less or equal to 0, the item will be removed from inventory
		cout << fCurrentItem->getName() << " will now be discarded" << endl;
		fInventory.remove(fCurrentItem);
	}else{
		fInventory.modifyValue(fCurrentItem, pDecrementValue);
	}
};

//Use fCurrentItem
void Inventory::UseCurrentItem(Player& pPlayer){
	if(fCurrentItem != NULL){
		if(fCurrentItem->Use(pPlayer)){
			cout << "You have used " << fCurrentItem->getName() << endl;
			if(fCurrentItem->getIsConsumable()){
				DecreaseCurrentItemQuantity(1);
				if (getCurrentItemQuantity() > 0) {
					cout << "Decreasing " << fCurrentItem->getName() << "'s quantity by 1" << endl;
					cout << "You only have " << getCurrentItemQuantity() << " " << getCurrentItem()->getName() << " left!" << endl;
				}
			}
			if(Weapon* weapon = dynamic_cast<Weapon*>(fCurrentItem)){ //If fCurrentItem is type of Weapon, it will decrease the durability instead of the quantity
				weapon->decreaseCurrentDurability(1);
				cout << "Decreasing " << fCurrentItem->getName() << "'s durability by 1" << endl;
				if(weapon->getCurrentDurability() <= 0){ //If durability reaches 0, then it will call DecreaseCurrentItemQuantity(1), which will decrease the current item by 1
					DecreaseCurrentItemQuantity(1);
					if (getCurrentItemQuantity() > 0) {	//If there are still extra quantity, then change the CurrentDurability to the max Durability
						cout << "Decreasing " << fCurrentItem->getName() << "'s quantity by 1" << endl;
						cout << "You only have " << getCurrentItemQuantity() << " " << getCurrentItem()->getName() << " left!" << endl;
						weapon->setCurrentDurability(weapon->getDurability());
					}
				}
			}
		}
	}else{
		cout<<"You have no items equipped"<<endl;
	}
};

Inventory::~Inventory() {
}