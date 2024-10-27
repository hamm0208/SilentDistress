#pragma once
#include "Item.h"
class Food:public Item{
	private:
        int fNutrition;             //decrease the hunger of player
        int fHealthRestorationValue; //health restoration of player
        int fStaminaValue;           //Increase stamina of player
        bool fIsCooked;             //Food is cooked flag
        bool fIsCookable;           //Food is cookable flag
    public:
        Food();
        Food(string pName, string pDescription, int pWeight, bool pIsConsumable, int pNutrition,bool pIsCooked, bool pIsCookable, int pHealthRestorationValue, int pStaminaValue);
        void Use(Player& pPlayer);
        void Inspect();
};