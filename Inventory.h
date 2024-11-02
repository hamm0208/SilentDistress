#pragma once
#include "Weapon.h"
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
<<<<<<< HEAD
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
=======
>>>>>>> parent of 6ddcac8 (Finish Inventory class)
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

