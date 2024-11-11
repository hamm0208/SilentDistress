#pragma once
#include "Item.h"
class Weapon:public Item{
    private:
        int fDamage;            //Weapon's additional damage
        int fDurability;        //Amount of times the weapons can be used
        int fCurrentDurability; //Current durability of weapon
    public:
        Weapon();   //Default Construcotr
        Weapon(string pName, string pDescription, int pWeight, bool pIsConsumable, int pDamage, int pDurability); //Overloaded constructor
        bool Use(Player& pPlayer) override; //Use Weapon
        void Inspect() override;  //Inspect Weapon item
        Item* clone() const override;    //Clone Weapon item
        //Getter and setter for fDamage
        int getDamage();
        void setDamage(int pDamage);
        //Getter and setter for fDurability
        int getDurability();
        void setDurability(int pDurability);
        //Getter and setter for fCurrentDurability
        int getCurrentDurability();
        void setCurrentDurability(int pCurrentDurability);
        void decreaseCurrentDurability(int pDecrementValue);
};