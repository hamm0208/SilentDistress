#pragma once
#include "Item.h"
class Drinks :public Item{
    private:
        int fHydrationValue;
    public:
        Drinks();
        Drinks(string pName, string pDescription, int pWeight, bool pIsConsumable, int pHydrationValue);
        void Use(Player& pPlayer);
        void Inspect();
};

Drinks::Drinks():Item("Unknown Drinks", "No description available", 0, true), //Default values for base class
fHydrationValue(0){}

//Initialize attributes and base class, Item
Drinks::Drinks(string pName, string pDescription, int pWeight, bool pIsConsumable, int pHydrationValue)
:Item(pName, pDescription, pWeight, pIsConsumable),
fHydrationValue(pHydrationValue){};

//Use the Drinks
void Drinks::Use(Player& pPlayer){
    pPlayer.DecreaseThirstLevel(fHydrationValue);
}
//Display Drinks's attributes
void Drinks::Inspect(){
    Item::Inspect();
    cout << "Hydration Value: " << fHydrationValue << endl;
}