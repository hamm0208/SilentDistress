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
        Food(); //Constructor
        Food(string pName, string pDescription, int pWeight, bool pIsConsumable, int pNutrition,bool pIsCooked, bool pIsCookable, int pHealthRestorationValue, int pStaminaValue); //Overloaded constructor
        bool Use(Player& pPlayer) override; //Use Food Item
        void Inspect() override; //Inspect Food Item
        Item* clone() const override; //Clone Food Item
        
        //Getter and setter for fNutrition
        int getNutrition();
        void setNutrition(int  pNutrition);
        //Getter and setter for fHealthRestorationValue
        int getHealthRestorationValue();
        void setHealthRestorationValue(int pHealthRestorationValue);

        //Getter and setter for fStaminaValue
        int getStaminaValue();
        void setStaminaValue(int  pStaminaValue);
        //Getter and setter for fIsCooked
        bool getIsCooked();
        void setIsCooked(bool pIsCooked);

        //Getter and setter for fIsCookable
        bool getIsCookable();
        void setIsCookable(bool pIsCookable);
};