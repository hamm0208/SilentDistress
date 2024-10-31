#pragma once
#include "Item.h"
#include "Hash.h"

class Inventory{
	private:
		ItemHashTable<int> fInventory;
		int fMaxCapacity;
		int fCurrentCapacity;
		Item* fCurrentItem;
		static const int BUCKET_SIZE = 10;
	public:
		typedef HashNode<Item*, int> HNode;
		Inventory(int pCapacity);
		~Inventory();
		void AddItem(Item* pItem);
		void DisplayInventory();
};

