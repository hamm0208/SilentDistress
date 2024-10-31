#pragma once
#include "Item.h"
class Medical:public Item{
    private:
        int fHealAmount; //Heal amount of medical item
    public:
        Medical(); //Default construcotr
        Medical(string pName, string pDescription, int pWeight, bool pIsConsumable, int pHealAmount);
        void Use(Player& pPlayer); //Increase Player's HP
        void Inspect();
        //Getter and setter for fDamage
        int getHealAmount();
        void setHealAmount(int pHealAmount);
};