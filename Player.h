/*
Remove this when youre done broooo
Maybe sleeping will count as 2 turns, and will increase hunger and thirst
*/
#pragma once
#include "Inventory.h";
#include "Entity.h"
class Player :public Entity{
     private:
        int fHungerLevel;   //0 - 10 Hunger Level, the higher the level, your stamina and current health will slowly decrease
        int fThirstLevel;   //0 - 10 Thirst level, same concept as fHungerLevel
        int fStamina;       //If stamina reach 0, you must go to sleep and waste 1 turn
        bool fIsresting;    //Is resting flag
        Inventory fInventory;
        //List<Decision> fDecisions; 
    public:
        Player();
        Player(string pName, int pAttackDamage, int pHealth, int pHungerLevel, int pThirstLevel, int pStamina, int pInventoryCapacity);
        int getHungerLevel();
        //Getter and setter for fHungerLevel
        void setHungerLevel(int pHungerLevel);

        //Getter and setter for fThirstLevel
        int getThirstLevel();
        void setThirstLevel(int pThirstLevel);

        //Getter and setter for fStamina
        int getfStamina();
        void setStamina(int pStamina);

        //Getter and setter for fIsresting
        bool getfIsresting();
        void setIsresting(bool pIsresting);
        
        void IncreaseHungerLevel(int pIncrementValue); //Increase hunger level
        void DecreaseHungerLevel(int pDecrementValue); //Decrease hunger level, If pDecrementValue is more than fHungerLevel, then set fHungerLevel back to 0

        void IncreaseThirstLevel(int pIncrementValue); //Increase thirst level
        void DecreaseThirstLevel(int pDecrementValue); //Decrease thirst level, If pDecrementValue is more than fThirstLevel, then set fThirstLevel back to 0

        void IncreaseStamina(int pIncrementValue);     //Increase Stamina
        void DecreaseStamina(int pDecrementValue);     //Decrease Stamina

        void Heal(int pHealValue);
        void EquipItem();
        void ViewItems();
        void ViewItemsDetails();
        void ViewItemDetails(Item& pItem);
        void DiscardItem();
        void SearchItems();
        Item* getCurrentItem();
        void UseCurrentItem();

        // void ApplyEffects(); This function will run every turn to check for the Hunger level, thirst level, and stamina
};

//Equip item to be used
void Player::EquipItem() {
	fInventory.ViewInventoryItems();
	string item_Name = "";
	cout << "Name of item to equip (Case sensitive and leave no blank space): ";
	cin.clear();
	getline(cin, item_Name);
	Item* searched_Item = fInventory.SearchItem(item_Name);
	if (searched_Item != (Item*)0) {
		fInventory.setCurrentItem(searched_Item);
		cout << "You have equipped " << searched_Item->getName() << "!" << endl;
	}else {
		cout << item_Name << " is not in your inventory" << endl;
	}
}

void Player::ViewItems(){
    fInventory.ViewInventoryItems();
}

void Player::ViewItemsDetails(){
    fInventory.ViewInventoryDetails();
}

void Player::ViewItemDetails(Item& pItem){
    fInventory.ViewItemDetails(&pItem);
}

void Player::DiscardItem(){
    ViewItems();
    string item_Name = "";
	cout << "Name of item to remove (Case sensitive and leave no blank space): ";
	cin.clear();
	getline(cin, item_Name);
	Item* searched_Item = fInventory.SearchItem(item_Name);
	if (searched_Item != (Item*)0) {
		fInventory.RemoveItem(searched_Item);
	}else {
		cout << item_Name << " is not in your inventory" << endl;
	}
};
void Player::SearchItems(){
    string item_Name = "";
	cout << "Name of item to search (Case sensitive and leave no blank space): ";
	cin.clear();
	getline(cin, item_Name);
	Item* searched_Item = fInventory.SearchItem(item_Name);
	if (searched_Item != (Item*)0) {
        cout<<searched_Item->getName() <<" has been found in your inventory:" <<endl;
        searched_Item->Inspect();
	}else {
		cout << item_Name << " is not in your inventory" << endl;
	}
};
Item* Player::getCurrentItem(){
    fInventory.getCurrentItem();
};
void Player::UseCurrentItem(){
	if(Weapon* weapon = dynamic_cast<Weapon*>(getCurrentItem())){ //If fCurrentItem is type of Weapon, it will decrease the durability instead of the quantity
        if(getIsFighting()){
            weapon->Use(*this);
            setAttackDamage(getAttackDamage() -  weapon->getDamage());
        }else{
            cout<<"You are unable to use "  << weapon->getName() << " right now, because you are not fighting" <<endl;
        }     
    }else{
       fInventory.UseCurrentItem(*this);
    }
};