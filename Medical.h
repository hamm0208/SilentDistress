#pragma once
#include "Item.h"
class Medical:public Item{
    private:
        int fHealAmount; //Heal amount of medical item
    public:
        Medical(); //Default construcotr
        Medical(string pName, string pDescription, int pWeight, bool pIsConsumable, int pHealAmount); //Overloaded constructor
        bool Use(Player& pPlayer) override; //Increase Player's HP
        void Inspect() override; //Inspect Medical Item
        Item* clone() const override;  //Clone new medical item
        //Getter and setter for fDamage
        int getHealAmount();
        void setHealAmount(int pHealAmount);
};