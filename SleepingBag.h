#pragma once
#include "Item.h"
class SleepingBag:public Item{
    private:
        int fRecoveryAmount; //Recovery amount of player's stamina
    public:
        SleepingBag(); //Constructor
        SleepingBag(string pName, string pDescription, int pWeight, bool pIsConsumable, int pRecoveryAmount); //Overloaded constructor
        bool Use(Player& pPlayer) override; //Use SleepingBag, will increase Player's stamina
        void Inspect(); //Inspect Sleeping Bag attribute
        Item* clone() const;    //Clone Sleeping Bag
        //Getter and setter for fRecoveryAmount
        int getRecoveryAmount();
        void setRecoveryAmount(int  pRecoveryAmount);
};