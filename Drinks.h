#pragma once
#include "Item.h"
class Drinks :public Item{
    private:
        int fHydrationValue; //Hydration value for the player
    public:
        Drinks();   //Default construcotr
        Drinks(string pName, string pDescription, int pWeight, bool pIsConsumable, int pHydrationValue);  //Overloaded constructor
        bool Use(Player& pPlayer) override; //Use drinks to lower thirst level
        void Inspect() override; //Inspect drink item
        Item* clone() const override; //Clone drink item
        
        //Getter and setter for fHydrationValue
        int getHydrationValue();
        void setHydrationValue(int pHydrationValue);
};