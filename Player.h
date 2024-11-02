/*
Remove this when youre done broooo
Maybe sleeping will count as 2 turns, and will increase hunger and thirst
*/
#pragma once
#include "Entity.h"
#include "Inventory.h"
class Player :public Entity{
     private:
        int fMaxHungerLevel;   //0 - 10 Hunger Level, the higher the level, your stamina and current health will slowly decrease
        int fMaxThirstLevel;   //0 - 10 Thirst level, same concept as fMaxHungerLevel
        int fMaxStaminaLevel;       //If stamina reach 0, you must go to sleep and waste 1 turn
        bool fIsresting;    //Is resting flag
        int fCurrentHungerLevel;
        int fCurrentThirstLevel;
        int fCurrentStaminaLevel;
        Inventory fInventory;
        //List<Decision> fDecisions; 
    public:
        Player();
        Player(string pName, int pAttackDamage, int pHealth, int pHungerLevel, int pThirstLevel, int pStamina, int pInventoryCapacity);
        //Getter and setter for fMaxHungerLevel
        int getMaxHungerLevel();
        void setMaxHungerLevel(int pHungerLevel);
        int getCurrentHungerLevel();
        void setCurrentHungerLevel(int pHungerLevel);

        //Getter and setter for fMaxThirstLevel
        int getMaxThirstLevel();
        void setMaxThirstLevel(int pThirstLevel);
        int getCurrentThirstLevel();
        void setCurrentThirstLevel(int pThirstLevel);

        //Getter and setter for fMaxStaminaLevel
        int getMaxStaminaLevel();
        void setMaxStaminaLevel(int pStamina);
        int getCurrentStaminaLevel();
        void setCurrentStaminaLevel(int pStamina);

        //Getter and setter for fIsresting
        bool getfIsresting();
        void setIsresting(bool pIsresting);
        
        void IncreaseHungerLevel(int pIncrementValue); //Increase hunger level
        void DecreaseHungerLevel(int pDecrementValue); //Decrease hunger level, If pDecrementValue is more than fMaxHungerLevel, then set fMaxHungerLevel back to 0

        void IncreaseThirstLevel(int pIncrementValue); //Increase thirst level
        void DecreaseThirstLevel(int pDecrementValue); //Decrease thirst level, If pDecrementValue is more than fMaxThirstLevel, then set fMaxThirstLevel back to 0

        void IncreaseStamina(int pIncrementValue);     //Increase Stamina
        void DecreaseStamina(int pDecrementValue);     //Decrease Stamina
        void Heal(int pHealValue);
        void AddItem(Item* pItem);
        void EquipItem();
        void ViewItems();
        void ViewItemsDetails();
        void ViewItemDetails(Item& pItem);
        void DiscardItem();
        void SearchItems();
        Item* getCurrentItem();
        void UseCurrentItem();
        // void ApplyEffects(); This function will run every turn to check for the Hunger level, thirst level, and stamina
};