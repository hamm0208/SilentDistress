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
        //Finish building the overload constructor, getter and setters later
        //Getter and setter for fHungerLevel
        int getHungerLevel();
        void setHungerLevel(string pHungerLevel);

        void IncreaseHungerLevel(int pIncrementValue); //Increase hunger level
        void DecreasehungerLevel(int pDecrementValue); //Decrease hunger level
        void IncreaseStamina(int pIncrementValue);     //Increase Stamina
        void DecreaseStamina(int pDecrementValue);     //Decrease Stamina
        void ApplyEffects(); //This function will run every turn to check for the Hunger level, thirst level, and stamina
};
