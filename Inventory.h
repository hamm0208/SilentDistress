#pragma once
#include "Hash.h"

class Inventory{
	private:
		ItemHashTable<int> fInventory; 	//HashTable of Inventory (Item , Int), Int = Quantity of that Item in the inventory
		int fMaxCapacity;				//Max capacity of the inventory
		int fCurrentCapacity;			//Current capacity of inventory
		Item* fCurrentItem;				//Current equiped item
		static const int BUCKET_SIZE = 10;	//Constant bucket size of the HashTable
	public:
		typedef HashNode<Item*, int> HNode;
		Inventory(int pCapacity);								//Default constructor
		~Inventory();											//Overload constructor
		void AddItem(Item* pItem);								//Adding item to inventory
		bool RemoveItem(Item* pItem);							//Removing an item from inventory
		Item* SearchItem(string pName);							//Search if item exist in fInventory by name
		void ViewInventoryDetails();							//View All Item Details
		void ViewItemDetails(Item* pItem);						//View Item Details
		void ViewInventoryItems();								//View All of items
		void UseCurrentItem(Player & pPlayer);					//Use fCurrentItem
		void DecreaseCurrentItemQuantity(int pDecrementValue); 	//so if item quantity reaches 0, remove item from inventory
		bool IsFull();											//Check if Inventory is full

		//Getters and setters
		ItemHashTable<int> getInventory();				//Getter for fInventory
		int getMaxCapacity() const;						//Getter for fMaxCapacity
		int getCurrentCapacity() const;					//Getter for fCurrentCapacity
		void setCurrentCapacity(int pCurrentCapacity);	//Setter for current capacity
		Item* getCurrentItem();							//Get current item
		void setCurrentItem(Item* pItem);				//Set current item
		int getCurrentItemQuantity();					//So basically these  will be used by the player, when they use an item
};
