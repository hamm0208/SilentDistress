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
        void Use(Player& pPlayer) override;
        void Inspect();

        //Getter and setter for fNutrition
        int getNutrition(){
            return fNutrition;
        }
        void setNutrition(int  pNutrition){
            fNutrition = pNutrition;
        }

        //Getter and setter for fHealthRestorationValue
        int getHealthRestorationValue(){
            return fHealthRestorationValue;
        }
        void setHealthRestorationValue(int  pHealthRestorationValue){
            fHealthRestorationValue = pHealthRestorationValue;
        }

        //Getter and setter for fStaminaValue
        int getStaminaValue(){
            return fStaminaValue;
        }
        void setStaminaValue(int  pStaminaValue){
            fStaminaValue = pStaminaValue;
        }

        //Getter and setter for fIsCooked
        bool getIsCooked(){
            return fIsCooked;
        }
        void setIsCooked(bool pIsCooked){
            fIsCooked = pIsCooked;
        }
        
        //Getter and setter for fIsCookable
        bool getIsCookable(){
            return fIsCookable;
        }
        void setIsCookable(bool pIsCookable){
            fIsCookable = pIsCookable;
        }
};