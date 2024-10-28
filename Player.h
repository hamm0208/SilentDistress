/*
Remove this when youre done broooo
Maybe sleeping will count as 2 turns, and will increase hunger and thirst
oh and also do the implementation later on the Player.cpp 
*/
#pragma once
#include "Entity.h"
class Player :public Entity{
     private:
        int fHungerLevel;   //0 - 10 Hunger Level, the higher the level, your stamina and current health will slowly decrease
        int fThirstLevel;   //0 - 10 Thirst level, same concept as fHungerLevel
        int fStamina;       //If stamina reach 0, you must go to sleep and waste 1 turn
        bool fIsresting;    //Is resting flag
        //Inventory fInventory;
        //List<Decision> fDecisions; 
    public:
        Player();
        Player(string pName, int pAttackDamage, int pHealth, int pHungerLevel, int pThirstLevel, int pStamina);
        //Getter and setter for fHungerLevel
        int getHungerLevel();
        void setHungerLevel(int pHungerLevel);

        //Getter and setter for fThirstLevel
        int getThirstLevel();
        void setThirstLevel(int pThirstLevel);

        //Getter and setter for fStamina
        int getfStamina();
        void setStamina(int pStamina);

        //Getter and setter for fIsresting
        bool getfIsresting();
        void setIsresting(bool pIsresting);
        
        void IncreaseHungerLevel(int pIncrementValue); //Increase hunger level
        void DecreaseHungerLevel(int pDecrementValue); //Decrease hunger level, If pDecrementValue is more than fHungerLevel, then set fHungerLevel back to 0

        void IncreaseStamina(int pIncrementValue);     //Increase Stamina
        void DecreaseStamina(int pDecrementValue);     //Decrease Stamina

        void Heal(int pHealValue);
        // void ApplyEffects(); This function will run every turn to check for the Hunger level, thirst level, and stamina
};
