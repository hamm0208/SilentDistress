#pragma once
#include "Item.h"
class SleepingBag:public Item{
    private:
        int fRecoveryAmount; //Recovery amount of player's stamina
    public:
        SleepingBag(); //Constructor
        SleepingBag(string pName, string pDescription, int pWeight, bool pIsConsumable, int pRecoveryAmount);
        void Use(Player& pPlayer);
        void Inspect();
        //Getter and setter for fRecoveryAmount
        int getRecoveryAmount();
        void setRecoveryAmount(int  pRecoveryAmount);
};