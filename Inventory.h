#pragma once
#include "Item.h"
#include "Hash.h"

class Inventory{
	private:
		ItemHashTable<int> fInventory; 	//HashTable of Inventory (Item , Int), Int = Quantity of that Item in the inventory
		int fMaxCapacity;				//Max capacity of the inventory
		int fCurrentCapacity;
		Item* fCurrentItem;
		static const int BUCKET_SIZE = 10;
	public:
		typedef HashNode<Item*, int> HNode;
		Inventory(int pCapacity);
		~Inventory();
		void AddItem(Item* pItem);
		void ViewInventory();
		void ViewItemDetails(Item* pItem);
		bool RemoveItem(Item* pItem);
		bool IsFull();
		//Develop these tomorrow okay
		ItemHashTable<int> getInventory();
		int getMaxCapacity() const;
		int getCurrentCapacity() const;
		void setCurrentCapacity(int pCurrentCapacity);
		Item* getCurrentItem();
		void setCurrentItem(Item* pItem);
		int getCurrentItemQuantity(); //So basically these  will be used by the player, when they use an item
		void DecreaseItemQuantity(int pDecrementValue); //so if item quantity reaches 0, remove item from inventory
};

